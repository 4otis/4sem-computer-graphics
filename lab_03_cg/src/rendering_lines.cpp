#include "rendering_lines.h"

#include <QDebug>
#include <QGraphicsScene>

void clear_scene(render_t &data) { data.scene->clear(); }

void fill_scene_background(render_t &data) { data.scene->setBackgroundBrush(data.bg_color); }

void render_line(render_t &data, line_t &line, QColor &color) {
    data.scene->addLine(line.p1.x, line.p1.y, line.p2.x, line.p2.y, color);
}

error_t render_all_lines(render_t &data, lines_t &lines) {
    if (is_lines_empty(lines))
        return LINES_NOT_BUILDED;

    for (size_t i = 0; i < lines.alen; i++)
        render_line(data, lines.arr[i], lines.color);

    return SUCCESS;
}

error_t render_lines(render_t &data, lines_t &lines) {
    error_t rc;

    clear_scene(data);
    fill_scene_background(data);

    rc = render_all_lines(data, lines);

    return rc;
}
