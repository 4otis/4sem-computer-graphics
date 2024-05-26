#ifndef MY_ELLIPSE_H
#define MY_ELLIPSE_H

#include "errorcodes.h"
#include <QColor>
#include <cstdbool>

struct my_ellipse {
    int centerX;
    int centerY;
    int rX;
    int rY;
    QColor color;
};
using ellipse_t = struct my_ellipse;

struct build_ellipse {
    int centerX;
    int centerY;
    int rX;
    int rY;
    QColor color;
};
using build_ellipse_t = struct build_ellipse;

struct my_ellipses {
    ellipse_t *arr;
    size_t alen;
};
using ellipses_t = struct my_ellipses;

struct build_ellipses {
    size_t step;
    size_t amount;
    int centerX;
    int centerY;
    int basic_rX;
    int basic_rY;
    QColor color;
};
using build_ellipses_t = struct build_ellipses;

ellipse_t init_ellipse();
bool is_ellipse_empty(ellipse_t &ellipse);
error_t build_ellipse(ellipse_t &ellipse, build_ellipse_t &data);

error_t alloc_ellipses(ellipses_t &ellipses, size_t amount);
void destroy_ellipses(ellipses_t &ellipses);
ellipses_t init_ellipses();

bool is_ellipses_empty(ellipses_t &ellipses);
error_t build_ellipses(ellipses_t &ellipses, build_ellipses_t &data);

#endif // MY_ELLIPSE_H
