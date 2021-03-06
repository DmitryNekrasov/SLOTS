#include "magicsmarttracker.h"

#include <cassert>
#include <cmath>

#include "fft.h"
#include "hogfeatures.h"
#include "misc.h"

#include <QDebug>

static constexpr double g_Eps = 0.00000000000000000001;
static constexpr double g_Pi = 3.14159265358979323846;

MagicSmartTracker::MagicSmartTracker(bool scale_invariance):
    m_Lambda(0.0001),
    m_Padding(2.5),
    m_OutputSigmaFactor(0.125f),
    m_InterpFactor(0.012),
    m_Sigma(0.6),
    m_CellSize(4),
    m_TemplateSize(96),
    m_ScaleStep(scale_invariance ? 1.05 : 1.00),
    m_ScaleWeight(0.95f)

{}

void MagicSmartTracker::init(const cv::Mat& frame, const cv::Rect2d& roi) {
    m_Roi = roi;
    m_FirstObject = frame(m_Roi);
    assert(m_Roi.width > 0 && m_Roi.height > 0);
    m_Features = getFeatures(frame, true);
    m_GausseanPeak = createGaussianPeak(m_SizePatch[0], m_SizePatch[1]);
    m_AlphaMat = cv::Mat(m_SizePatch[0], m_SizePatch[1], CV_32FC2, 0.0);
    train(m_Features, 1.0);
}

void MagicSmartTracker::update(const cv::Mat& frame, cv::Rect2d& roi) {
    //-----

//    cv::Mat putImage = frame(roi);
//    m_SmartQueue.put(putImage.clone());
//    cv::imshow("put", putImage);
//    if (m_SmartQueue.isFull()) {
//        cv::Mat getImage = m_SmartQueue.get();
//        cv::imshow("get", getImage);

//        cv::Mat result;
//        cv::matchTemplate(frame, getImage, result, cv::TM_CCOEFF_NORMED);
//        cv::imshow("result", result);

//        cv::Mat q = result >= 0.6;
//        cv::imshow("q", q);

//        double min, max;
//        cv::minMaxLoc(result, &min, &max);
//        qDebug() << max << "\n";
//    }

    //-----

    if (m_Roi.x + m_Roi.width <= 0) {
        m_Roi.x = -m_Roi.width + 1;
    }
    if (m_Roi.y + m_Roi.height <= 0) {
        m_Roi.y = -m_Roi.height + 1;
    }
    if (m_Roi.x >= frame.cols - 1) {
        m_Roi.x = frame.cols - 2;
    }
    if (m_Roi.y >= frame.rows - 1) {
        m_Roi.y = frame.rows - 2;
    }

    double cx = m_Roi.x + m_Roi.width / 2.0;
    double cy = m_Roi.y + m_Roi.height / 2.0;

    float peak_value;
    cv::Point2f res = detect(m_Features, getFeatures(frame, 0, 1.0f), peak_value);

    float new_peak_value;
    cv::Point2f new_res = detect(m_Features, getFeatures(frame, 0, 1.0f / float(m_ScaleStep)), new_peak_value);

    if (m_ScaleWeight * new_peak_value > peak_value) {
        res = new_res;
        peak_value = new_peak_value;
        m_Scale /= m_ScaleStep;
        m_Roi.width /= m_ScaleStep;
        m_Roi.height /= m_ScaleStep;
    }

    new_res = detect(m_Features, getFeatures(frame, 0, float(m_ScaleStep)), new_peak_value);

    if (m_ScaleWeight * new_peak_value > peak_value) {
        res = new_res;
        peak_value = new_peak_value;
        m_Scale *= m_ScaleStep;
        m_Roi.width *= m_ScaleStep;
        m_Roi.height *= m_ScaleStep;
    }

    m_Roi.x = cx - m_Roi.width / 2.0 + double(res.x * m_CellSize * m_Scale);
    m_Roi.y = cy - m_Roi.height / 2.0 + double(res.y * m_CellSize * m_Scale);

    if (m_Roi.x >= frame.cols - 1) {
        m_Roi.x = frame.cols - 1;
    }
    if (m_Roi.y >= frame.rows - 1) {
        m_Roi.y = frame.rows - 1;
    }
    if (m_Roi.x + m_Roi.width <= 0) {
        m_Roi.x = -m_Roi.width + 2;
    }
    if (m_Roi.y + m_Roi.height <= 0) {
        m_Roi.y = -m_Roi.height + 2;
    }

    assert(m_Roi.width >= 0 && m_Roi.height >= 0);
    cv::Mat x = getFeatures(frame, 0);
    train(x, m_InterpFactor);
    roi = m_Roi;
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
        hann1t.at<float> (0, i) = 0.5f * float(1 - std::cos(2 * g_Pi * i / (hann1t.cols - 1)));
    }
    for (int i = 0; i < hann2t.rows; i++) {
        hann2t.at<float> (i, 0) = 0.5f * float(1 - std::cos(2 * g_Pi * i / (hann2t.rows - 1)));
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

cv::Point2f MagicSmartTracker::detect(cv::Mat z, cv::Mat x, float& peak_value) {
    cv::Mat k = gaussianCorrelation(x, z);
    cv::Mat res = (real(fftd(complexMultiplication(m_AlphaMat, fftd(k)), true)));

    cv::Point2i pi;
    double pv;
    cv::minMaxLoc(res, NULL, &pv, NULL, &pi);
    peak_value = float(pv);

    cv::Point2f p(float(pi.x), float(pi.y));

    if (pi.x > 0 && pi.x < res.cols-1) {
        p.x += subPixelPeak(res.at<float>(pi.y, pi.x-1), peak_value, res.at<float>(pi.y, pi.x+1));
    }

    if (pi.y > 0 && pi.y < res.rows-1) {
        p.y += subPixelPeak(res.at<float>(pi.y-1, pi.x), peak_value, res.at<float>(pi.y+1, pi.x));
    }

    p.x -= (res.cols) / 2;
    p.y -= (res.rows) / 2;

    return p;
}

float MagicSmartTracker::subPixelPeak(float left, float center, float right) {
    float divisor = 2 * center - right - left;

    if (fabs(double(divisor)) < g_Eps) {
        return 0;
    }

    return 0.5f * (right - left) / divisor;
}
