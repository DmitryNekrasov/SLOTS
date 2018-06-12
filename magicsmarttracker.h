#pragma once

#include <array>

#include "smarttracker.h"

class MagicSmartTracker : public SmartTracker
{
public:
    MagicSmartTracker();

    virtual ~MagicSmartTracker() = default;

    virtual void init(const cv::Mat& frame, const cv::Rect2d& roi) override;
    virtual void update(const cv::Mat& frame, cv::Rect2d& roi) override;

private:
    class SmartQueue
    {
    private:
        static constexpr size_t N = 10;
        std::array<cv::Mat, N> mats;
        size_t index;
        size_t counter;

    public:
        SmartQueue() :
            index(0),
            counter(0)
        {}

        void put(cv::Mat mat) {
            mats[index] = mat;
            index = (index + 1) % N;
            if (counter < N) {
                counter++;
            }
        }

        cv::Mat get() {
            return mats[(index + 1) % N];
        }

        bool isFull() {
            return counter == N;
        }
    };

private:
    double m_Lambda;
    double m_Padding;
    float m_OutputSigmaFactor;
    double m_InterpFactor;
    double m_Sigma;
    int m_CellSize;
    int m_TemplateSize;
    double m_ScaleStep;
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

    cv::Mat m_FirstObject;
    SmartQueue m_SmartQueue;

private:
    cv::Mat getFeatures(const cv::Mat& frame, bool initHanningMats, float scale_adjust = 1.0f);
    void createHanningMats();
    cv::Mat createGaussianPeak(int size_y, int size_x);
    void train(cv::Mat x, double train_interp_factor);
    cv::Mat gaussianCorrelation(cv::Mat x1, cv::Mat x2);
    cv::Point2f detect(cv::Mat z, cv::Mat x, float& peak_value);
    float subPixelPeak(float left, float center, float right);
};
