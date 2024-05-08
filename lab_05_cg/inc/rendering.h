#ifndef RENDERING_H
#define RENDERING_H

#include <QDebug>
#include <QGraphicsScene>
#include <QPainter>
#include <QPoint>

#include "my_point.h"
// #include "errorcodes.h"

struct render {
    QGraphicsScene *scene;
    QPainter *p;
    double width;
    double height;
};
using render_t = struct render;

error_t render_point(render_t &data, point_t &point, QColor color);
error_t render_edge(render_t &data, point_t &p1, point_t &p2);
error_t render_all_connecting_edges(render_t &data, points_t &points);

// error_t render_fill(render_t &data, points_t &points);

#endif // RENDERING_H
