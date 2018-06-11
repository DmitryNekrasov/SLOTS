#include "trackerrunner.h"

#include "defaultsmarttracker.h"
#include "magicsmarttracker.h"

#include <QDebug>

TrackerRunner::TrackerRunner(std::unique_ptr<VideoStream> video_stream) :
    m_VideoStream(std::move(video_stream)),
    m_IsFinished(false)
{
    m_Frame = m_VideoStream->nextFrame();
}

void TrackerRunner::update() {
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

QImage TrackerRunner::getFrameAsQImage() {
    cv::cvtColor(m_Frame, m_Frame, CV_BGR2RGB);
    QImage qimg((uchar*)m_Frame.data, m_Frame.cols, m_Frame.rows, m_Frame.step, QImage::Format_RGB888);
    return qimg;
}

bool TrackerRunner::isFinished() {
    return m_IsFinished;
}

double TrackerRunner::getPercentageOfVideo() {
    return m_VideoStream->getPercentageOfVideo();
}

void TrackerRunner::setRois(std::vector<cv::Rect2d> rois) {
    m_Rois = rois;
    for (auto&& roi : rois) {
        m_Trackers.push_back(std::make_unique<MagicSmartTracker>());
        m_Trackers.back()->init(m_Frame, roi);
    }
}
