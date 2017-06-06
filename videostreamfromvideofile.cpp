#include "videostreamfromvideofile.h"

VideoStreamFromVideoFile::VideoStreamFromVideoFile(const std::string& path)
    : VideoStream()
    , m_Capture(path)
{
}

cv::Mat& VideoStreamFromVideoFile::nextFrame() {
    m_Capture >> m_Frame;
    return m_Frame;
}
