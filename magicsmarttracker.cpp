#include "magicsmarttracker.h"

#include <cassert>
#include <cmath>

#include "fft.h"
#include "hogfeatures.h"
#include "misc.h"

#include <QDebug>

MagicSmartTracker::MagicSmartTracker():
    m_Lambda(0.0001),
    m_Padding(2.5),
//    m_OutputSigmaFactor(0.1f),
    m_InterpFactor(0.012f),
    m_Sigma(0.6),
    m_CellSize(4),
//    m_LabCentroids(g_ClustersNumber, 3, CV_32FC1, &g_Data),
    m_TemplateSize(96),
    m_ScaleStep(1.05f),
    m_ScaleWeight(0.95f)

{
//    m_CellSizeSqr = m_CellSize * m_CellSize;
}

void MagicSmartTracker::init(const cv::Mat& frame, const cv::Rect2d& roi) {
    m_Roi = roi;
    assert(m_Roi.width > 0 && m_Roi.height > 0);
    m_Features = getFeatures(frame, true);
    m_GausseanPeak = createGaussianPeak(m_SizePatch[0], m_SizePatch[1]);
    m_AlphaMat = cv::Mat(m_SizePatch[0], m_SizePatch[1], CV_32FC2, 0.0);
    train(m_Features, 1.0);
}

void MagicSmartTracker::update(const cv::Mat& frame, cv::Rect2d& roi) {
    if (roi.x + roi.width <= 0) {
        roi.x = -roi.width + 1;
    }
    if (roi.y + roi.height <= 0) {
        roi.y = -roi.height + 1;
    }
    if (roi.x >= frame.cols - 1) {
        roi.x = frame.cols - 2;
    }
    if (roi.y >= frame.rows - 1) {
        roi.y = frame.rows - 2;
    }

    double cx = roi.x + roi.width / 2.0;
    double cy = roi.y + roi.height / 2.0;

    float peak_value;
    cv::Point2f res = detect(m_Features, getFeatures(frame, 0, 1.0f), peak_value);

    if (m_ScaleStep != 1) {
        float new_peak_value;
        cv::Point2f new_res = detect(m_Features, getFeatures(frame, 0, 1.0f / m_ScaleStep), new_peak_value);

        if (m_ScaleWeight * new_peak_value > peak_value) {
            res = new_res;
            peak_value = new_peak_value;
            m_Scale /= m_ScaleStep;
            roi.width /= m_ScaleStep;
            roi.height /= m_ScaleStep;
        }

        new_res = detect(m_Features, getFeatures(frame, 0, m_ScaleStep), new_peak_value);

        if (m_ScaleWeight * new_peak_value > peak_value) {
            res = new_res;
            peak_value = new_peak_value;
            m_Scale *= m_ScaleStep;
            roi.width *= m_ScaleStep;
            roi.height *= m_ScaleStep;
        }
    }

    roi.x = cx - roi.width / 2.0f + ((float) res.x * m_CellSize * m_Scale);
    roi.y = cy - roi.height / 2.0f + ((float) res.y * m_CellSize * m_Scale);

    if (roi.x >= frame.cols - 1) {
        roi.x = frame.cols - 1;
    }
    if (roi.y >= frame.rows - 1) {
        roi.y = frame.rows - 1;
    }
    if (roi.x + roi.width <= 0) {
        roi.x = -roi.width + 2;
    }
    if (roi.y + roi.height <= 0) {
        roi.y = -roi.height + 2;
    }

    assert(roi.width >= 0 && roi.height >= 0);
    cv::Mat x = getFeatures(frame, 0);
    train(x, m_InterpFactor);
}

cv::Mat MagicSmartTracker::getFeatures(const cv::Mat& frame, bool initHanningMats, float scale_adjust) {
    if (initHanningMats) {
        int padded_width = int(m_Roi.width * m_Padding);
        int padded_height = int(m_Roi.height * m_Padding);

        if (m_TemplateSize > 1) {
            if (padded_width >= padded_height) {
                m_Scale = padded_width / float(m_TemplateSize);
            } else {
                m_Scale = padded_height / float(m_TemplateSize);
            }

            m_TemplateCvSize.width = int(padded_width / m_Scale);
            m_TemplateCvSize.height = int(padded_height / m_Scale);
        } else {
            m_TemplateCvSize.width = padded_width;
            m_TemplateCvSize.height = padded_height;
            m_Scale = 1;
        }

        m_TemplateCvSize.width = int(m_TemplateCvSize.width / (2 * m_CellSize)) * 2 * m_CellSize + 2 * m_CellSize;
        m_TemplateCvSize.height = int(m_TemplateCvSize.height / (2 * m_CellSize)) * 2 * m_CellSize + 2 * m_CellSize;
    }

    cv::Rect2d extracted_roi;
    extracted_roi.width = double(scale_adjust * m_Scale * m_TemplateCvSize.width);
    extracted_roi.height = double(scale_adjust * m_Scale * m_TemplateCvSize.height);

    double center_x = m_Roi.x + m_Roi.width / 2;
    double center_y = m_Roi.y + m_Roi.height / 2;
    extracted_roi.x = center_x - extracted_roi.width / 2;
    extracted_roi.y = center_y - extracted_roi.height / 2;

    cv::Mat subwindow = getSubwindow(frame, extracted_roi, cv::BORDER_REPLICATE);
    if (subwindow.cols != m_TemplateCvSize.width || subwindow.rows != m_TemplateCvSize.height) {
        cv::resize(subwindow, subwindow, m_TemplateCvSize);
    }

    cv::Mat features;

    IplImage ipl = subwindow;
    HogFeatures *hogFeatures;
    getHogFeatures(&ipl, m_CellSize, &hogFeatures);
    normalizeAndTruncate(hogFeatures, 0.2f);
    PCAFeatureMaps(hogFeatures);
    m_SizePatch[0] = hogFeatures->size_y;
    m_SizePatch[1] = hogFeatures->size_x;
    m_SizePatch[2] = hogFeatures->features_number;

    features = cv::Mat(cv::Size(hogFeatures->features_number,hogFeatures->size_x * hogFeatures->size_y),
                       CV_32F, hogFeatures->map);
    features = features.t();

    freeHogFeatures(&hogFeatures);

    if (initHanningMats) {
        createHanningMats();
    }

    features = m_Hann.mul(features);

    return features;
}

