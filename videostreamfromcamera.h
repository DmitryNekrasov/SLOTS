#pragma once

#include <opencv2/opencv.hpp>

#include "videostream.h"

class VideoStreamFromCamera : public VideoStream
{
public:
    VideoStreamFromCamera();

    VideoStreamFromCamera(const VideoStreamFromCamera&) = delete;
    VideoStreamFromCamera(VideoStreamFromCamera&&) = delete;

    VideoStreamFromCamera& operator=(const VideoStreamFromCamera&) = delete;
    VideoStreamFromCamera& operator=(VideoStreamFromCamera&&) = delete;

    virtual ~VideoStreamFromCamera() override = default;

    virtual cv::Mat nextFrame() override;
    virtual bool hasNext() override;

private:
    cv::VideoCapture m_Capture;
};
