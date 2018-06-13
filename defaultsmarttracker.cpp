#include "defaultsmarttracker.h"

DefaultSmartTracker::DefaultSmartTracker(std::string algorithm_name) :
    m_Tracker(cv::Tracker::create(algorithm_name))
{}

void DefaultSmartTracker::init(const cv::Mat& frame, const cv::Rect2d& roi) {
    m_Tracker->init(frame, roi);
}

void DefaultSmartTracker::update(const cv::Mat& frame, cv::Rect2d& roi) {
    m_Tracker->update(frame, roi);
}
