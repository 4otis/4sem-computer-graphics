#include "draw_algorithms.h"
#include <QDebug>
#include <cmath>

void draw_line_dda(render_t &data, line_t &line, QColor &color) {
    float x1 = line.p1.x, y1 = line.p1.y;
    float x2 = line.p2.x, y2 = line.p2.y;

    int dx = (int)x2 - x1;
    int dy = (int)y2 - y1;

    int step = (fabs(dx) > fabs(dy)) ? fabs(dx) : fabs(dy);

    float x_inc = (float)dx / step;
    float y_inc = (float)dy / step;

    for (int i = 0; i < step; i++) {
        data.scene->addLine((float)round(x1), (float)round(y1), (float)round(x1), (float)round(y1), color);
        qDebug() << round(x1) << round(y1);
        x1 += x_inc;
        y1 += y_inc;
    }
}

void draw_line_bresenham_int(render_t &data, line_t &line, QColor &color) {
    float x1 = line.p1.x, y1 = line.p1.y;
    float x2 = line.p2.x, y2 = line.p2.y;

    const int deltaX = fabs(x2 - x1);
    const int deltaY = fabs(y2 - y1);

    const int signX = x1 < x2 ? 1 : -1;
    const int signY = y1 < y2 ? 1 : -1;
    int error = deltaX - deltaY;

    data.scene->addLine((float)round(x1), (float)round(y1), (float)round(x1), (float)round(y1), color);
    while (x1 != x2 || y1 != y2) {
        data.scene->addLine((float)round(x1), (float)round(y1), (float)round(x1), (float)round(y1), color);
        int error2 = error * 2;
        if (error2 > -deltaY) {
            error -= deltaY;
            x1 += signX;
        }
        if (error2 < deltaX) {
            error += deltaX;
            y1 += signY;
        }
    }
}

void draw_line_bresenham_float(render_t &data, line_t &line, QColor &color);
void draw_line_bresenham_modified(render_t &data, line_t &line, QColor &color);
void draw_line_wu(render_t &data, line_t &line, QColor &color);
