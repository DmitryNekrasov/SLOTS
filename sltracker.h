#ifndef SLTRACKER_H
#define SLTRACKER_H

#include <vector>

#include <videostream.h>

#include <opencv2/tracking/tracking.hpp>

#include <QImage>

class SLTracker
{
public:
    SLTracker(std::unique_ptr<VideoStream> video_stream);

public:
    void update();
    QImage getFrameAsQImage();
    bool isFinished();
    double getPercentageOfVideo();
    void setRois(std::vector<cv::Rect2d> rois);

private:
    std::unique_ptr<VideoStream> m_VideoStream;
    cv::Ptr<cv::Tracker> m_Tracker, m_Tracker2;
    std::vector<cv::Rect2d> m_Rois;
    cv::Mat m_Frame;
    bool m_IsFinished;
};

#endif // SLTRACKER_H
