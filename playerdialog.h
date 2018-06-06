#ifndef PLAYERDIALOG_H
#define PLAYERDIALOG_H

#include <QDialog>
#include <QMouseEvent>
#include <QTimer>

#include <sltracker.h>

#include <opencv2/opencv.hpp>

#include <vector>

namespace Ui {
class PlayerDialog;
}

class PlayerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PlayerDialog(QWidget *parent = 0);
    explicit PlayerDialog(QString path, QWidget *parent = 0);

    void mousePressEvent(QMouseEvent* ev) override;
    void mouseReleaseEvent(QMouseEvent* ev) override;
    void mouseMoveEvent(QMouseEvent*) override;

    ~PlayerDialog();

private:
    Ui::PlayerDialog *ui;
    QString m_Path;
    QTimer *m_Timer;
    QImage m_Image;

private:
    std::unique_ptr<SLTracker> m_SLTracker;
    bool m_VideoOnStart;
    std::vector<cv::Rect2i> m_Rects;

private:
    void refreshTracker();
    std::vector<cv::Rect2d> convertRectsToRois();

protected:
    void paintEvent(QPaintEvent*) override;

signals:
    void repaintSignal();

private slots:
    void mainExec();
    void on_playButton_clicked();
    void on_stopButton_clicked();
};

#endif // PLAYERDIALOG_H
