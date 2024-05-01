#include "mainwindow.h"
#include "errorcodes.h"
#include "my_circle.h"
#include "rendering.h"
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
