#include "draw_algorithms.h"
#include <QDebug>
#include <cmath>

QList<point_t> draw_line_dda(line_t &line, size_t &steps, bool stat_mode) {
    QList<point_t> points_list;
    point_t point;

    float x1 = line.p1.x, y1 = line.p1.y;
    float x2 = line.p2.x, y2 = line.p2.y;

    int dx = (int)x2 - x1;
    int dy = (int)y2 - y1;

    int step = (fabs(dx) > fabs(dy)) ? fabs(dx) : fabs(dy);

    float x_inc = (float)dx / step;
    float y_inc = (float)dy / step;

    if (!stat_mode) {
        for (int i = 0; i < step; i++) {
            point = {.x = round(x1), .y = round(y1)};
            points_list.push_back(point);
            // data.p->drawPoint(round(x1), round(y1));

            if (round(x1 + x_inc) != round(x1) && round(y1 + y_inc) != round(y1))
                steps += 1;

            x1 += x_inc;
            y1 += y_inc;
        }
    } else
        for (int i = 0; i < step; i++) {
            point = {.x = round(x1), .y = round(y1)};
            x1 += x_inc;
            y1 += y_inc;
        }

    return points_list;
}

QList<point_t> draw_line_bresenham_int(line_t &line, bool stat_mode) {
    QList<point_t> points_list;
    point_t point;

    int x1 = (int)line.p1.x, y1 = (int)line.p1.y;
    int x2 = (int)line.p2.x, y2 = (int)line.p2.y;

    const int deltaX = fabs(x2 - x1);
    const int deltaY = fabs(y2 - y1);

    const int signX = x1 < x2 ? 1 : -1;
    const int signY = y1 < y2 ? 1 : -1;
    int error = deltaX - deltaY;

    if (!stat_mode) {
        while (x1 != x2 || y1 != y2) {
            point = {.x = (int)x1, .y = (int)y1};
            points_list.push_back(point);
            // data.p->drawPoint((int)x1, (int)y1);
            int error2 = error * 2;
            if (error2 > -deltaY) {
                error -= deltaY;
                x1 += signX;
            }
            if (error2 < deltaX) {
                error += deltaX;
                y1 += signY;
            }
        }
    } else
        while (x1 != x2 || y1 != y2) {
            // qDebug() << "dzudz";
            point = {.x = (int)x1, .y = (int)y1};
            int error2 = error * 2;
            if (error2 > -deltaY) {
                error -= deltaY;
                x1 += signX;
            }
            if (error2 < deltaX) {
                error += deltaX;
                y1 += signY;
            }
        }

    return points_list;
}

