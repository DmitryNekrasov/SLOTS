#include "videostreamfromvideofile.h"

VideoStreamFromVideoFile::VideoStreamFromVideoFile(const std::string& path)
    : m_Capture(path)
{
}

cv::Mat& VideoStreamFromVideoFile::nextFrame() {
    m_Capture >> m_Frame;
    return m_Frame;
}
