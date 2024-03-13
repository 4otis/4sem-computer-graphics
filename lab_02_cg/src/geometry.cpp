#include "geometry.h"
#include <QDebug>
#include <cmath>

#define EPS 10e-8;

double degrees_to_radians(double degrees) { return degrees * M_PI / 180; }

point_t *alloc_points(size_t &alen) {
    point_t *tmp = (point_t *)malloc(alen * sizeof(point_t));
    if (!tmp)
        return nullptr;
    return tmp;
}

void destroy_points(point_t *arr) { free(arr); }

long long gcd(long long num1, long long num2) {
    while (num1 && num2)
        if (num1 > num2)
            num1 %= num2;
        else
            num2 %= num1;
    return num1 + num2;
}

size_t get_amount_of_rotations_for_epicycloid(double a, double b) { return b * 1000 / gcd(a * 1000, b * 1000); }

int calc_epicycloid_point(build_t &params, point_t &p) {
    double a = params.a;
    double b = params.b;
    double angle = params.angle;
    p.x = (a + b) * cos(angle) - b * cos((a + b) * angle / b);
    p.y = (a + b) * sin(angle) - b * sin((a + b) * angle / b);
    return 0;
}

error_t calc_all_points(build_t &params, point_t *arr, size_t &alen) {

    double angle = 0;
    for (size_t i = 0; i < alen; i++) {
        params.angle = degrees_to_radians(360 - angle);
        calc_epicycloid_point(params, arr[i]);

        angle += 1;
    }
    return SUCCESS;
}

void move_point(move_t &params, point_t &p) {
    p.x = p.x + params.x;
    p.y = p.y + params.y;
}

error_t move_all_points(move_t &params, point_t *arr, size_t &alen) {
    if (!arr)
        return NO_MODEL_ERROR;

    for (size_t i = 0; i < alen; i++)
        move_point(params, arr[i]);

    return SUCCESS;
}

void rotate_OZ_point(double angle, point_t &p) {
    double tmp_x = p.x * cos(angle) - p.y * sin(angle);
    double tmp_y = p.x * sin(angle) + p.y * cos(angle);

    p.x = tmp_x;
    p.y = tmp_y;
}

void rotate_point(rotate_t &params, point_t &p) {
    move_t default_transformation;
    default_transformation.x = -params.center_p.x;
    default_transformation.y = -params.center_p.y;
    move_point(default_transformation, p);

    double angle_OZ_in_radians = degrees_to_radians(params.angle_OZ_in_degrees);

    rotate_OZ_point(angle_OZ_in_radians, p);

    default_transformation.x = -default_transformation.x;
    default_transformation.y = -default_transformation.y;

    move_point(default_transformation, p);
}

error_t rotate_all_points(rotate_t &params, point_t *arr, size_t &alen) {
    if (!arr)
        return NO_MODEL_ERROR;

    for (size_t i = 0; i < alen; i++)
        rotate_point(params, arr[i]);

    return SUCCESS;
}

void scale_point(scale_t &params, point_t &p) {
    p.x = (p.x - params.center_p.x) * params.x_scale + params.center_p.x;
    p.y = (p.y - params.center_p.y) * params.y_scale + params.center_p.y;
}

error_t scale_all_points(scale_t &params, point_t *arr, size_t &alen) {
    if (!arr)
        return NO_MODEL_ERROR;

    for (size_t i = 0; i < alen; i++)
        scale_point(params, arr[i]);

    return SUCCESS;
}
