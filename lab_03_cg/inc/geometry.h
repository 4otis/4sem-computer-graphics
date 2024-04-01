#ifndef GEOMETRY_H
#define GEOMETRY_H

struct point {
    double x;
    double y;
};
using point_t = struct point;

struct point_Af {
    double x;
    double y;
    float Af;
};
using point_Af_t = struct point_Af;

struct two_points {
    point_t p1;
    point_t p2;
};
using two_points_t = struct two_points;

struct my_line {
    point_t p1;
    point_t p2;
};
using line_t = struct my_line;

struct move {
    double x;
    double y;
};
using move_t = struct move;

struct rotate {
    double angle;
    point_t center_p;
};
using rotate_t = struct rotate;

void rotate_two_points(two_points_t &points, double angle);

void add_two_points_to_line(line_t &line, two_points_t &data);

#endif // GEOMETRY_H
