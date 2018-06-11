#include "magicsmarttracker.h"

#include <cassert>

#include "hogfeatures.h"
#include "misc.h"

#include <QDebug>

MagicSmartTracker::MagicSmartTracker():
    m_Lambda(0.0001f),
    m_Padding(2.5),
//    m_OutputSigmaFactor(0.1f),
    m_InterpFactor(0.012f),
    m_Sigma(0.6f),
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
    getFeatures(frame, true);
}

void MagicSmartTracker::update(const cv::Mat& frame, cv::Rect2d& roi) {

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

    return features;
}
