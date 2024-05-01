#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "my_circle.h"
// #include "my_ellipse.h"
#include <QList>

struct my_point {
    int x;
    int y;
};
using point_t = struct my_point;

enum algorithms { CANONIC, PARAMETRIC, MIDPOINT, BRESENHAM, BUILT_IN };
using algorithm_t = enum algorithms;

QList<point_t> canonic_circle(circle_t &circle);

// QList<point_t> canonic_ellipse(ellipse_t &ellipse);

#endif // ALGORITHMS_H
