#pragma once

#include <string>

#include <opencv2/opencv.hpp>

#include "videostream.h"

class VideoStreamFromVideoFile : public VideoStream
{
public:
    VideoStreamFromVideoFile(const std::string& path);

    VideoStreamFromVideoFile(const VideoStreamFromVideoFile&) = delete;
    VideoStreamFromVideoFile(VideoStreamFromVideoFile&&) = delete;

    VideoStreamFromVideoFile& operator=(const VideoStreamFromVideoFile&) = delete;
    VideoStreamFromVideoFile& operator=(VideoStreamFromVideoFile&&) = delete;

    virtual ~VideoStreamFromVideoFile() override = default;

    virtual cv::Mat nextFrame() override;
    virtual bool hasNext() override;

private:
    cv::VideoCapture m_Capture;
};
