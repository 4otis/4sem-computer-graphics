#include "rendering_lines.h"

#include <QGraphicsScene>

fill_scene_background(render_t &data) { data.scene->setBackgroundBrush(data.bg_color); }

error_t render_all_lines(render_t &data, lines_t &lines) {
    if (is_lines_empty(lines))
        return LINES_NOT_BUILDED;

    for (size_t i = 0; i < lines.alen; i++) {
    }
}

error_t render_lines(render_t &data, lines_t &lines) {
    fill_scene_background(data);
    render_all_lines(render_t & data, lines_t & lines);
}
