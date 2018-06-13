#pragma once

#include "smarttracker.h"

#include <string>

#include <opencv2/tracking/tracking.hpp>

class DefaultSmartTracker : public SmartTracker
{
public:
    DefaultSmartTracker(std::string algorithm_name);

    virtual ~DefaultSmartTracker() = default;

    virtual void init(const cv::Mat& frame, const cv::Rect2d& roi) override;
    virtual void update(const cv::Mat& frame, cv::Rect2d& roi) override;

private:
    cv::Ptr<cv::Tracker> m_Tracker;
};
