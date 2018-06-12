#pragma once

#include <opencv2/opencv.hpp>

cv::Mat fftd(cv::Mat img, bool backwards = false);
cv::Mat complexDivision(cv::Mat a, cv::Mat b);
void rearrange(cv::Mat& img);
cv::Mat real(cv::Mat img);
