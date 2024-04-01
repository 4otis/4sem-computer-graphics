#ifndef DRAW_ALGORITHMS_H
#define DRAW_ALGORITHMS_H

#include "lines.h"
#include <QGraphicsScene>
#include <QList>
#include <QPainter>

enum draw_line_algs { DDA, BRESENHAM_INT, BRESENHAM_FLOAT, BRESENHAM_SMOOTH, WU, BUILT_IN };
using draw_algorithm_t = enum draw_line_algs;

struct render {
    QGraphicsScene *scene;
    QPainter *p;
    double width;
    double height;
    QColor bg_color;
    draw_algorithm_t draw_line_alg;
};
using render_t = struct render;

QList<point_t> draw_line_dda(line_t &line, bool stat_mode);
QList<point_t> draw_line_bresenham_int(line_t &line, bool stat_mode);
QList<point_t> draw_line_bresenham_float(line_t &line, bool stat_mode);
void draw_line_bresenham_smooth(line_t &line, bool stat_mode);
void draw_line_wu(line_t &line, bool stat_mode);

#endif // DRAW_ALGORITHMS_H
