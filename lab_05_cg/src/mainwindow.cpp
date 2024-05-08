#include "mainwindow.h"
#include "errorcodes.h"
#include "ui_mainwindow.h"

QColor BG_COLOR = QColor(255, 255, 255);
QColor FILL_COLOR = QColor(0, 0, 0);
// render_t render_data;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    QGraphicsScene *scene = new QGraphicsScene(this);
    this->setWindowTitle("Лабораторная работа 5");

    ui->graphicsView->setScene(scene);

    // render_data.scene = ui->graphicsView->scene();
    // render_data.width = ui->graphicsView->width();
    // render_data.height = ui->graphicsView->height();
}

MainWindow::~MainWindow() { delete ui; }

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
