#include "sltracker.h"

#include <QDebug>

SLTracker::SLTracker(std::unique_ptr<VideoStream> video_stream) :
    m_VideoStream(std::move(video_stream)),
    m_Tracker(cv::Tracker::create("KCF")),
    m_Tracker2(cv::Tracker::create("KCF")),
    m_IsFinished(false)
{
    m_Frame = m_VideoStream->nextFrame();
}

void SLTracker::update() {
    if (m_VideoStream->hasNext()) {
        m_Frame = m_VideoStream->nextFrame();
        cv::Mat new_frame(m_Frame);
        m_Tracker->update(m_Frame, m_Roi);
        m_Tracker2->update(new_frame, m_Roi2);
        cv::rectangle(m_Frame, m_Roi, cv::Scalar(0, 0, 255), 2, 1);
        cv::rectangle(m_Frame, m_Roi2, cv::Scalar(0, 0, 255), 2, 1);
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

void SLTracker::setRoi(cv::Rect2d roi) {
    m_Roi = roi;
    m_Tracker->init(m_Frame, m_Roi);
    m_Roi2 = cv::Rect2d(241, 179, 14, 25);
    m_Tracker2->init(m_Frame, m_Roi2);
}
