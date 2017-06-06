#pragma once

#include <vector>

#include <boost/filesystem.hpp>

#include <opencv2/opencv.hpp>

#include "videostream.h"

namespace bfs = boost::filesystem;

class VideoStreamFromImageSequence : public VideoStream
{
public:
    VideoStreamFromImageSequence(const std::string& path_str);

    VideoStreamFromImageSequence(const VideoStreamFromImageSequence&) = delete;
    VideoStreamFromImageSequence(VideoStreamFromImageSequence&&) = delete;

    VideoStreamFromImageSequence& operator=(const VideoStreamFromImageSequence&) = delete;
    VideoStreamFromImageSequence& operator=(VideoStreamFromImageSequence&&) = delete;

    virtual cv::Mat nextFrame() override;
    virtual bool hasNext() override;

private:
    bfs::directory_iterator m_Iter;
};
