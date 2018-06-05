#pragma once

#include <opencv2/core/core.hpp>

class VideoStream
{
public:
    VideoStream() {}

    VideoStream(const VideoStream&) = delete;
    VideoStream(VideoStream&&) = delete;

    VideoStream& operator=(const VideoStream&) = delete;
    VideoStream& operator=(VideoStream&&) = delete;

    virtual ~VideoStream() = default;

    virtual cv::Mat nextFrame() = 0;
    virtual bool hasNext() = 0;
    virtual double getPercentageOfVideo() = 0;
};
