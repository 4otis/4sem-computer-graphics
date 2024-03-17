#ifndef GEOMETRY_H
#define GEOMETRY_H

struct point {
    double x;
    double y;
};
using point_t = struct point_t;

struct line {
    point_t p1;
    point_t p2;
};
using line_t = struct line;

#endif // GEOMETRY_H
