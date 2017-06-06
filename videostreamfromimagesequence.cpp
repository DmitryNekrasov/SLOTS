#include "videostreamfromimagesequence.h"

static bfs::directory_iterator g_EndIter;

VideoStreamFromImageSequence::VideoStreamFromImageSequence(const std::string& path_str)
    : m_Iter(bfs::path(path_str))
{
}

cv::Mat VideoStreamFromImageSequence::nextFrame() {
    auto current_file = m_Iter->path().string();
    ++m_Iter;
    auto frame = cv::imread(current_file);
    return frame;
}

bool VideoStreamFromImageSequence::hasNext() {
    return m_Iter != g_EndIter;
}
