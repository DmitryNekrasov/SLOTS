#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_radioButton_Camera_toggled(bool checked);

    void on_pushButton_Open_clicked();

    void on_pushButton_LoadVideoStream_clicked();

private:
    Ui::MainWindow *ui;

private:
    void setEnableBrowse(bool value);
};

#endif // MAINWINDOW_H
