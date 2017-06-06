#pragma once

#include <vector>

#include <opencv2/opencv.hpp>

#include "videostream.h"

class VideoStreamFromImageSequence : public VideoStream
{
public:
    VideoStreamFromImageSequence(const std::string& path);

    VideoStreamFromImageSequence(const VideoStreamFromImageSequence&) = delete;
    VideoStreamFromImageSequence(VideoStreamFromImageSequence&&) = delete;

    VideoStreamFromImageSequence& operator=(const VideoStreamFromImageSequence&) = delete;
    VideoStreamFromImageSequence& operator=(VideoStreamFromImageSequence&&) = delete;

    virtual cv::Mat& nextFrame() override;

private:
    using ImageSequenceT = std::vector<cv::Mat>;

    ImageSequenceT m_ImageSequence;
};
