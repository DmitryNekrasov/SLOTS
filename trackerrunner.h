#pragma once

#include <vector>

#include <videostream.h>

#include <QImage>

#include "smarttracker.h"

/*!
 * Класс для запуска заданного алгоритма трекинга на заданном видеопотоке
 * \brief The TrackerRunner class
 * \author Dmitry Nekrasov
 * \version 0.1
 * \date Июнь 2018
 */
class TrackerRunner
{
public:
    TrackerRunner(std::unique_ptr<VideoStream> video_stream);

public:
    /*!
     * Обновление трекеров
     * \brief update
     */
    void update();

    /*!
     * Возвращает кадр, сконвертированный в QImage
     * \brief getFrameAsQImage
     * \return Кадр в формате QImage
     */
    QImage getFrameAsQImage();

    /*!
     * Проверяет, остановлен ли видеопоток
     * \brief isFinished
     * \return Признак остановки
     */
    bool isFinished();

    /*!
     * Возвращает процент воспроизведённого видеопотока
     * \brief getPercentageOfVideo
     * \return Процент воспроизведённого видеопотока
     */
    double getPercentageOfVideo();

    /*!
     * Устанавливает параметры, необходимые трекерам
     * \brief setParams
     * \param rois Области интереса
     * \param tracker_type Тип трекера
     * \param scale_invariance Признак инвариантности к масштабу
     */
    void setParams(std::vector<cv::Rect2d> rois, int tracker_type, bool scale_invariance);

private:
    std::unique_ptr<VideoStream> m_VideoStream;
    std::vector<std::unique_ptr<SmartTracker>> m_Trackers;
    std::vector<cv::Rect2d> m_Rois;
    cv::Mat m_Frame;
    bool m_IsFinished;
};
