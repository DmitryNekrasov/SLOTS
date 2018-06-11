#pragma once

#include "smarttracker.h"

class MagicSmartTracker : public SmartTracker
{
public:
    MagicSmartTracker();

    virtual ~MagicSmartTracker() = default;

    virtual void init(const cv::Mat& frame, const cv::Rect2d& roi) override;
    virtual void update(const cv::Mat& frame, cv::Rect2d& roi) override;

private:
    double m_Lambda;
    double m_Padding;
    float m_OutputSigmaFactor;
    float m_InterpFactor;
    float m_Sigma;
    int m_CellSize;
    cv::Mat m_LabCentroids;
    int m_CellSizeSqr;
    int m_TemplateSize;
    float m_ScaleStep;
    float m_ScaleWeight;

private:
    cv::Rect2d m_Roi;
    float m_Scale;
    cv::Size m_TemplateCvSize;
    int m_SizePatch[3];
    cv::Mat m_Hann;
    cv::Mat m_Features;
    cv::Mat m_GausseanPeak;
    cv::Mat m_AlphaMat;

private:
    cv::Mat getFeatures(const cv::Mat& frame, bool initHanningMats, float scale_adjust = 1.0f);
    void createHanningMats();
    cv::Mat createGaussianPeak(int size_y, int size_x);
    void train(cv::Mat x, double train_interp_factor);
    cv::Mat gaussianCorrelation(cv::Mat x1, cv::Mat x2);
};
