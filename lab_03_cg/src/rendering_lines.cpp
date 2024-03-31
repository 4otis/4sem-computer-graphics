#include "rendering_lines.h"

#include <QDebug>
#include <QGraphicsScene>
#include <QPainter>
#include <QPoint>

void clear_scene(render_t &data) { data.scene->clear(); }

void fill_scene_background(render_t &data) { data.scene->setBackgroundBrush(data.bg_color); }

void render_line(render_t &data, line_t &line) { data.p->drawLine(QPoint(line.p1.x, line.p1.y), QPoint(line.p2.x, line.p2.y)); }

error_t render_all_lines(render_t &data, lines_t &lines) {
    if (is_lines_empty(lines))
        return LINES_NOT_BUILDED;

    qDebug() << data.draw_line_alg;

    for (size_t i = 0; i < lines.alen; i++)
        switch (data.draw_line_alg) {
        case BUILT_IN:
            render_line(data, lines.arr[i]);
            break;
        case DDA:
            draw_line_dda(data, lines.arr[i]);
            break;
        case BRESENHAM_INT:
            draw_line_bresenham_int(data, lines.arr[i]);
            break;
        case BRESENHAM_FLOAT:
            draw_line_bresenham_float(data, lines.arr[i]);
            break;
        case BRESENHAM_SMOOTH:
            draw_line_bresenham_smooth(data, lines.arr[i]);
            break;
        // case WU:
        //     draw_line_wu(data, lines.arr[i]);
        //     break;
        default:
            render_line(data, lines.arr[i]);
            break;
        }
    return SUCCESS;
}

error_t render_lines(render_t &data, lines_t &lines) {
    error_t rc;

    clear_scene(data);

    QPixmap pixmap = QPixmap(data.width, data.height);
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);

    data.p = &painter;
    data.p->setPen(lines.color);

    fill_scene_background(data);

    rc = render_all_lines(data, lines);

    for (size_t i = 0; i < 30; i++)
        data.p->drawPoint(430, i);

    for (size_t i = 0; i < 30; i++)
        painter.drawPoint(i, 320);

    if (rc == SUCCESS)
        data.scene->addPixmap(pixmap);

    return rc;
}
