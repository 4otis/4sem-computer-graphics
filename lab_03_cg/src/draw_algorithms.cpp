#include "draw_algorithms.h"
#include <QDebug>
#include <cmath>

QList<point_t> draw_line_dda(line_t &line, size_t &steps, bool stat_mode) {
    QList<point_t> points_list;
    point_t point;

    double x1 = line.p1.x, y1 = line.p1.y;
    double x2 = line.p2.x, y2 = line.p2.y;

    double dx = x2 - x1;
    double dy = y2 - y1;

    if (dx == 0 && dy == 0) {
        point = {.x = x1, .y = y1};
        points_list.append(point);
        return points_list;
    }

    int l = (fabs(dx) > fabs(dy)) ? fabs(dx) : fabs(dy);

    dx /= (double)l;
    dy /= (double)l;

    if (!stat_mode)
        for (int i = 0; i < l + 1; ++i) {
            point = {.x = round(x1), .y = round(y1)};
            points_list.append(point);
            x1 += dx;
            y1 += dy;
        }
    else
        for (int i = 0; i < l + 1; ++i) {
            point = {.x = round(x1), .y = round(y1)};
            x1 += dx;
            y1 += dy;
        }

    return points_list;
}

QList<point_t> draw_line_bresenham_int(line_t &line, bool stat_mode) {
    QList<point_t> points_list;
    point_t point;

    int x1 = line.p1.x, y1 = line.p1.y;
    int x2 = line.p2.x, y2 = line.p2.y;

    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);

    if (dx == 0 && dy == 0) {
        point = {.x = x1, .y = y1};
        points_list.append(point);
        return points_list;
    }

    const int signX = x1 < x2 ? 1 : -1;
    const int signY = y1 < y2 ? 1 : -1;

    bool was_swaped = false;
    if (dx < dy) {
        int tmp = dx;
        dx = dy;
        dy = tmp;
        was_swaped = true;
    }

    int e = 2 * dy - dx;

    if (!stat_mode)
        for (int i = 0; i < dx + 1; ++i) {
            point = {.x = x1, .y = y1};
            points_list.append(point);
            if (e >= 0) {
                if (was_swaped)
                    x1 += signX;
                else
                    y1 += signY;

                e -= 2 * dx;
            }

            if (was_swaped)
                y1 += signY;
            else
                x1 += signX;

            e += 2 * dy;
        }
    else
        for (int i = 0; i < dx + 1; ++i) {
            point = {.x = x1, .y = y1};
            if (e >= 0) {
                if (was_swaped)
                    x1 += signX;
                else
                    y1 += signY;

                e -= 2 * dx;
            }

            if (was_swaped)
                y1 += signY;
            else
                x1 += signX;

            e += 2 * dy;
        }

    return points_list;
}

// QList<point_t> draw_line_bresenham_int(line_t &line, bool stat_mode) {
//     QList<point_t> points_list;
//     point_t point;

//     int x1 = (int)line.p1.x, y1 = (int)line.p1.y;
//     int x2 = (int)line.p2.x, y2 = (int)line.p2.y;

//     const int deltaX = fabs(x2 - x1);
//     const int deltaY = fabs(y2 - y1);

//     const int signX = x1 < x2 ? 1 : -1;
//     const int signY = y1 < y2 ? 1 : -1;
//     int error = deltaX - deltaY;

//     if (!stat_mode) {
//         while (x1 != x2 || y1 != y2) {
//             point = {.x = (int)x1, .y = (int)y1};
//             points_list.push_back(point);
//             int error2 = error * 2;
//             if (error2 > -deltaY) {
//                 error -= deltaY;
//                 x1 += signX;
//             }
//             if (error2 < deltaX) {
//                 error += deltaX;
//                 y1 += signY;
//             }
//         }
//     } else
//         while (x1 != x2 || y1 != y2) {
//             point = {.x = (int)x1, .y = (int)y1};
//             int error2 = error * 2;
//             if (error2 > -deltaY) {
//                 error -= deltaY;
//                 x1 += signX;
//             }
//             if (error2 < deltaX) {
//                 error += deltaX;
//                 y1 += signY;
//             }
//         }

//     return points_list;
// }

QList<point_t> draw_line_bresenham_float(line_t &line, bool stat_mode) {
    QList<point_t> points_list;
    point_t point;

    int x1 = line.p1.x, y1 = line.p1.y;
    int x2 = line.p2.x, y2 = line.p2.y;

    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);

    if (dx == 0 && dy == 0) {
        point = {.x = x1, .y = y1};
        points_list.append(point);
        return points_list;
    }

    const int signX = x1 < x2 ? 1 : -1;
    const int signY = y1 < y2 ? 1 : -1;

    bool was_swaped = false;
    if (dx < dy) {
        int tmp = dx;
        dx = dy;
        dy = tmp;
        was_swaped = true;
    }

    double m = double(dy) / double(dx);
    double e = m - 0.5;

    if (!stat_mode)
        for (int i = 0; i < dx + 1; ++i) {
            point = {.x = x1, .y = y1};
            points_list.append(point);
            if (e >= 0) {
                if (was_swaped)
                    x1 += signX;
                else
                    y1 += signY;

                e -= 1;
            }
            if (e < 0) {
                if (was_swaped)
                    y1 += signY;
                else
                    x1 += signX;

                e += m;
            }
        }
    else
        for (int i = 0; i < dx + 1; ++i) {
            point = {.x = x1, .y = y1};
            if (e >= 0) {
                if (was_swaped)
                    x1 += signX;
                else
                    y1 += signY;

                e -= 1;
            }
            if (e < 0) {
                if (was_swaped)
                    y1 += signY;
                else
                    x1 += signX;

                e += m;
            }
        }

    return points_list;
}

