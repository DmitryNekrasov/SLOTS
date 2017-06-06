#include "videostreamfromvideofile.h"

#include <cassert>

VideoStreamFromVideoFile::VideoStreamFromVideoFile(const std::string& path)
    : m_Capture(path)
{
}

cv::Mat& VideoStreamFromVideoFile::nextFrame() {
    bool is_correct = m_Capture.retrieve(m_Frame);
    assert(is_correct && "Incorrect retrieve.");
    return m_Frame;
}

bool VideoStreamFromVideoFile::hasNext() {
    return m_Capture.grab();
}
