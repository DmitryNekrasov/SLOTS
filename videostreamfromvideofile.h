#pragma once

#include <string>

#include <opencv2/opencv.hpp>

#include "videostream.h"

/*!
 * Реализация интерфейса видеопотока
 * Видеопоток из видеофайла
 * \brief The VideoStream class
 * \author Dmitry Nekrasov
 * \version 0.1
 * \date Июнь 2018
 */
class VideoStreamFromVideoFile : public VideoStream
{
public:
    VideoStreamFromVideoFile(const std::string& path);

    VideoStreamFromVideoFile(const VideoStreamFromVideoFile&) = delete;
    VideoStreamFromVideoFile(VideoStreamFromVideoFile&&) = delete;

    VideoStreamFromVideoFile& operator=(const VideoStreamFromVideoFile&) = delete;
    VideoStreamFromVideoFile& operator=(VideoStreamFromVideoFile&&) = delete;

    virtual ~VideoStreamFromVideoFile() override = default;

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
