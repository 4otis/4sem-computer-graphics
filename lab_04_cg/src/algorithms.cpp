#include "algorithms.h"
#include <math.h>

void tmirrored(QList<point_t> &points, point_t point, point_t center) {
    points.push_back(point.x, point.y);
    points.push_back(2 * center.x - point.x, point.y);
    points.push_back(point.x, 2 * center.y - point.y);
    points.push_back(2 * center.x - point.x, 2 * center.y - point.y);
    points.push_back(point.y + center.x - center.y, point.x + center.y - center.x);
    points.push_back(-point.y + center.x + center.y, point.x + center.y - center.x);
    points.push_back(point.y + center.x - center.y, -point.x + center.y + center.x);
    points.push_back(-point.y + center.x + center.y, -point.x + center.x + center.y);
}

QList<point_t> canonic_circle(circle_t &circle) {
    QList<point_t> points;

    int powered_r = circle.radius * circle.radius;
    for (int x = 0; x < int((double)circle.radius / sqrt(2)); ++x) {
        int y = (int)sqrt(powered_r - x * x);

        tmirrored(points, {circle.centerX + x, circle.centerY + y},
                  {circle.centerX, circle.centerY});
    }

    return points;
}

// QList<point_t> canonic_ellipse(ellipse_t &ellipse) { return; }
