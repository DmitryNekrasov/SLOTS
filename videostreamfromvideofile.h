#pragma once

#include <string>

#include <opencv2/opencv.hpp>

#include "videostream.h"

class VideoStreamFromVideoFile : public VideoStream
{
public:
    VideoStreamFromVideoFile(const std::string& path);

    virtual cv::Mat& nextFrame() override;

private:
    cv::VideoCapture m_Capture;
    cv::Mat m_Frame;
};
