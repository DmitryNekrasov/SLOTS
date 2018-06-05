#ifndef PLAYERDIALOG_H
#define PLAYERDIALOG_H

#include <QDialog>
#include <QTimer>

namespace Ui {
class PlayerDialog;
}

class PlayerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PlayerDialog(QWidget *parent = 0);
    explicit PlayerDialog(QString path, QWidget *parent = 0);
    ~PlayerDialog();

private:
    Ui::PlayerDialog *ui;
    QString m_Path;
    QTimer *m_Timer;
    QImage *m_Image;

protected:
    void paintEvent(QPaintEvent*);

signals:
    void repaintSignal();

private slots:
    void mainExec();
    void on_playButton_clicked();
};

#endif // PLAYERDIALOG_H
