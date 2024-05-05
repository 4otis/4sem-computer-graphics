#ifndef RENDERING_H
#define RENDERING_H

#include <QDebug>
#include <QGraphicsScene>
#include <QPainter>
#include <QPoint>

#include "draw_algorithms.h"
#include "my_circle.h"
#include "my_ellipse.h"

struct render {
    QGraphicsScene *scene;
    QPainter *p;
    double width;
    double height;
    algorithm_t algorithm;
};
using render_t = struct render;

error_t render_circle(render_t &data, circle_t &circle);

error_t render_ellipse(render_t &data, ellipse_t &ellipse);

#endif // RENDERING_H
