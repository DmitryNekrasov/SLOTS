#pragma once

#include <vector>

#include <videostream.h>

#include <QImage>

#include "smarttracker.h"

class TrackerRunner
{
public:
    TrackerRunner(std::unique_ptr<VideoStream> video_stream);

public:
    void update();
    QImage getFrameAsQImage();
    bool isFinished();
    double getPercentageOfVideo();
    void setRois(std::vector<cv::Rect2d> rois, int tracker_type);

private:
    std::unique_ptr<VideoStream> m_VideoStream;
    std::vector<std::unique_ptr<SmartTracker>> m_Trackers;
    std::vector<cv::Rect2d> m_Rois;
    cv::Mat m_Frame;
    bool m_IsFinished;
};
