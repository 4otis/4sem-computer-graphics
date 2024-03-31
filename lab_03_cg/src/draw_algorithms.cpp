#include "draw_algorithms.h"
#include <QDebug>
#include <cmath>

void draw_line_dda(render_t &data, line_t &line) {
    float x1 = line.p1.x, y1 = line.p1.y;
    float x2 = line.p2.x, y2 = line.p2.y;

    int dx = (int)x2 - x1;
    int dy = (int)y2 - y1;

    int step = (fabs(dx) > fabs(dy)) ? fabs(dx) : fabs(dy);

    float x_inc = (float)dx / step;
    float y_inc = (float)dy / step;

    for (int i = 0; i < step; i++) {
        data.p->drawPoint(round(x1), round(y1));
        // qDebug() << round(x1) << round(y1);
        x1 += x_inc;
        y1 += y_inc;
    }
}

void draw_line_bresenham_int(render_t &data, line_t &line) {
    int x1 = (int)line.p1.x, y1 = (int)line.p1.y;
    int x2 = (int)line.p2.x, y2 = (int)line.p2.y;

    const int deltaX = fabs(x2 - x1);
    const int deltaY = fabs(y2 - y1);

    const int signX = x1 < x2 ? 1 : -1;
    const int signY = y1 < y2 ? 1 : -1;
    int error = deltaX - deltaY;

    while (x1 != x2 || y1 != y2) {
        data.p->drawPoint((int)x1, (int)y1);
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

void draw_line_bresenham_float(render_t &data, line_t &line) {
    float x1 = line.p1.x, y1 = line.p1.y;
    float x2 = line.p2.x, y2 = line.p2.y;

    float dx = x2 - x1;
    float dy = y2 - y1;

    float steps = std::max(fabs(dx), fabs(dy));

    float xIncrement = dx / steps;
    float yIncrement = dy / steps;
    float x = x1;
    float y = y1;

    for (int i = 0; i <= steps; i++) {
        data.p->drawPoint(round(x), round(y));
        x += xIncrement;
        y += yIncrement;
    }
}
void draw_line_bresenham_smooth(render_t &data, line_t &line) {

    int x1 = (int)line.p1.x, y1 = (int)line.p1.y;
    int x2 = (int)line.p2.x, y2 = (int)line.p2.y;

    int deltaX = fabs(x2 - x1);
    int deltaY = fabs(y2 - y1);
    qDebug() << "dX:" << deltaX << "dY:" << deltaY;

    int signX = x1 < x2 ? 1 : -1;
    int signY = y1 < y2 ? 1 : -1;

    float intensivity = 255;
    int dx_less_than_dy;

    float tg = (float)deltaY / deltaX;

    if (tg > 1) {
        int tmp = deltaX;
        deltaX = deltaY;
        deltaY = tmp;

        dx_less_than_dy = 1;
    } else
        dx_less_than_dy = 0;

    tg *= intensivity;
    float cur_intensivity = (float)intensivity / 2;
    qDebug() << "e:" << cur_intensivity << "treshold:" << tg;
    float treshold_value = intensivity - tg;

    int x = x1, y = y1;
    // size_t steps = 0;

    data.p->drawPoint(x, y);
    while (x != x2 || y != y2) {
        // qDebug() << x << y;
        // qDebug() << "e:" << cur_intensivity << "treshold:" << treshold_value;

        if (cur_intensivity <= treshold_value) {
            if (dx_less_than_dy == 0)
                x += signX;
            else
                y += signY;

            cur_intensivity += tg;
        } else {
            x += signX;
            y += signY;
            cur_intensivity -= treshold_value;
        }
        data.p->drawPoint(x, y);
    }
}

void draw_line_wu(render_t &data, line_t &line);