void MagicSmartTracker::createHanningMats() {
    cv::Mat hann1t = cv::Mat(cv::Size(m_SizePatch[1], 1), CV_32F, cv::Scalar(0));
    cv::Mat hann2t = cv::Mat(cv::Size(1, m_SizePatch[0]), CV_32F, cv::Scalar(0));

    for (int i = 0; i < hann1t.cols; i++) {
        hann1t.at<float> (0, i) = 0.5 * (1 - std::cos(2 * 3.14159265358979323846 * i / (hann1t.cols - 1)));
    }
    for (int i = 0; i < hann2t.rows; i++) {
        hann2t.at<float> (i, 0) = 0.5 * (1 - std::cos(2 * 3.14159265358979323846 * i / (hann2t.rows - 1)));
    }

    cv::Mat hann2d = hann2t * hann1t;
    cv::Mat hann1d = hann2d.reshape(1, 1);

    m_Hann = cv::Mat(cv::Size(m_SizePatch[0] * m_SizePatch[1], m_SizePatch[2]), CV_32F, cv::Scalar(0));
    for (int i = 0; i < m_SizePatch[2]; i++) {
        for (int j = 0; j < m_SizePatch[0] * m_SizePatch[1]; j++) {
            m_Hann.at<float>(i, j) = hann1d.at<float>(0, j);
        }
    }
}

cv::Mat MagicSmartTracker::createGaussianPeak(int size_y, int size_x) {
    cv::Mat_<float> result(size_y, size_x);

    int size_y_half = size_y / 2;
    int size_x_half = size_x / 2;

    float output_sigma = sqrt(float(size_x * size_y)) / float(m_Padding) * m_OutputSigmaFactor;
    float mult = -0.5f / (output_sigma * output_sigma);

    for (int i = 0; i < size_y; i++) {
        for (int j = 0; j < size_x; j++) {
            int first = i - size_y_half;
            int second = j - size_x_half;
            result(i, j) = exp(mult * float(first * first + second * second));
        }
    }

    return fftd(result);
}

void MagicSmartTracker::train(cv::Mat x, double train_interp_factor) {
    cv::Mat gaussian_correlation_mat = gaussianCorrelation(x, x);
    cv::Mat alpha_mat = complexDivision(m_GausseanPeak, (fftd(gaussian_correlation_mat) + m_Lambda));

    m_Features = (1 - train_interp_factor) * m_Features + train_interp_factor * x;
    m_AlphaMat = (1 - train_interp_factor) * m_AlphaMat + train_interp_factor * alpha_mat;
}

cv::Mat MagicSmartTracker::gaussianCorrelation(cv::Mat x1, cv::Mat x2) {
    cv::Mat c = cv::Mat(cv::Size(m_SizePatch[1], m_SizePatch[0]), CV_32F, cv::Scalar(0));

    cv::Mat caux;
    cv::Mat x1aux;
    cv::Mat x2aux;

    for (int i = 0; i < m_SizePatch[2]; i++) {
        x1aux = x1.row(i);
        x1aux = x1aux.reshape(1, m_SizePatch[0]);
        x2aux = x2.row(i).reshape(1, m_SizePatch[0]);
        cv::mulSpectrums(fftd(x1aux), fftd(x2aux), caux, 0, true);
        caux = fftd(caux, true);
        rearrange(caux);
        caux.convertTo(caux,CV_32F);
        c = c + real(caux);
    }

    cv::Mat d;
    cv::max(((cv::sum(x1.mul(x1))[0] + cv::sum(x2.mul(x2))[0]) - 2.0 * c) /
            (m_SizePatch[0] * m_SizePatch[1] * m_SizePatch[2]), 0, d);

    cv::Mat k;
    cv::exp((-d / (m_Sigma * m_Sigma)), k);
    return k;
}

cv::Point2f MagicSmartTracker::detect(cv::Mat z, cv::Mat x, float &peak_value) {
    //TODO
    return cv::Point2f(0, 0);
}
