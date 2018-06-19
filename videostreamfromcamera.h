#pragma once

#include <opencv2/opencv.hpp>

#include "videostream.h"

/*!
 * Реализация интерфейса видеопотока
 * Видеопоток с камеры
 * \brief The VideoStream class
 * \author Dmitry Nekrasov
 * \version 0.1
 * \date Июнь 2018
 */
class VideoStreamFromCamera : public VideoStream
{
public:
    VideoStreamFromCamera();

    VideoStreamFromCamera(const VideoStreamFromCamera&) = delete;
    VideoStreamFromCamera(VideoStreamFromCamera&&) = delete;

    VideoStreamFromCamera& operator=(const VideoStreamFromCamera&) = delete;
    VideoStreamFromCamera& operator=(VideoStreamFromCamera&&) = delete;

    virtual ~VideoStreamFromCamera() override = default;

    /*!
     * Возвращает следующий кадр из видеопотока
     * \brief nextFrame
     * \return Кадр
     */
    virtual cv::Mat nextFrame() override;

    /*!
     * Проверяет наличие следующего кадра в видеопотоке
     * \brief hasNext
     * \return Признак наличия следующего кадра
     */
    virtual bool hasNext() override;

    /*!
     * Возвращает процент воспроизведённого видеопотока
     * \brief getPercentageOfVideo
     * \return Процент воспроизведённого видеопотока
     */
    virtual double getPercentageOfVideo() override;

private:
    cv::VideoCapture m_Capture;
};
