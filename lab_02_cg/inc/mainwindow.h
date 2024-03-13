#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "controller.h"
#include "errorcodes.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    error_t render();

    void on_MainWindow_destroyed();

    void on_btnBuild_clicked();

    void on_btnMove_clicked();

    void on_btnScale_clicked();

    void on_btnRotate_clicked();

    void on_showTask_triggered();

    void on_btnReset_clicked();

    void on_btnStepBack_clicked();

    void on_dspRotXcenter_valueChanged(double arg1);

    void on_dspRotYcenter_valueChanged(double arg1);

    void on_dspScaleXcenter_valueChanged(double arg1);

    void on_dspScaleYcenter_valueChanged(double arg1);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
