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

error_t render_lines(render_t &data, lines_t &lines);

#endif // RENDERING_LINES_H
