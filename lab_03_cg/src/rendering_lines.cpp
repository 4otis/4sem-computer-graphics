#include "rendering_lines.h"

#include <QDebug>
#include <QGraphicsScene>
#include <QPainter>
#include <QPoint>

void clear_scene(render_t &data) { data.scene->clear(); }

void fill_scene_background(render_t &data) { data.scene->setBackgroundBrush(data.bg_color); }

void render_point(render_t &data, point_t &point) { data.p->drawPoint(point.x, point.y); }

void render_point_Af(render_t &data, point_Af_t &point) {
    qDebug() << point.Af;
    data.fill_color.setAlphaF(fminf((float)point.Af * 2, 1.));
    // data.fill_color.setAlphaF(1);
    data.p->setPen(data.fill_color);
    data.p->drawPoint(point.x, point.y);
}

void render_line_built_in(render_t &data, line_t &line) {
    data.p->drawLine(QPoint((int)round(line.p1.x), (int)round(line.p1.y)), QPoint((int)round(line.p2.x), (int)round(line.p2.y)));
}

void render_points_list(render_t &data, QList<point_t> &list) {
    foreach (point_t point, list)
        render_point(data, point);
}

void render_points_list_Af(render_t &data, QList<point_Af_t> &list) {
    foreach (point_Af_t point, list)
        render_point_Af(data, point);
}

error_t render_all_lines(render_t &data, lines_t &lines) {
    if (is_lines_empty(lines))
        return LINES_NOT_BUILDED;

    // qDebug() << data.draw_line_alg;

    QList<point_t> points_list;
    QList<point_Af_t> points_list_Af;
    bool stat_mode = false;

    for (size_t i = 0; i < lines.alen; i++)
        switch (data.draw_line_alg) {
        case BUILT_IN:
            render_line_built_in(data, lines.arr[i]);
            break;
        case DDA:
            qDebug() << "DDA";
            points_list = draw_line_dda(lines.arr[i], stat_mode);
            render_points_list(data, points_list);
            break;
        case BRESENHAM_INT:
            qDebug() << "BR INT";
            points_list = draw_line_bresenham_int(lines.arr[i], stat_mode);
            render_points_list(data, points_list);
            break;
        case BRESENHAM_FLOAT:
            points_list = draw_line_bresenham_float(lines.arr[i], stat_mode);
            render_points_list(data, points_list);
            break;
        case BRESENHAM_SMOOTH:
            points_list_Af = draw_line_bresenham_smooth(lines.arr[i], stat_mode);
            render_points_list_Af(data, points_list_Af);
            break;
        default:
            render_line_built_in(data, lines.arr[i]);
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
    // lines.color.setAlphaF();
    data.fill_color = lines.color;
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
