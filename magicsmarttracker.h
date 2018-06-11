#pragma once

#include "smarttracker.h"

class MagicSmartTracker : public SmartTracker
{
public:
    MagicSmartTracker();

    virtual ~MagicSmartTracker() = default;

    virtual void init(const cv::Mat& frame, const cv::Rect2d& roi) override;
    virtual void update(const cv::Mat& frame, cv::Rect2d& roi) override;
};
