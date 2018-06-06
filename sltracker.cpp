#include "sltracker.h"

#include <QDebug>

SLTracker::SLTracker(std::unique_ptr<VideoStream> video_stream) :
    m_VideoStream(std::move(video_stream)),
    m_IsFinished(false)
{
    m_Frame = m_VideoStream->nextFrame();
}

void SLTracker::update() {
    if (m_VideoStream->hasNext()) {
        m_Frame = m_VideoStream->nextFrame();
        size_t roi_index = 0;
        for (auto&& tracker : m_Trackers) {
            tracker->update(m_Frame, m_Rois[roi_index++]);
        }
        for (auto&& roi : m_Rois) {
            cv::rectangle(m_Frame, roi, cv::Scalar(0, 0, 255), 2, 1);
        }
    } else {
        m_IsFinished = true;
    }
}

QImage SLTracker::getFrameAsQImage() {
    cv::cvtColor(m_Frame, m_Frame, CV_BGR2RGB);
    QImage qimg((uchar*)m_Frame.data, m_Frame.cols, m_Frame.rows, m_Frame.step, QImage::Format_RGB888);
    return qimg;
}

bool SLTracker::isFinished() {
    return m_IsFinished;
}

double SLTracker::getPercentageOfVideo() {
    return m_VideoStream->getPercentageOfVideo();
}

void SLTracker::setRois(std::vector<cv::Rect2d> rois) {
    m_Rois = rois;
    for (auto&& roi : rois) {
        m_Trackers.push_back(cv::Tracker::create("KCF"));
        m_Trackers.back()->init(m_Frame, roi);
    }
}
