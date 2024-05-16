#include "mainwindow.h"
#include "errorcodes.h"
#include "my_graphicsview.h"
#include "my_point.h"
#include "rendering.h"
#include "ui_mainwindow.h"

#include <QMouseEvent>
#include <QWidget>

QColor BG_COLOR = QColor(255, 255, 255);
QColor FILL_COLOR = QColor(0, 0, 0);
QString CUR_STR;

MyGraphicsView *graphicsView;
MainWindow *g_mainWindow = nullptr;

render_t render_data;
points_t POINTS;
#define INIT_POINTS_N 3

void MyGraphicsView::mousePressEvent(QMouseEvent *event) {
    int x = event->pos().x();
    int y = event->pos().y();

    error_t rc = SUCCESS;
    point_t new_point = {.x = x, .y = y};

    rc = add_point(POINTS, new_point);
    if (rc)
        show_error(rc);
    else {
        show_error(rc);
        rc = render_point(render_data, new_point, FILL_COLOR);
        if (rc)
            show_error(rc);
        else {
            if (POINTS.alen > 1)
                rc = render_edge(render_data, POINTS.arr[POINTS.alen - 2],
                                 POINTS.arr[POINTS.alen - 1]);
            if (rc)
                show_error(rc);
            else
                g_mainWindow->add_item_to_list(QString("%1. x: %2; y: %3;")
                                                   .arg(POINTS.alen)
                                                   .arg(POINTS.arr[POINTS.alen - 1].x)
                                                   .arg(POINTS.arr[POINTS.alen - 1].y));
        }
    }

    QGraphicsView::mousePressEvent(event);
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    g_mainWindow = this;

    graphicsView = new MyGraphicsView(this);
    graphicsView->setGeometry(QRect(1350, 470, 860, 640));
    graphicsView->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    graphicsView->setMinimumSize(QSize(860, 640));
    graphicsView->setMaximumSize(QSize(860, 640));
    graphicsView->setFont(QFont("Arial", 16));
    graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    graphicsView->setInteractive(false);
    graphicsView->setSceneRect(QRectF(0, 0, 860, 640));
    graphicsView->setAlignment(Qt::AlignLeading | Qt::AlignLeft | Qt::AlignTop);

    QGraphicsScene *scene = new QGraphicsScene(this);
    graphicsView->setScene(scene);
    this->setWindowTitle("Лабораторная работа 5");

    ui->verticalLayout->addWidget(graphicsView);

    render_data.scene = graphicsView->scene();
    render_data.width = graphicsView->width();
    render_data.height = graphicsView->height();
    render_data.pixmap = QPixmap(data.width, data.height);
    render_data.pixmap.fill(Qt::transparent);

    POINTS = init_points();
    error_t rc = alloc_points(POINTS, INIT_POINTS_N);
    if (rc)
        show_error(rc);
}

MainWindow::~MainWindow() {
    delete ui;
    destroy_points(POINTS);
}

void MainWindow::add_item_to_list(QString str) {
    // qDebug() << str;
    ui->listWidget->addItem(str);
}

void MainWindow::update_bg_color() { graphicsView->setBackgroundBrush(BG_COLOR); }

void MainWindow::change_fill_color() {
    ui->colorIndicator->setStyleSheet(QString("background-color: rgb(%1, %2, %3)")
                                          .arg(FILL_COLOR.red())
                                          .arg(FILL_COLOR.green())
                                          .arg(FILL_COLOR.blue()));
}

void MainWindow::on_btnClearScreen_clicked() {
    render_data.pixmap = QPixmap(data.width, data.height);
    render_data.pixmap.fill(Qt::transparent);
    graphicsView->scene()->clear();
    ui->listWidget->clear();
    POINTS.alen = 0;
}

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

void MainWindow::on_btnBuildPoint_clicked() {
    error_t rc = SUCCESS;
    point_t new_point = {.x = ui->dspCoordX->value(), .y = ui->dspCoordY->value()};

    rc = add_point(POINTS, new_point);
    if (rc)
        show_error(rc);
    else {
        show_error(rc);
        rc = render_point(render_data, new_point, FILL_COLOR);
        if (rc)
            show_error(rc);
        else {
            if (POINTS.alen > 1)
                rc = render_edge(render_data, POINTS.arr[POINTS.alen - 2],
                                 POINTS.arr[POINTS.alen - 1]);
            if (rc)
                show_error(rc);
            ui->listWidget->addItem(QString("%1. x: %2; y: %3;")
                                        .arg(POINTS.alen)
                                        .arg(POINTS.arr[POINTS.alen - 1].x)
                                        .arg(POINTS.arr[POINTS.alen - 1].y));
        }
    }
}

void MainWindow::on_btnConnectAllPoints_clicked() {
    error_t rc = SUCCESS;
    if (POINTS.alen > 3)
        rc = render_all_connecting_edges(render_data, POINTS);
}

void MainWindow::on_btnFill_clicked() {
    error_t rc = SUCCESS;
    if (POINTS.alen > 3) {
        edges_t edges = get_edges_from_points(POINTS);
        rc = render_fill_by_edges(render_data, edges);
    }
}
