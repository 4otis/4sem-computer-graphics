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
    void update_bg_color();
    void change_fill_color();

private slots:
    void on_btnBuildCircle_clicked();
    void on_btnClearScreen_clicked();

    void on_btnBgColorRED_clicked();
    void on_btnBgColorORANGE_clicked();
    void on_btnBgColorYELLOW_clicked();
    void on_btnBgColorGREEN_clicked();
    void on_btnBgColorBLACK_clicked();
    void on_btnBgColorWHITE_clicked();

    void on_btnFillColorRED_clicked();
    void on_btnFillColorORANGE_clicked();
    void on_btnFillColorYELLOW_clicked();
    void on_btnFillColorGREEN_clicked();
    void on_btnFillColorBLACK_clicked();
    void on_btnFillColorWHITE_clicked();

    void on_btnBuildEllipse_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
