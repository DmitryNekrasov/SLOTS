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

void rearrange(cv::Mat& img) {
    int cx = img.cols / 2;
    int cy = img.rows / 2;

    cv::Mat q0(img, cv::Rect(0, 0, cx, cy));
    cv::Mat q1(img, cv::Rect(cx, 0, cx, cy));
    cv::Mat q2(img, cv::Rect(0, cy, cx, cy));
    cv::Mat q3(img, cv::Rect(cx, cy, cx, cy));

    cv::Mat tmp;
    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);
    q1.copyTo(tmp);
    q2.copyTo(q1);
    tmp.copyTo(q2);
}

cv::Mat real(cv::Mat img) {
    std::vector<cv::Mat> planes;
    cv::split(img, planes);
    return planes[0];
}
