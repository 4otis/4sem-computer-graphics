#ifndef RENDERING_LINES_H
#define RENDERING_LINES_H

#include <QColor>
#include <QGraphicsScene>

#include "lines.h"

struct render {
    QGraphicsScene *scene;
    double width;
    double height;
    QColor bg_color;
};
using render_t = struct render;

error_t render_lines(lines_t &lines, render_t);

#endif // RENDERING_LINES_H
