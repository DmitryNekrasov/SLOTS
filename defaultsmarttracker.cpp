#include "defaultsmarttracker.h"

DefaultSmartTracker::DefaultSmartTracker() :
    m_Tracker(cv::Tracker::create("KCF"))
{}

void DefaultSmartTracker::init(const cv::Mat& frame, const cv::Rect2d& roi) {
    m_Tracker->init(frame, roi);
}

void DefaultSmartTracker::update(const cv::Mat& frame, cv::Rect2d& roi) {
    m_Tracker->update(frame, roi);
}
