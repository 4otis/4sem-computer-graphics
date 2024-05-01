#ifndef MY_CIRCLE_H
#define MY_CIRCLE_H

#include "errorcodes.h"
#include <QColor>
#include <cstdbool>

struct my_circle {
    int centerX;
    int centerY;
    int radius;
    QColor color;
};
using circle_t = struct my_circle;

struct build_circle {
    int centerX;
    int centerY;
    int radius;
    QColor color;
};
using build_circle_t = struct build_circle;

struct my_circles {
    circle_t *arr;
    size_t alen;
    QColor color;
};
using circles_t = struct my_circles;

struct build_circles {
    size_t step;
    size_t amount;
    int centerX;
    int centerY;
    int basic_radius;
    QColor color;
};
using build_circles_t = struct build_circles;

circle_t init_circle();
bool is_circle_empty(circle_t &circle);
error_t build_circle(circle_t &circle, build_circle_t &data);

error_t alloc_circles(circles_t &circles, size_t amount);
void destroy_circles(circles_t &circles);
circles_t init_circles();

bool is_circles_empty(circles_t &circles);
error_t build_circles(circles_t &circles, build_circles_t &data);

#endif // MY_CIRCLE_H
