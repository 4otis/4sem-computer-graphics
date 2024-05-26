#ifndef DRAW_ALGORITHMS_H
#define DRAW_ALGORITHMS_H

#include "my_circle.h"
#include "my_ellipse.h"
#include <QList>

struct my_point {
    double x;
    double y;
};
using point_t = struct my_point;

enum algorithms { CANONIC, PARAMETRIC, MIDPOINT, BRESENHAM, BUILT_IN };
using algorithm_t = enum algorithms;

QList<point_t> canonic_circle(circle_t &circle);
QList<point_t> canonic_ellipse(ellipse_t &ellipse);

QList<point_t> param_circle(circle_t &circle);
QList<point_t> param_ellipse(ellipse_t &ellipse);

QList<point_t> midpoint_circle(circle_t &circle);
QList<point_t> midpoint_ellipse(ellipse_t &ellipse);

QList<point_t> bresenham_circle(circle_t &circle);
QList<point_t> bresenham_ellipse(ellipse_t &ellipse);

#endif // DRAW_ALGORITHMS_H
