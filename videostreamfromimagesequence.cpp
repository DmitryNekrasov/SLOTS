#include "videostreamfromimagesequence.h"

#include <algorithm>

#include <QDebug>

VideoStreamFromImageSequence::VideoStreamFromImageSequence(const std::string& path_str) {
    bfs::path path(path_str);
    bfs::directory_iterator end_iter;
    for (bfs::directory_iterator dir_iter(path); dir_iter != end_iter; dir_iter++) {
        auto current_file = dir_iter->path().string();
        m_Pathways.push_back(current_file);
    }
    std::sort(m_Pathways.begin(), m_Pathways.end());
    m_Iter = m_Pathways.begin();
}

cv::Mat VideoStreamFromImageSequence::nextFrame() {
    auto current_file = *m_Iter;
    auto frame = cv::imread(current_file);
    ++m_Iter;
    return frame;
}

bool VideoStreamFromImageSequence::hasNext() {
    return m_Iter != m_Pathways.end();
}
