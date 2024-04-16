#include "mainwindow.h"
#include "QChartView"
#include "QLineSeries"
#include "controller.h"
#include "statistics.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QBarCategoryAxis>
#include <QBarSet>
#include <QHorizontalBarSeries>
#include <QValueAxis>

QColor BG_COLOR = QColor(255, 255, 255);
QColor FILL_COLOR = QColor(0, 0, 0);

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    QGraphicsScene *scene = new QGraphicsScene(this);
    this->setWindowTitle("Лабораторная работа 3");

    ui->graphicsView->setScene(scene);
}

MainWindow::~MainWindow() { delete ui; }

draw_algorithm_t MainWindow::get_draw_line_alg() {
    int ind = ui->comboBox->currentIndex();
    switch (ind) {
    case 0:
        return DDA;
    case 1:
        return BRESENHAM_INT;
    case 2:
        return BRESENHAM_FLOAT;
    case 3:
        return BRESENHAM_SMOOTH;
    case 4:
        return WU;
    default:
        break;
    }
    return BUILT_IN;
}

error_t MainWindow::render() {
    ui->stackedWidget->setCurrentIndex(0);

    request_t new_req;

    new_req.action = RENDER;

    new_req.render.scene = ui->graphicsView->scene();
    new_req.render.width = ui->graphicsView->width();
    new_req.render.height = ui->graphicsView->height();
    new_req.render.bg_color = BG_COLOR;
    new_req.render.draw_line_alg = get_draw_line_alg();

    return handle_action(new_req);
    return SUCCESS;
}

void MainWindow::on_btnCreateLine_clicked() {

    request_t new_req;

    new_req.action = CREATE_LINE;

    new_req.build_line.p1 = {.x = ui->dspBeginPointX->value(), .y = ui->dspBeginPointY->value()};
    new_req.build_line.p2 = {.x = ui->dspEndPointX->value(), .y = ui->dspEndPointY->value()};
    new_req.build_line.color = FILL_COLOR;

    error_t rc = handle_action(new_req);
    if (rc) {
        show_error(rc);
        if (rc == INVALID_LINE_COORDS_ERROR) {
            rc = render();
            if (rc)
                show_error(rc);
        }
    } else {
        rc = render();
        if (rc)
            show_error(rc);
    }
}

void MainWindow::on_btnCreateLines_clicked() {
    request_t new_req;

    new_req.action = CREATE_LINES;

    new_req.build_lines.p1 = {.x = ui->dspBeginPointX->value(), .y = ui->dspBeginPointY->value()};
    new_req.build_lines.p2 = {.x = ui->dspEndPointX->value(), .y = ui->dspEndPointY->value()};
    new_req.build_lines.color = FILL_COLOR;
    new_req.build_lines.angle = ui->dspAngle->value();

    error_t rc = handle_action(new_req);
    if (rc) {
        show_error(rc);
        if (rc == INVALID_LINE_COORDS_ERROR) {
            rc = render();
            if (rc)
                show_error(rc);
        }
    } else {
        rc = render();
        if (rc)
            show_error(rc);
    }
}

void MainWindow::update_bg_color() { ui->graphicsView->setBackgroundBrush(BG_COLOR); }

void MainWindow::change_fill_color() {
    request_t new_req;

    new_req.action = CHANGE_COLOR;

    new_req.new_color.color = FILL_COLOR;

    error_t rc = handle_action(new_req);
    if (rc)
        show_error(rc);
    else {
        rc = render();
        if (rc)
            show_error(rc);
    }
}

void MainWindow::on_btnTimeStat_clicked() {
    if (ui->horizontalLayout != NULL) {
        QLayoutItem *item;
        while ((item = ui->horizontalLayout->takeAt(0)) != NULL) {
            delete item->widget();
            delete item;
        }
    }

    ui->stackedWidget->setCurrentIndex(1);

    show_time_bar(ui->horizontalLayout, (size_t)ui->dspLineLenght->value());
}

void MainWindow::on_btnSteppingStat_clicked() {
    if (ui->gridLayout_3 != NULL) {
        QLayoutItem *item;
        while ((item = ui->gridLayout_3->takeAt(0)) != NULL) {
            delete item->widget();
            delete item;
        }
    }

    ui->stackedWidget->setCurrentIndex(2);

    show_step_bar(ui->gridLayout_3, (size_t)ui->dspLineLenght->value());
}

void MainWindow::on_btnClearScreen_clicked() { ui->graphicsView->scene()->clear(); }

void MainWindow::on_btnBgColorRED_clicked() {
    BG_COLOR = QColor(139, 0, 0);
    update_bg_color();
}

void MainWindow::on_btnBgColorORANGE_clicked() {
    BG_COLOR = QColor(255, 140, 0);
    update_bg_color();
}

void MainWindow::on_btnBgColorYELLOW_clicked() {
    BG_COLOR = QColor(255, 215, 0);
    update_bg_color();
}

void MainWindow::on_btnBgColorGREEN_clicked() {
    BG_COLOR = QColor(0, 100, 0);
    update_bg_color();
}

void MainWindow::on_btnBgColorLIGHTBLUE_clicked() {
    BG_COLOR = QColor(0, 0, 0);
    update_bg_color();
}

void MainWindow::on_btnBgColorWHITE_clicked() {
    BG_COLOR = QColor(255, 255, 255);
    update_bg_color();
}

void MainWindow::on_btnLineColorRED_clicked() {
    FILL_COLOR = QColor(0, 139, 139);
    change_fill_color();
}

void MainWindow::on_btnLineColorORANGE_clicked() {
    FILL_COLOR = QColor(0, 115, 255);
    change_fill_color();
}

void MainWindow::on_btnLineColorYELLOW_clicked() {
    FILL_COLOR = QColor(0, 40, 255);
    change_fill_color();
}

void MainWindow::on_btnLineColorGREEN_clicked() {
    FILL_COLOR = QColor(100, 0, 100);
    change_fill_color();
}

void MainWindow::on_btnLineColorLIGHTBLUE_clicked() {
    FILL_COLOR = QColor(180, 120, 70);
    change_fill_color();
}

void MainWindow::on_btnLineColorBLACK_clicked() {
    FILL_COLOR = QColor(0, 0, 0);
    change_fill_color();
}
