#pragma once

#include <opencv2/opencv.hpp>

/*!
 * Интерфейс трекера
 * \brief The SmartTracker class
 * \author Dmitry Nekrasov
 * \version 0.1
 * \date Июнь 2018
 */
class SmartTracker
{
public:
    SmartTracker() {}

    virtual ~SmartTracker() = default;

    /*!
     * Инициализирует трекер
     * \brief init
     * \param frame Кадр
     * \param roi Область интереса
     */
    virtual void init(const cv::Mat& frame, const cv::Rect2d& roi) = 0;

    /*!
     * Обновляет трекер
     * \brief update
     * \param frame Кадр
     * \param roi Область интереса
     */
    virtual void update(const cv::Mat& frame, cv::Rect2d& roi) = 0;
};
