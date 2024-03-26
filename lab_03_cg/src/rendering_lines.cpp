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

    qDebug() << data.draw_line_alg;

    for (size_t i = 0; i < lines.alen; i++)
        switch (data.draw_line_alg) {
        case BUILT_IN:
            render_line(data, lines.arr[i], lines.color);
            break;
        case DDA:
            draw_line_dda(data, lines.arr[i], lines.color);
            break;
        case BRESENHAM_INT:
            draw_line_bresenham_int(data, lines.arr[i], lines.color);
            break;
        // case BRESENHAM_FLOAT:
        //     draw_line_bresenham_float(data, lines.arr[i], lines.color);
        //     break;
        // case BRESENHAM_MODIFIED:
        //     draw_line_bresenham_modified(data, lines.arr[i], lines.color);
        //     break;
        // case WU:
        //     draw_line_wu(data, lines.arr[i], lines.color);
        //     break;
        default:
            render_line(data, lines.arr[i], lines.color);
            break;
        }
    return SUCCESS;
}

error_t render_lines(render_t &data, lines_t &lines) {
    error_t rc;

    clear_scene(data);
    fill_scene_background(data);

    rc = render_all_lines(data, lines);

    return rc;
}
