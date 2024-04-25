#ifndef RENDERING_H
#define RENDERING_H

#include <QDebug>
#include <QGraphicsScene>
#include <QPainter>
#include <QPoint>

struct render {
    QGraphicsScene *scene;
    QPainter *p;
    double width;
    double height;
    union {
        circle_t render_circle;
        circles_t render_circles;
        ellipse_t render_ellipse;
        ellipses_t render_ellipses;
    };
};
using render_t = struct render;

#endif // RENDERING_H