QList<point_t> draw_line_bresenham_float(line_t &line, bool stat_mode) {
    QList<point_t> points_list;
    point_t point;

    float x1 = line.p1.x, y1 = line.p1.y;
    float x2 = line.p2.x, y2 = line.p2.y;

    float dx = x2 - x1;
    float dy = y2 - y1;

    float steps = std::max(fabs(dx), fabs(dy));

    float xIncrement = dx / steps;
    float yIncrement = dy / steps;
    float x = x1;
    float y = y1;

    if (!stat_mode)
        for (int i = 0; i <= steps; i++) {
            point = {.x = round(x), .y = round(y)};
            points_list.push_back(point);
            x += xIncrement;
            y += yIncrement;
        }
    else
        for (int i = 0; i <= steps; i++) {
            point = {.x = round(x), .y = round(y)};
            x += xIncrement;
            y += yIncrement;
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

    // if (!deltaX)
    //     signX = 0;
    // if (!deltaY)
    //     signY = 0;

    float intensivity = 1;
    int was_swaped;

    float m = (float)deltaY / deltaX;
    if (m > 1) {
        m = (float)1 / (float)m;

        was_swaped = 2;
    } else
        was_swaped = 0;

    m *= intensivity;
    float w = intensivity - m;
    float e = intensivity / 2;

    int x = x1, y = y1;
    if (!stat_mode) {
        point = {.x = x1, .y = y1, .Af = (float)m / 2};
        points_list.push_back(point);
        while (x != x2 || y != y2) {
            // qDebug() << "e:" << e << "w:" << w << "m:" << m;

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

    int x1 = (int)line.p1.x, y1 = (int)line.p1.y;
    int x2 = (int)line.p2.x, y2 = (int)line.p2.y;

    int deltaX = fabs(x2 - x1);
    int deltaY = fabs(y2 - y1);

    return points_list;
}

// QList<point_Af_t> draw_line_wu(line_t &line, bool stat_mode) {
//     QList<point_Af_t> points_list;
//     point_Af_t point;

//     int x1 = (int)line.p1.x, y1 = (int)line.p1.y;
//     int x2 = (int)line.p2.x, y2 = (int)line.p2.y;

//     int deltaX = fabs(x2 - x1);
//     int deltaY = fabs(y2 - y1);

//     int signX = x1 < x2 ? 1 : -1;
//     int signY = y1 < y2 ? 1 : -1;

//     return points_list;
// }

// void DrawWuLine(CDC *pDC, short X0, short Y0, short X1, short Y1, short BaseColor, short NumLevels, unsigned short IntensityBits) {
//     unsigned short IntensityShift, ErrorAdj, ErrorAcc;
//     unsigned short ErrorAccTemp, Weighting, WeightingComplementMask;
//     short DeltaX, DeltaY, Temp, XDir;

//     /* Make sure the line runs top to bottom */
//     if (Y0 > Y1) {
//         Temp = Y0;
//         Y0 = Y1;
//         Y1 = Temp;
//         Temp = X0;
//         X0 = X1;
//         X1 = Temp;
//     }
//     /* Draw the initial pixel, which is always exactly intersected by
//       the line and so needs no weighting */
//     DrawPixel(pDC, X0, Y0, BaseColor);

//     if ((DeltaX = X1 - X0) >= 0) {
//         XDir = 1;
//     } else {
//         XDir = -1;
//         DeltaX = -DeltaX; /* make DeltaX positive */
//     }
//     /* Special-case horizontal, vertical, and diagonal lines, which
//       require no weighting because they go right through the center of
//       every pixel */
//     if ((DeltaY = Y1 - Y0) == 0) {
//         /* Horizontal line */
//         while (DeltaX-- != 0) {
//             X0 += XDir;
//             DrawPixel(pDC, X0, Y0, BaseColor);
//         }
//         return;
//     }
//     if (DeltaX == 0) {
//         /* Vertical line */
//         do {
//             Y0++;
//             DrawPixel(pDC, X0, Y0, BaseColor);
//         } while (--DeltaY != 0);
//         return;
//     }
//     if (DeltaX == DeltaY) {
//         /* Diagonal line */
//         do {
//             X0 += XDir;
//             Y0++;
//             DrawPixel(pDC, X0, Y0, BaseColor);
//         } while (--DeltaY != 0);
//         return;
//     }
//     /* Line is not horizontal, diagonal, or vertical */
//     ErrorAcc = 0; /* initialize the line error accumulator to 0 */
//     /* # of bits by which to shift ErrorAcc to get intensity level */
//     IntensityShift = 16 - IntensityBits;
//     /* Mask used to flip all bits in an intensity weighting, producing the
//       result (1 - intensity weighting) */
//     WeightingComplementMask = NumLevels - 1;
//     /* Is this an X-major or Y-major line? */
//     if (DeltaY > DeltaX) {
//         /* Y-major line; calculate 16-bit fixed-point fractional part of a
//          pixel that X advances each time Y advances 1 pixel, truncating the
//          result so that we won't overrun the endpoint along the X axis */
//         ErrorAdj = ((unsigned long)DeltaX << 16) / (unsigned long)DeltaY;
//         /* Draw all pixels other than the first and last */
//         while (--DeltaY) {
//             ErrorAccTemp = ErrorAcc; /* remember current accumulated error */
//             ErrorAcc += ErrorAdj;    /* calculate error for next pixel */
//             if (ErrorAcc <= ErrorAccTemp) {
//                 /* The error accumulator turned over, so advance the X coord */
//                 X0 += XDir;
//             }
//             Y0++; /* Y-major, so always advance Y */
//             /* The IntensityBits most significant bits of ErrorAcc give us the
//             intensity weighting for this pixel, and the complement of the
//             weighting for the paired pixel */
//             Weighting = ErrorAcc >> IntensityShift;
//             DrawPixel(pDC, X0, Y0, BaseColor + Weighting);
//             DrawPixel(pDC, X0 + XDir, Y0, BaseColor + (Weighting ^ WeightingComplementMask));
//         }
//         /* Draw the final pixel, which is
//          always exactly intersected by the line
//          and so needs no weighting */
//         DrawPixel(pDC, X1, Y1, BaseColor);
//         return;
//     }
//     /* It's an X-major line; calculate 16-bit fixed-point fractional part of a
//       pixel that Y advances each time X advances 1 pixel, truncating the
//       result to avoid overrunning the endpoint along the X axis */
//     ErrorAdj = ((unsigned long)DeltaY << 16) / (unsigned long)DeltaX;
//     /* Draw all pixels other than the first and last */
//     while (--DeltaX) {
//         ErrorAccTemp = ErrorAcc; /* remember current accumulated error */
//         ErrorAcc += ErrorAdj;    /* calculate error for next pixel */
//         if (ErrorAcc <= ErrorAccTemp) {
//             /* The error accumulator turned over, so advance the Y coord */
//             Y0++;
//         }
//         X0 += XDir; /* X-major, so always advance X */
//         /* The IntensityBits most significant bits of ErrorAcc give us the
//          intensity weighting for this pixel, and the complement of the
//          weighting for the paired pixel */
//         Weighting = ErrorAcc >> IntensityShift;
//         DrawPixel(pDC, X0, Y0, BaseColor + Weighting);
//         DrawPixel(pDC, X0, Y0 + 1, BaseColor + (Weighting ^ WeightingComplementMask));
//     }
//     /* Draw the final pixel, which is always exactly intersected by the line
//       and so needs no weighting */
//     DrawPixel(pDC, X1, Y1, BaseColor);
// }
