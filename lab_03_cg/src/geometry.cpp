#include "geometry.h"
#include <cmath>

void move_point(point_t &p, move_t delta) {
    p.x += delta.x;
    p.y += delta.y;
}

double degrees_to_radains(double angle) { return {-angle * M_PI / 180}; }

void rotate_OZ_point(point_t &p, double angle) {
    double tmp_x = p.x * cos(angle) - p.y * sin(angle);
    double tmp_y = p.x * sin(angle) + p.y * cos(angle);

    p.x = tmp_x;
    p.y = tmp_y;
}

void rotate_point(point_t &p, rotate_t &data) {
    move_t default_trans;
    default_trans.x = -data.center_p.x;
    default_trans.y = -data.center_p.y;

    move_point(p, default_trans);

    double angle_in_radians = degrees_to_radains(data.angle);

    rotate_OZ_point(p, angle_in_radians);

    default_trans.x *= -1;
    default_trans.y *= -1;

    move_point(p, default_trans);
}

void rotate_two_points(two_points_t &points, double angle) {
    rotate_t rotate_data = {.angle = angle, .center_p = points.p1};
    rotate_point(points.p2, rotate_data);
}

void add_two_points_to_line(line_t &line, two_points_t &data) {
    line.p1 = data.p1;
    line.p2 = data.p2;
}
