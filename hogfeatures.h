#pragma once

#include <opencv2/opencv.hpp>

typedef struct {
    int size_x;
    int size_y;
    int features_number;
    float* map;
} HogFeatures;

void getHogFeatures(const IplImage* image, int k, HogFeatures** hogFeatures);
