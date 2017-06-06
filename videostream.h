#pragma once

#include <opencv2/core/core.hpp>

class VideoStream
{
public:
    virtual cv::Mat& nextFrame() = 0;

    VideoStream(const VideoStream&) = delete;
    VideoStream(VideoStream&&) = delete;

    VideoStream& operator=(const VideoStream&) = delete;
    VideoStream& operator=(VideoStream&&) = delete;

    virtual ~VideoStream() = default;
};
