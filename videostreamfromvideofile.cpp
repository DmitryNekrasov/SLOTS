#include "videostreamfromvideofile.h"

#include <cassert>

VideoStreamFromVideoFile::VideoStreamFromVideoFile(const std::string& path)
    : m_Capture(path)
{
}

cv::Mat VideoStreamFromVideoFile::nextFrame() {
    cv::Mat frame;
    bool is_correct = m_Capture.retrieve(frame);
    assert(is_correct && "Incorrect retrieve.");
    return frame;
}

bool VideoStreamFromVideoFile::hasNext() {
    return m_Capture.grab();
}
