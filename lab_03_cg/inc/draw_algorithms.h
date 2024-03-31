#ifndef DRAW_ALGORITHMS_H
#define DRAW_ALGORITHMS_H

#include "lines.h"
#include <QGraphicsScene>
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

void draw_line_dda(render_t &data, line_t &line);
void draw_line_bresenham_int(render_t &data, line_t &line);
void draw_line_bresenham_float(render_t &data, line_t &line);
void draw_line_bresenham_smooth(render_t &data, line_t &line);
void draw_line_wu(render_t &data, line_t &line);

#endif // DRAW_ALGORITHMS_H
