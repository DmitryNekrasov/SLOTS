#pragma once

#include <opencv2/core/core.hpp>

/*!
 * Интерфейс видеопотока
 * \brief The VideoStream class
 * \author Dmitry Nekrasov
 * \version 0.1
 * \date Июнь 2018
 */
class VideoStream
{
public:
    VideoStream() {}

    VideoStream(const VideoStream&) = delete;
    VideoStream(VideoStream&&) = delete;

    VideoStream& operator=(const VideoStream&) = delete;
    VideoStream& operator=(VideoStream&&) = delete;

    virtual ~VideoStream() = default;

    /*!
     * Возвращает следующий кадр из видеопотока
     * \brief nextFrame
     * \return Кадр
     */
    virtual cv::Mat nextFrame() = 0;

    /*!
     * Проверяет наличие следующего кадра в видеопотоке
     * \brief hasNext
     * \return Признак наличия следующего кадра
     */
    virtual bool hasNext() = 0;

    /*!
     * Возвращает процент воспроизведённого видеопотока
     * \brief getPercentageOfVideo
     * \return Процент воспроизведённого видеопотока
     */
    virtual double getPercentageOfVideo() = 0;
};
