#ifndef LINES_H
#define LINES_H

#include <QColor>
#include <cstdlib>

#include "errorcodes.h"
#include "geometry.h"

struct my_lines {
    line_t *arr;
    size_t alen;
    QColor color;
};
using lines_t = struct my_lines;

struct build_line {
    point_t p1;
    point_t p2;
    QColor color;
};
using build_line_t = struct build_line;

struct build_lines {
    point_t p1;
    point_t p2;
    QColor color;
    double angle;
};
using build_lines_t = struct build_lines;

error_t create_line(lines_t &lines, build_line_t &data);
error_t create_lines(lines_t &lines, build_lines_t &data);
error_t change_lines_color(lines_t &lines, QColor &color);

#endif // LINES_H
