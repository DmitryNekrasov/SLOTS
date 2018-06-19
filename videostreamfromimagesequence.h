#pragma once

#include <vector>

#include <boost/filesystem.hpp>

#include <opencv2/opencv.hpp>

#include "videostream.h"

namespace bfs = boost::filesystem;

/*!
 * Реализация интерфейса видеопотока
 * Видеопоток из последовательности изображений
 * \brief The VideoStream class
 * \author Dmitry Nekrasov
 * \version 0.1
 * \date Июнь 2018
 */
class VideoStreamFromImageSequence : public VideoStream
{
public:
    VideoStreamFromImageSequence(const std::string& path_str);

    VideoStreamFromImageSequence(const VideoStreamFromImageSequence&) = delete;
    VideoStreamFromImageSequence(VideoStreamFromImageSequence&&) = delete;

    VideoStreamFromImageSequence& operator=(const VideoStreamFromImageSequence&) = delete;
    VideoStreamFromImageSequence& operator=(VideoStreamFromImageSequence&&) = delete;

    ~VideoStreamFromImageSequence() override = default;

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
    std::vector<std::string> m_Pathways;
    std::vector<std::string>::iterator m_Iter;
};