QList<point_Af_t> draw_line_bresenham_smooth(line_t &line, bool stat_mode) {
    QList<point_Af_t> points_list;
    point_Af_t point;

    int x1 = (int)line.p1.x, y1 = (int)line.p1.y;
    int x2 = (int)line.p2.x, y2 = (int)line.p2.y;

    int deltaX = fabs(x2 - x1);
    int deltaY = fabs(y2 - y1);

    int signX = x1 < x2 ? 1 : -1;
    int signY = y1 < y2 ? 1 : -1;

    float intensivity = 1;
    bool was_swaped;

    float m = (float)deltaY / deltaX;
    if (m > 1) {
        m = (float)1 / (float)m;

        was_swaped = true;
    } else
        was_swaped = false;

    m *= intensivity;
    float w = intensivity - m;
    float e = intensivity / 2;

    int x = x1, y = y1;
    if (!stat_mode) {
        point = {.x = x1, .y = y1, .Af = (float)m / 2};
        points_list.push_back(point);
        while (x != x2 || y != y2) {

            if (e < w) {
                if (was_swaped) // dx < dy
                    y += signY;
                else
                    x += signX;
                e += m;
            } else {
                x += signX;
                y += signY;
                e -= w;
            }
            // drawpoint intens = e
            point = {.x = x, .y = y, .Af = e * intensivity};
            points_list.push_back(point);
        }
    } else {
        point = {.x = x1, .y = y1, .Af = (float)m / 2};
        while (x != x2 || y != y2) {
            if (e < w) {
                if (was_swaped) // dx < dy
                    y += signY;
                else
                    x += signX;
                e += m;
            } else {
                x += signX;
                y += signY;
                e -= w;
            }
            point = {.x = x, .y = y, .Af = e};
        }
    }

    return points_list;
}

QList<point_Af_t> draw_line_wu(line_t &line, bool stat_mode) {
    QList<point_Af_t> points_list;
    point_Af_t point;

    int x1 = (int)line.p1.x, y1 = (int)line.p1.y;
    int x2 = (int)line.p2.x, y2 = (int)line.p2.y;

    int deltaX = fabs(x2 - x1);
    int deltaY = fabs(y2 - y1);

    bool was_swaped;

    if (deltaY > deltaX) {
        int tmp = x1;
        x1 = y1;
        y1 = tmp;

        tmp = x2;
        x2 = y2;
        y2 = tmp;

        was_swaped = true;
    } else
        was_swaped = false;

    if (x2 < x1) {
        int tmp = x1;
        x1 = x2;
        x2 = tmp;
        tmp = y1;
        y1 = y2;
        y2 = tmp;
    }

    deltaX = x2 - x1;
    deltaY = y2 - y1;
    float tg;

    if (deltaX == 0)
        tg = 1;
    else
        tg = (float)deltaY / deltaX;

    int xend = round(x1);
    int yend = y1 + tg * (xend - x1);
    int xpx1 = xend;
    float y = yend + tg;

    xend = int(x2 + 0.5);
    int xpx2 = xend;

    if (stat_mode) {
        if (was_swaped)
            for (int x = xpx1; x < xpx2; ++x) {
                point = {.x = int(y), .y = x + 1, .Af = 1 - (y - int(y))};
                point = {.x = int(y) + 1, .y = x + 1, .Af = y - int(y)};
                y += tg;
            }
        else
            for (int x = xpx1; x < xpx2; ++x) {
                point = {.x = x + 1, .y = int(y), .Af = 1 - (y - int(y))};
                point = {.x = x + 1, .y = int(y) + 1, .Af = y - int(y)};
                y += tg;
            }
    } else {
        if (was_swaped)
            for (int x = xpx1; x < xpx2; ++x) {
                point = {.x = int(y), .y = x + 1, .Af = 1 - (y - int(y))};
                points_list.append(point);
                point = {.x = int(y) + 1, .y = x + 1, .Af = y - int(y)};
                points_list.append(point);
                y += tg;
            }
        else
            for (int x = xpx1; x < xpx2; ++x) {
                point = {.x = x + 1, .y = int(y), .Af = 1 - (y - int(y))};
                points_list.append(point);
                point = {.x = x + 1, .y = int(y) + 1, .Af = y - int(y)};
                points_list.append(point);
                y += tg;
            }
    }

    return points_list;
}
