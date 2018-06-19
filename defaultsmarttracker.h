#pragma once

#include "smarttracker.h"

#include <string>

#include <opencv2/tracking/tracking.hpp>

/*!
 * Базовая реализация интерфейса трекинга
 * Обёртка над алгоритмами трекинга из OpenCV
 * \brief The DefaultSmartTracker class
 * \author Dmitry Nekrasov
 * \version 0.1
 * \date Июнь 2018
 */
class DefaultSmartTracker : public SmartTracker
{
public:
    DefaultSmartTracker(std::string algorithm_name);

    virtual ~DefaultSmartTracker() = default;

    /*!
     * Инициализирует трекер
     * \brief init
     * \param frame Кадр
     * \param roi Область интереса
     */
    virtual void init(const cv::Mat& frame, const cv::Rect2d& roi) override;

    /*!
     * Обновляет трекер
     * \brief update
     * \param frame Кадр
     * \param roi Область интереса
     */
    virtual void update(const cv::Mat& frame, cv::Rect2d& roi) override;

private:
    cv::Ptr<cv::Tracker> m_Tracker;
};
