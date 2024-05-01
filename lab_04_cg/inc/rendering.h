#ifndef RENDERING_H
#define RENDERING_H

#include <QDebug>
#include <QGraphicsScene>
#include <QPainter>
#include <QPoint>

#include "algorithms.h"
#include "my_circle.h"

struct render {
    QGraphicsScene *scene;
    QPainter *p;
    double width;
    double height;
    // union {
    //     circle_t render_circle;
    //     circles_t render_circles;
    //     ellipse_t render_ellipse;
    //     ellipses_t render_ellipses;
    // };
    algorithm_t algorithm;
};
using render_t = struct render;

error_t render_circle(render_t &data, circle_t &circle);

// error_t render_ellipse(render_t &data, ellipse_t &ellipse);

#endif // RENDERING_H
