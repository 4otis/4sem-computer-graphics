#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "draw_algorithms.h"
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
    error_t render();
    draw_algorithm_t get_draw_line_alg();
    void update_bg_color();
    void change_fill_color();
    ~MainWindow();

private slots:

    void on_btnCreateLine_clicked();

    void on_btnBgColorRED_clicked();

    void on_btnBgColorORANGE_clicked();

    void on_btnBgColorYELLOW_clicked();

    void on_btnBgColorGREEN_clicked();

    void on_btnBgColorLIGHTBLUE_clicked();

    void on_btnBgColorWHITE_clicked();

    void on_btnLineColorRED_clicked();

    void on_btnLineColorORANGE_clicked();

    void on_btnLineColorYELLOW_clicked();

    void on_btnLineColorGREEN_clicked();

    void on_btnLineColorLIGHTBLUE_clicked();

    void on_btnLineColorBLACK_clicked();

    void on_btnCreateLines_clicked();

    void on_btnClearScreen_clicked();

    void on_btnTimeStat_clicked();

    void on_btnSteppingStat_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
