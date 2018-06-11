#pragma once

#include <cassert>

#include <opencv2/opencv.hpp>

static constexpr int g_ClustersNumber = 15;
static float g_Data [g_ClustersNumber][3] = {
    {161.317504f, 127.223401f, 128.609333f},
    {142.922425f, 128.666965f, 127.532319f},
    {67.879757f, 127.721830f, 135.903311f},
    {92.705062f, 129.965717f, 137.399500f},
    {120.172257f, 128.279647f, 127.036493f},
    {195.470568f, 127.857070f, 129.345415f},
    {41.257102f, 130.059468f, 132.675336f},
    {12.014861f, 129.480555f, 127.064714f},
    {226.567086f, 127.567831f, 136.345727f},
    {154.664210f, 131.676606f, 156.481669f},
    {121.180447f, 137.020793f, 153.433743f},
    {87.042204f, 137.211742f, 98.614874f},
    {113.809537f, 106.577104f, 157.818094f},
    {81.083293f, 170.051905f, 148.904079f},
    {45.015485f, 138.543124f, 102.402528f}};

void limit(cv::Rect2d& rect, cv::Rect2d limit) {
    if (rect.x + rect.width > limit.x + limit.width) {
        rect.width = limit.x + limit.width - rect.x;
    }
    if (rect.y + rect.height > limit.y + limit.height) {
        rect.height = limit.y + limit.height - rect.y;
    }
    if (rect.x < limit.x) {
        rect.width -= (limit.x - rect.x);
        rect.x = limit.x;
    }
    if (rect.y < limit.y) {
        rect.height -= (limit.y - rect.y);
        rect.y = limit.y;
    }
    if (rect.width < 0) {
        rect.width = 0;
    }
    if (rect.height < 0) {
        rect.height = 0;
    }
}

cv::Rect2d getBorder(const cv::Rect2d& rect, const cv::Rect2d& limited) {
    cv::Rect2d result;
    result.x = limited.x - rect.x;
    result.y = limited.y - rect.y;
    result.width = (rect.x + rect.width) - (limited.x + limited.width);
    result.height = (rect.y + rect.height) - (limited.y + limited.height);
    assert(result.x >= 0 && result.y >= 0 && result.width >= 0 && result.height >= 0);
    return result;
}

cv::Mat getSubwindow(const cv::Mat& frame, const cv::Rect2d& rect, int border_type) {
    cv::Rect2d cut_rect = rect;
    limit(cut_rect, cv::Rect2d(0, 0, frame.cols, frame.rows));
    assert(cut_rect.width > 0 && cut_rect.height > 0);
    cv::Rect2d border = getBorder(rect, cut_rect);
    cv::Mat result = frame(cut_rect);
    if (border != cv::Rect2d(0, 0, 0, 0)) {
        cv::copyMakeBorder(result, result, int(border.y), int(border.height),
                           int(border.x), int(border.width), border_type);
    }
    return result;
}
