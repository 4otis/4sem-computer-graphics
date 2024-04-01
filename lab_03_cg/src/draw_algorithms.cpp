#include "draw_algorithms.h"
#include <QDebug>
#include <cmath>

QList<point_t> draw_line_dda(line_t &line, bool stat_mode) {
    QList<point_t> points_list;
    point_t point;

    float x1 = line.p1.x, y1 = line.p1.y;
    float x2 = line.p2.x, y2 = line.p2.y;

    int dx = (int)x2 - x1;
    int dy = (int)y2 - y1;

    int step = (fabs(dx) > fabs(dy)) ? fabs(dx) : fabs(dy);

    float x_inc = (float)dx / step;
    float y_inc = (float)dy / step;

    if (!stat_mode) {
        for (int i = 0; i < step; i++) {
            point = {.x = round(x1), .y = round(y1)};
            points_list.push_back(point);
            // data.p->drawPoint(round(x1), round(y1));
            x1 += x_inc;
            y1 += y_inc;
        }
    } else
        for (int i = 0; i < step; i++) {
            point = {.x = round(x1), .y = round(y1)};
            x1 += x_inc;
            y1 += y_inc;
        }

    return points_list;
}

QList<point_t> draw_line_bresenham_int(line_t &line, bool stat_mode) {
    QList<point_t> points_list;
    point_t point;

    int x1 = (int)line.p1.x, y1 = (int)line.p1.y;
    int x2 = (int)line.p2.x, y2 = (int)line.p2.y;

    const int deltaX = fabs(x2 - x1);
    const int deltaY = fabs(y2 - y1);

    const int signX = x1 < x2 ? 1 : -1;
    const int signY = y1 < y2 ? 1 : -1;
    int error = deltaX - deltaY;

    if (!stat_mode) {
        while (x1 != x2 || y1 != y2) {
            point = {.x = (int)x1, .y = (int)y1};
            points_list.push_back(point);
            // data.p->drawPoint((int)x1, (int)y1);
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
    } else
        while (x1 != x2 || y1 != y2) {
            point = {.x = (int)x1, .y = (int)y1};
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

    return points_list;
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

    if (!deltaX)
        signX = 0;
    if (!deltaY)
        signY = 0;

    float intensivity = 100;
    int was_swaped;

    float m = (float)deltaY / deltaX;
    if (m > 1) {
        m = (float)1 / (float)m;

        was_swaped = 1;
    } else
        was_swaped = 0;

    m *= intensivity;
    float w = intensivity - m;
    float e = 0.5;

    // drawpoint intens = m / 2
    int x = x1, y = y1;
    data.p->drawPoint(x, y);
    while (x != x2 || y != y2) {
        qDebug() << "e:" << e << "w:" << w << "m:" << m;

        if (e < w) {
            if (was_swaped) // dx < dy
                y += signY;
            else
                x += signX;
            e += m;
        } else {
            x += signX;
            y += signY;
            e -= w;
        }
        // drawpoint intens = e
        data.p->drawPoint(x, y);
    }
}

void draw_line_wu(render_t &data, line_t &line);
