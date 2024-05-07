#include "mainwindow.h"
#include "errorcodes.h"
#include "my_circle.h"
#include "my_ellipse.h"
#include "rendering.h"
#include "statistics.h"
#include "ui_mainwindow.h"

QColor BG_COLOR = QColor(255, 255, 255);
QColor FILL_COLOR = QColor(0, 0, 0);
render_t render_data;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    QGraphicsScene *scene = new QGraphicsScene(this);
    this->setWindowTitle("Лабораторная работа 4");
    qDebug() << "babah";

    ui->graphicsView->setScene(scene);

    render_data.scene = ui->graphicsView->scene();
    render_data.width = ui->graphicsView->width();
    render_data.height = ui->graphicsView->height();
}

MainWindow::~MainWindow() { delete ui; }

algorithm_t MainWindow::get_draw_alg() {
    ui->stackedWidget->setCurrentIndex(0);
    int ind = ui->comboBox->currentIndex();
    switch (ind) {
    case 0:
        return CANONIC;
    case 1:
        return PARAMETRIC;
    case 2:
        return MIDPOINT;
    case 3:
        return BRESENHAM;
    default:
        break;
    }
    return BUILT_IN;
}

void MainWindow::update_bg_color() {
    ui->stackedWidget->setCurrentIndex(0);
    ui->graphicsView->setBackgroundBrush(BG_COLOR);
}

void MainWindow::change_fill_color() {
    ui->stackedWidget->setCurrentIndex(0);
    ui->colorIndicator->setStyleSheet(QString("background-color: rgb(%1, %2, %3)")
                                          .arg(FILL_COLOR.red())
                                          .arg(FILL_COLOR.green())
                                          .arg(FILL_COLOR.blue()));
}

void MainWindow::on_btnBuildCircle_clicked() {
    error_t rc;
    circle_t circle = init_circle();

    build_circle_t data = {.centerX = ui->dspCenterX->value(),
                           .centerY = ui->dspCenterY->value(),
                           .radius = ui->dspCircleRadius->value(),
                           .color = FILL_COLOR};
    rc = build_circle(circle, data);

    if (rc)
        show_error(rc);
    else {
        render_data.algorithm = get_draw_alg();
        render_circle(render_data, circle);
    }
}

void MainWindow::on_btnBuildEllipse_clicked() {
    error_t rc;
    ellipse_t ellipse = init_ellipse();

    build_ellipse_t data = {.centerX = ui->dspCenterX->value(),
                            .centerY = ui->dspCenterY->value(),
                            .rX = ui->dspEllipseRadiusX->value(),
                            .rY = ui->dspEllipseRadiusY->value(),
                            .color = FILL_COLOR};
    rc = build_ellipse(ellipse, data);

    if (rc)
        show_error(rc);
    else {
        render_data.algorithm = get_draw_alg();
        render_ellipse(render_data, ellipse);
    }
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

void MainWindow::on_btnBgColorBLACK_clicked() {
    BG_COLOR = QColor(0, 0, 0);
    update_bg_color();
}

void MainWindow::on_btnBgColorWHITE_clicked() {
    BG_COLOR = QColor(255, 255, 255);
    update_bg_color();
}

void MainWindow::on_btnFillColorRED_clicked() {
    FILL_COLOR = QColor(139, 0, 0);
    change_fill_color();
}

void MainWindow::on_btnFillColorORANGE_clicked() {
    FILL_COLOR = QColor(255, 140, 0);
    change_fill_color();
}

void MainWindow::on_btnFillColorYELLOW_clicked() {
    FILL_COLOR = QColor(255, 215, 0);
    change_fill_color();
}

void MainWindow::on_btnFillColorGREEN_clicked() {
    FILL_COLOR = QColor(0, 100, 0);
    change_fill_color();
}

void MainWindow::on_btnFillColorBLACK_clicked() {
    FILL_COLOR = QColor(0, 0, 0);
    change_fill_color();
}

void MainWindow::on_btnFillColorWHITE_clicked() {
    FILL_COLOR = QColor(255, 255, 255);
    change_fill_color();
}

void MainWindow::on_btnBuildCircles_clicked() {
    error_t rc;
    circles_t circles = init_circles();

    build_circles_t data = {.step = ui->dspStep->value(),
                            .amount = ui->dspAmount->value(),
                            .centerX = ui->dspCenterX->value(),
                            .centerY = ui->dspCenterY->value(),
                            .basic_radius = ui->dspCirclesRadius->value(),
                            .color = FILL_COLOR};

    alloc_circles(circles, data.amount);
    rc = build_circles(circles, data);

    if (rc)
        show_error(rc);
    else {
        render_data.algorithm = get_draw_alg();
        render_circles(render_data, circles);
    }

    destroy_circles(circles);
}

void MainWindow::on_btnBuildEllipses_clicked() {
    error_t rc;
    ellipses_t ellipses = init_ellipses();

    build_ellipses_t data = {.step = ui->dspStep->value(),
                             .amount = ui->dspAmount->value(),
                             .centerX = ui->dspCenterX->value(),
                             .centerY = ui->dspCenterY->value(),
                             .basic_rX = ui->dspEllipsesRadiusX->value(),
                             .basic_rY = ui->dspEllipsesRadiusY->value(),
                             .color = FILL_COLOR};

    alloc_ellipses(ellipses, data.amount);
    rc = build_ellipses(ellipses, data);

    if (rc)
        show_error(rc);
    else {
        render_data.algorithm = get_draw_alg();
        render_ellipses(render_data, ellipses);
    }

    destroy_ellipses(ellipses);
}

void MainWindow::on_btnShowTimeStatCircles_clicked() {
    if (ui->horizontalLayout != NULL) {
        QLayoutItem *item;
        while ((item = ui->horizontalLayout->takeAt(0)) != NULL) {
            delete item->widget();
            delete item;
        }
    }

    ui->stackedWidget->setCurrentIndex(1);

    show_time_bar_circles(ui->horizontalLayout);
}

void MainWindow::on_btnShowTimeStatEllipses_clicked() {
    if (ui->horizontalLayout_2 != NULL) {
        QLayoutItem *item;
        while ((item = ui->horizontalLayout_2->takeAt(0)) != NULL) {
            delete item->widget();
            delete item;
        }
    }

    ui->stackedWidget->setCurrentIndex(2);

    show_time_bar_ellipses(ui->horizontalLayout_2);
}
