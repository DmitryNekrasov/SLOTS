#include "fft.h"

cv::Mat fftd(cv::Mat img, bool backwards) {
    if (img.channels() == 1) {
        cv::Mat planes[] = {cv::Mat_<float> (img), cv::Mat_<float>::zeros(img.size())};
        cv::merge(planes, 2, img);
    }
    cv::dft(img, img, backwards ? (cv::DFT_INVERSE | cv::DFT_SCALE) : 0 );

    return img;
}

cv::Mat complexDivision(cv::Mat a, cv::Mat b) {
    //TODO
    return cv::Mat();
}
