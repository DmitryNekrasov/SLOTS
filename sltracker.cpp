#include "sltracker.h"

#include <QDebug>

SLTracker::SLTracker(std::unique_ptr<VideoStream> video_stream) :
    m_VideoStream(std::move(video_stream)),
    m_Tracker(cv::Tracker::create("KCF")),
    m_IsFinished(false)
{
    m_Frame = m_VideoStream->nextFrame();
//    m_Roi = cv::selectROI("tracker", m_Frame);
    m_Roi = cv::Rect2d(241, 179, 14, 24);

    m_Tracker->init(m_Frame, m_Roi);
}

void SLTracker::update() {
    if (m_VideoStream->hasNext()) {
        m_Frame = m_VideoStream->nextFrame();
        m_Tracker->update(m_Frame, m_Roi);
        cv::rectangle(m_Frame, m_Roi, cv::Scalar(0, 0, 255), 2, 1);
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
