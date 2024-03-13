#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <cstdio>
#include <cstdlib>
#include <errorcodes.h>
#include <stdlib.h>

struct point {
    double x;
    double y;
};
using point_t = struct point;

struct build {
    double a;
    double b;
    double angle;
};
using build_t = struct build;

struct move {
    double x;
    double y;
};
using move_t = struct move;

struct rotate {
    double angle_OZ_in_degrees;
    point_t center_p;
};
using rotate_t = struct rotate;

struct scale {
    double x_scale;
    double y_scale;
    point_t center_p;
};
using scale_t = struct scale;

point_t *alloc_points(size_t &alen);
void destroy_points(point_t *arr);

size_t get_amount_of_rotations_for_epicycloid(double a, double b);
error_t calc_all_points(build_t &params, point_t *arr, size_t &alen);

error_t move_all_points(move_t &params, point_t *arr, size_t &alen);
error_t rotate_all_points(rotate_t &params, point_t *arr, size_t &alen);
error_t scale_all_points(scale_t &params, point_t *arr, size_t &alen);

point_t &get_max_y_point(point_t *arr, size_t &alen);
point_t &get_min_y_point(point_t *arr, size_t &alen);
point_t &get_lpoint_in_row(point_t *arr, size_t &alen, size_t y_value);
point_t &get_lpoint_in_row(point_t *arr, size_t &alen, size_t y_value);

#endif // GEOMETRY_H
