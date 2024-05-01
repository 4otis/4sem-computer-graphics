#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "rendering.h"
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
    algorithm_t get_draw_alg();

private slots:
    void on_btnBuildCircle_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
