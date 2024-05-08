#ifndef MY_POINT_H
#define MY_POINT_H

#include <QColor>
#include <cstdbool>
#include <cstdlib>

#include "errorcodes.h"

struct my_point {
    int x;
    int y;
};
using point_t = struct my_point;

struct my_points {
    point_t *arr;
    size_t alen;
    size_t capacity;
    QColor color;
};
using points_t = struct my_points;

points_t init_points();

error_t alloc_points(points_t &points, size_t amount);
void destroy_points(points_t &points);

bool is_points_empty(points_t &points);
error_t add_point(points_t &points, point_t &point);

#endif // MY_POINT_H
