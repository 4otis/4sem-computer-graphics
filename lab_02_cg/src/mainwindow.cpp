#include "QDebug"
#include "QElapsedTimer"
#include "QFileDialog"

#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace std;

QGraphicsScene *scene;

float **points_coordinates;

void delay(int ms) {
    QElapsedTimer et;
    et.start();
    while (true) {
        qApp->processEvents();
        if (et.elapsed() > ms)
            break;
    }
}

error_t MainWindow::render() {
    request_t new_req;

    new_req.action = RENDER;

    new_req.render_data = {.scene = ui->graphicsView->scene(), .width = 1000, .height = 1000};

    new_req.render_data.rotate_center = {.x = ui->dspRotXcenter->value(), .y = ui->dspRotYcenter->value()};

    new_req.render_data.scale_center = {.x = ui->dspScaleXcenter->value(), .y = ui->dspScaleYcenter->value()};

    return action_handler(new_req);
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    QGraphicsScene *scene = new QGraphicsScene(this);

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setStyleSheet("QGraphicsView {background-color: white}");
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_MainWindow_destroyed() { delete scene; }

void MainWindow::on_btnBuild_clicked() {
    request_t new_req;

    new_req.action = BUILD;

    new_req.build_data.a = ui->dspBuildA->value();
    new_req.build_data.b = ui->dspBuildB->value();
    new_req.build_data.angle = 0;
    error_t rc = action_handler(new_req);
    if (rc)
        show_error(rc);
    else {
        rc = render();
        if (rc)
            show_error(rc);
    }
}

void MainWindow::on_btnMove_clicked() {
    request_t new_req;

    new_req.action = MOVE;

    new_req.move_data.x = ui->dspMoveX->value();
    new_req.move_data.y = ui->dspMoveY->value();

    error_t rc = action_handler(new_req);
    if (rc)
        show_error(rc);
    else {
        rc = render();
        if (rc)
            show_error(rc);
    }
}

void MainWindow::on_btnRotate_clicked() {
    request_t new_req;

    new_req.action = ROTATE;

    new_req.rotate_data.angle_OZ_in_degrees = ui->dspRotZ->value();

    new_req.rotate_data.center_p.x = ui->dspRotXcenter->value();
    new_req.rotate_data.center_p.y = ui->dspRotYcenter->value();

    error_t rc = action_handler(new_req);
    if (rc)
        show_error(rc);
    else {
        rc = render();
        if (rc)
            show_error(rc);
    }
}

void MainWindow::on_btnScale_clicked() {
    request_t new_req;

    new_req.action = SCALE;

    new_req.scale_data.x_scale = ui->dspScaleX->value();
    new_req.scale_data.y_scale = ui->dspScaleY->value();

    new_req.scale_data.center_p.x = ui->dspScaleXcenter->value();
    new_req.scale_data.center_p.y = ui->dspScaleYcenter->value();

    error_t rc = action_handler(new_req);
    if (rc)
        show_error(rc);
    else {
        rc = render();
        if (rc)
            show_error(rc);
    }
}

void MainWindow::on_btnReset_clicked() {
    request_t new_req;

    new_req.action = RESET;

    error_t rc = action_handler(new_req);
    if (rc)
        show_error(rc);
    else {
        rc = render();
        if (rc)
            show_error(rc);
    }
}

void MainWindow::on_btnStepBack_clicked() {
    request_t new_req;

    new_req.action = PREV;

    error_t rc = action_handler(new_req);
    if (rc)
        show_error(rc);
    else {
        rc = render();
        if (rc)
            show_error(rc);
    }
}

void MainWindow::on_showTask_triggered() {
    QMessageBox::information(0, "Условие лабараторной",
                             "Нарисовать исходный рисунок (эпициклоиду),\n"
                             "затем его переместить, промасштабировать и повернуть.\n\n"
                             "Уравнение эпициклоиды:\n"
                             "x = (R + r) * cos(t) - R * cos((R + r) * t / a)\n"
                             "y = (R + r) * sin(t) - R * sin((R + r) * t / a)\n"
                             "где R/r = m/n - положительные числа,"
                             "t = [0, 2pi * n]");
}

void MainWindow::on_dspRotXcenter_valueChanged(double arg1) {
    error_t rc = render();
    if (rc)
        show_error(rc);
}

void MainWindow::on_dspRotYcenter_valueChanged(double arg1) {
    error_t rc = render();
    if (rc)
        show_error(rc);
}

void MainWindow::on_dspScaleXcenter_valueChanged(double arg1) {
    error_t rc = render();
    if (rc)
        show_error(rc);
}

void MainWindow::on_dspScaleYcenter_valueChanged(double arg1) {
    error_t rc = render();
    if (rc)
        show_error(rc);
}
