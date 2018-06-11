#include "magicsmarttracker.h"

#include "misc.h"

MagicSmartTracker::MagicSmartTracker():
    m_Lambda(0.0001f),
    m_Padding(2.5f),
    m_OutputSigmaFactor(0.1f),
    m_InterpFactor(0.005f),
    m_Sigma(0.4f),
    m_CellSize(4),
    m_LabCentroids(g_ClustersNumber, 3, CV_32FC1, &g_Data),
    m_TemplateSize(96),
    m_ScaleStep(1.05f),
    m_ScaleWeight(0.95f)

{
    m_CellSizeSqr = m_CellSize * m_CellSize;
}

void MagicSmartTracker::init(const cv::Mat& frame, const cv::Rect2d& roi) {

}

void MagicSmartTracker::update(const cv::Mat& frame, cv::Rect2d& roi) {

}
