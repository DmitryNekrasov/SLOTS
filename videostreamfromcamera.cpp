#include "videostreamfromcamera.h"

VideoStreamFromCamera::VideoStreamFromCamera()
    : m_Capture(0)
{
}

cv::Mat VideoStreamFromCamera::nextFrame() {
    cv::Mat frame;
    m_Capture >> frame;
    return frame;
}

bool VideoStreamFromCamera::hasNext() {
    return true;
}

double VideoStreamFromCamera::getPercentageOfVideo() {
    return 0;
}
