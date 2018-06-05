#ifndef SLTRACKER_H
#define SLTRACKER_H

#include <memory>

#include <videostream.h>

#include <opencv2/tracking/tracking.hpp>

class SLTracker
{
public:
    SLTracker(std::unique_ptr<VideoStream> video_stream);

public:
    void update();

private:
    std::unique_ptr<VideoStream> m_VideoStream;
    cv::Ptr<cv::Tracker> m_Tracker;
    cv::Rect2d m_Roi;
    cv::Mat m_Frame;
};

#endif // SLTRACKER_H
