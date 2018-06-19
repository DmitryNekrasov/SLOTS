#pragma once

#include <array>

#include "smarttracker.h"

/*!
 * Реализация алгоритма трекинга с обработкой препятствий
 * \brief The MagicSmartTracker class
 * \author Dmitry Nekrasov
 * \version 0.1
 * \date Июнь 2018
 */
class MagicSmartTracker : public SmartTracker
{
public:
    MagicSmartTracker(bool scale_invariance);

    virtual ~MagicSmartTracker() = default;

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

    /*!
     * Реализация умной очереди - буфера для алгоритма обработки препятствий
     * \brief The SmartQueue class
     * \author Dmitry Nekrasov
     * \version 0.1
     * \date Июнь 2018
     */
    class SmartQueue
    {
    private:
        static constexpr size_t N = 10;
        std::array<cv::Mat, N> mats;
        size_t index;
        size_t counter;

    public:
        SmartQueue() :
            index(0),
            counter(0)
        {}

        /*!
         * Кладёт патч в очередь
         * \brief put
         * \param mat Патч
         */
        void put(cv::Mat mat) {
            mats[index] = mat;
            index = (index + 1) % N;
            if (counter < N) {
                counter++;
            }
        }

        /*!
         * Достаёт патч из очереди
         * \brief get
         * \return Патч
         */
        cv::Mat get() {
            return mats[(index + 1) % N];
        }

        /*!
         * Проверяет заполненность очереди
         * \brief isFull
         * \return true, если очередь заполнена, иначе false
         */
        bool isFull() {
            return counter == N;
        }
    };

private:
    double m_Lambda;
    double m_Padding;
    float m_OutputSigmaFactor;
    double m_InterpFactor;
    double m_Sigma;
    int m_CellSize;
    int m_TemplateSize;
    double m_ScaleStep;
    float m_ScaleWeight;

private:
    cv::Rect2d m_Roi;
    float m_Scale;
    cv::Size m_TemplateCvSize;
    int m_SizePatch[3];
    cv::Mat m_Hann;
    cv::Mat m_Features;
    cv::Mat m_GausseanPeak;
    cv::Mat m_AlphaMat;

    cv::Mat m_FirstObject;
    SmartQueue m_SmartQueue;

private:
    /*!
     * Возвращает патч с извлечёнными особенностями
     * \brief getFeatures
     * \param frame Кадр
     * \param initHanningMats Признак построения окна Ханна для сглаживания ядра
     * \param scale_adjust Регулирование масштаба
     * \return Патч с извлечёнными особенностями
     */
    cv::Mat getFeatures(const cv::Mat& frame, bool initHanningMats, float scale_adjust = 1.0f);

    /*!
     * Создаёт окно Ханна
     * Функция вызывается только на первом кадре
     * \brief createHanningMats
     */
    void createHanningMats();

    /*!
     * Создаёт пик Гаусса
     * Функция вызывается только на первом кадре
     * \brief createGaussianPeak
     * \param size_y Размер ядра по горизонтали
     * \param size_x Размер ядра по вертикали
     * \return Ядро
     */
    cv::Mat createGaussianPeak(int size_y, int size_x);

    /*!
     * Обучает трекер на одном изображении
     * \brief train
     * \param x Матрица - целевой объект трекинга
     * \param train_interp_factor Фактор линейной интерполяции
     */
    void train(cv::Mat x, double train_interp_factor);

    /*!
     * Вычисляет ядро Гаусса для всех относительных сдвигов между входными изображениями x1 и x2
     * \brief gaussianCorrelation
     * \param x1 Изображение x1
     * \param x2 Изображение x2
     * \return Ядро Гаусса
     */
    cv::Mat gaussianCorrelation(cv::Mat x1, cv::Mat x2);

    /*!
     * Обнаруживает объект на текущем кадре
     * \brief detect
     * \param z Целевой объект трекинга с предыдущего кадра
     * \param x Целевой объект трекинга с текущего кадра
     * \param peak_value оценка обнаружения
     * \return Положение объекта на кадре
     */
    cv::Point2f detect(cv::Mat z, cv::Mat x, float& peak_value);

    /*!
     * Вычисляет субпиксельный пик для одного измерения
     * Вспомогательный метод для метода обнаружения
     * Необходим для вычисления положения объекта на новом кадре
     * \brief subPixelPeak
     * \param left Положение слева
     * \param center Положение в центре
     * \param right Положение справа
     * \return Новое положением(смещение) объекта
     */
    float subPixelPeak(float left, float center, float right);
};
