#include "draw_algorithms.h"
#include <QDebug>
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

void dmirrored(QList<point_t> &points, point_t point, point_t center) {
    points.append({point.x, point.y});
    points.append({2 * center.x - point.x, point.y});
    points.append({point.x, 2 * center.y - point.y});
    points.append({2 * center.x - point.x, 2 * center.y - point.y});
}

QList<point_t> canonic_circle(circle_t &circle) {
    QList<point_t> points;

    int powered_r = circle.radius * circle.radius;

    double limit = round((double)circle.radius / sqrt(2));

    for (double x = 0.; x <= limit; ++x) {
        double y = sqrt(powered_r - x * x);

        tmirrored(points, {circle.centerX + x, circle.centerY + y},
                  {circle.centerX, circle.centerY});
    }

    return points;
}

QList<point_t> param_circle(circle_t &circle) {
    QList<point_t> points;

    double step = (double)1 / (double)circle.radius;

    for (double angle = 0.; angle <= M_PI_4 + step; angle += step)
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

    while (x >= y) {
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
    int f = 1 - circle.radius;
    int incrE = 3, incrSE = 5 - 2 * circle.radius;

    dmirrored(points, {circle.centerX + x, circle.centerY + y},
              {circle.centerX, circle.centerY});

    while (x <= y) {
        if (f > 0) {
            --y;
            f += incrSE;
            incrSE += 4;
        } else {
            f += incrE;
            incrSE += 2;
        }
        incrE += 2;
        ++x;
        tmirrored(points, {circle.centerX + x, circle.centerY + y},
                  {circle.centerX, circle.centerY});
    }

    // // double tmp;

    // dmirrored(points, {circle.centerX + x, circle.centerY},
    //           {circle.centerX, circle.centerY});

    // while (x <= y) {
    //     if (delta < 0) {
    //         auto temp = 2 * (delta + y) - 1;
    //         ++x;
    //         if (temp > 0) {
    //             --y;
    //             delta += 2 * (x - y + 1);
    //         } else
    //             delta += 2 * x + 1;
    //     } else {
    //         auto temp = 2 * (delta - x) - 1;
    //         --y;
    //         if (temp < 0) {
    //             ++x;
    //             delta += 2 * (x - y + 1);
    //         } else
    //             delta -= 2 * y - 1;
    //     }

    //     tmirrored(points, {circle.centerX + x, circle.centerY},
    //               {circle.centerX, circle.centerY});
    // }

    return points;
}

QList<point_t> canonic_ellipse(ellipse_t &ellipse) {
    QList<point_t> points;

    int powered_rX = ellipse.rX * ellipse.rX;
    int powered_rY = ellipse.rY * ellipse.rY;

    int limit = int(ellipse.centerX +
                    ((double)ellipse.rX / sqrt(1 + ((double)powered_rY / powered_rX))));

    for (int x = ellipse.centerX; x <= limit; ++x) {
        int y = round(
            (double)sqrt(powered_rX * powered_rY -
                         (x - ellipse.centerX) * (x - ellipse.centerX) * powered_rY) /
                (double)ellipse.rX +
            ellipse.centerY);

        dmirrored(points, {x, y}, {ellipse.centerX, ellipse.centerY});
    }

    limit = int(ellipse.centerY +
                ((double)ellipse.rY / sqrt(1 + ((double)powered_rX / powered_rY))));

    for (int y = limit; y >= ellipse.centerY; --y) {
        int x = round(sqrt(powered_rX * powered_rY -
                           (y - ellipse.centerY) * (y - ellipse.centerY) * powered_rX) /
                          (double)ellipse.rY +
                      ellipse.centerX);

        dmirrored(points, {x, y}, {ellipse.centerX, ellipse.centerY});
    }

    return points;
}

QList<point_t> param_ellipse(ellipse_t &ellipse) {
    QList<point_t> points;

    double step = (double)1 / (double)(ellipse.rX > ellipse.rY ? ellipse.rX : ellipse.rY);

    for (double angle = 0.; angle <= M_PI_2; angle += step)
        dmirrored(points,
                  {ellipse.centerX + ellipse.rX * cos(angle),
                   ellipse.centerY + ellipse.rY * sin(angle)},
                  {ellipse.centerX, ellipse.centerY});

    return points;
}

QList<point_t> midpoint_ellipse(ellipse_t &ellipse) {
    QList<point_t> points;

    double x = 0.;
    double y = ellipse.rY;

    double powered_rX = ellipse.rX * ellipse.rX;
    double powered_rY = ellipse.rY * ellipse.rY;

    double delta = powered_rY - powered_rX * powered_rY + 0.25 * powered_rX;
    double dx = 2 * powered_rY * x;
    double dy = 2 * powered_rX * y;

    while (dx <= dy) {
        dmirrored(points, {ellipse.centerX + x, ellipse.centerY + y},
                  {ellipse.centerX, ellipse.centerY});

        ++x;
        dx += 2 * powered_rY;

        if (delta >= 0) {
            --y;
            dy -= 2 * powered_rX;
            delta -= dy;
        }

        delta += dx + powered_rY;
    }

    delta = powered_rY * (x + 0.5) * (x * 0.5) + powered_rX * (y - 1) * (y - 1) -
            powered_rX * powered_rY;

    while (y >= 0) {
        dmirrored(points, {ellipse.centerX + x, ellipse.centerY + y},
                  {ellipse.centerX, ellipse.centerY});

        --y;
        dy -= 2 * powered_rX;

        if (delta <= 0) {
            ++x;
            dx += 2 * powered_rY;
            delta += dx;
        }

        delta -= dy - powered_rX;
    }
    return points;
}

QList<point_t> bresenham_ellipse(ellipse_t &ellipse) {
    QList<point_t> points;

    double x = 0., y = ellipse.rY;

    double powered_rX = ellipse.rX * ellipse.rX;
    double powered_rY = ellipse.rY * ellipse.rY;

    double delta = powered_rY - powered_rX * (2 * ellipse.rY + 1);

    while (y >= 0) {
        dmirrored(points, {x + ellipse.centerX, y + ellipse.centerY},
                  {ellipse.centerX, ellipse.centerY});

        if (delta < 0) {
            auto temp = 2 * delta + powered_rX * (2 * y - 1);
            ++x;
            delta += powered_rY * (2 * x + 1);
            if (temp > 0) {
                --y;
                delta += powered_rX * (-2 * y + 1);
            }
        } else if (0 == delta) {
            ++x;
            --y;
            delta += powered_rY * (2 * x + 1) + (1 - 2 * y) * powered_rX;
        } else {
            auto temp = 2 * delta + powered_rY * (-2 * x - 1);
            --y;
            delta += powered_rX * (-2 * y + 1);
            if (temp < 0) {
                ++x;
                delta += powered_rY * (2 * x + 1);
            }
        }
    }

    return points;
}
