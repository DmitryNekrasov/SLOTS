#include "sltracker.h"

#include <QDebug>

SLTracker::SLTracker(std::unique_ptr<VideoStream> video_stream) :
    m_VideoStream(std::move(video_stream)),
    m_Tracker(cv::Tracker::create("KCF"))
{
    m_Frame = m_VideoStream->nextFrame();
    m_Roi = cv::selectROI("tracker", m_Frame);
    qDebug() << "width: " << m_Roi.width << ", height: " << m_Roi.height << "\n";

    m_Tracker->init(m_Frame, m_Roi);
}

void SLTracker::update() {
    if (m_VideoStream->hasNext()) {
        m_Frame = m_VideoStream->nextFrame();
        m_Tracker->update(m_Frame, m_Roi);
        cv::rectangle(m_Frame, m_Roi, cv::Scalar(0, 0, 255), 2, 1);

        cv::imshow("tracker", m_Frame);
    }
}
