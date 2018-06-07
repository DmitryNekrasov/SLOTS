#pragma once

#include <opencv2/opencv.hpp>

class SmartTracker
{
public:
    SmartTracker() {}

    virtual ~SmartTracker() = default;

    virtual void init(const cv::Mat& frame, const cv::Rect2d& roi) = 0;
    virtual void update(const cv::Mat& frame, cv::Rect2d& roi) = 0;
};
