#include "draw_algorithms.h"
#include <cmath>

void tmirrored(QList<point_t> &points, point_t point, point_t center) {
    points.append({point.x, point.y});
    points.append({2 * center.x - point.x, point.y});
    points.append({point.x, 2 * center.y - point.y});
    points.append({2 * center.x - point.x, 2 * center.y - point.y});
    points.append({point.y + center.x - center.y, point.x + center.y - center.x});
    points.append({-point.y + center.x + center.y, point.x + center.y - center.x});
    points.append({point.y + center.x - center.y, -point.x + center.y + center.x});
    points.append({-point.y + center.x + center.y, -point.x + center.x + center.y});
}

QList<point_t> canonic_circle(circle_t &circle) {
    QList<point_t> points;

    int powered_r = circle.radius * circle.radius;
    for (double x = 0.; x <= (double)circle.radius / sqrt(2); ++x) {
        double y = sqrt(powered_r - x * x);

        tmirrored(points, {circle.centerX + x, circle.centerY + y},
                  {circle.centerX, circle.centerY});
    }

    return points;
}

QList<point_t> param_circle(circle_t &circle) {
    QList<point_t> points;

    double step = (double)1 / (double)circle.radius;

    for (double angle = 0.; angle <= M_PI_4; angle += step)
        tmirrored(points,
                  {circle.centerX + circle.radius * cos(angle),
                   circle.centerY + circle.radius * sin(angle)},
                  {circle.centerX, circle.centerY});

    return points;
}

QList<point_t> midpoint_circle(circle_t &circle) {
    QList<point_t> points;

    double x = circle.radius;
    double y = 0;
    double delta = 1 - x;

    while (x > y) {
        tmirrored(points, {circle.centerX + x, circle.centerY + y},
                  {circle.centerX, circle.centerY});
        ++y;

        if (delta > 0) {
            --x;
            delta -= 2 * x + 1;
        }

        delta += 2 * y + 1;
    }

    return points;
}

QList<point_t> bresenham_circle(circle_t &circle) {
    QList<point_t> points;

    int x = 0;
    int y = circle.radius;
    double delta = 2 * (1 - circle.radius);
    // double tmp;

    tmirrored(points, {circle.centerX + x, circle.centerY},
              {circle.centerX, circle.centerY});

    while (x < y) {
        if (delta < 0) {
            auto temp = 2 * (delta + y) - 1;
            ++x;
            if (temp > 0) {
                --y;
                delta += 2 * (x - y + 1);
            } else
                delta += 2 * x + 1;
        } else {
            auto temp = 2 * (delta - x) - 1;
            --y;
            if (temp < 0) {
                ++x;
                delta += 2 * (x - y + 1);
            } else
                delta -= 2 * y - 1;
        }

        tmirrored(points, {circle.centerX + x, circle.centerY},
                  {circle.centerX, circle.centerY});
    }

    return points;
}
