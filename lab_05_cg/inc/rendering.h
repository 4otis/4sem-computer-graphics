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
    QPixmap pixmap;
};
using render_t = struct render;

struct my_edge {
    point_t p1;
    point_t p2;
};
using edge_t = struct my_edge;

struct my_edges {
    QList<edge_t> list;
    // int min_y;
    // int max_y;
    int min_x;
    int max_x;
};
using edges_t = struct my_edges;

edges_t get_edges_from_points(points_t &points);

error_t render_point(render_t &data, point_t &point, QColor color);
error_t render_edge(render_t &data, point_t &p1, point_t &p2);
error_t render_all_connecting_edges(render_t &data, points_t &points);
error_t render_fill_by_edges(render_t &data, edges_t &e_list);

#endif // RENDERING_H
