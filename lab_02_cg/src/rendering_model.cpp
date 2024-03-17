#include "rendering_model.h"
#include <QGraphicsTextItem>

void render_two_close_points(render_t &params, point_t &p1, point_t &p2) { params.scene->addLine(p1.x, p1.y, p2.x, p2.y); }

void render_all_points(render_t &params, model_t &model) {
    for (size_t i = 0; i < model.points_alen - 4 - 1; i++) {
        if (i == 0)
            render_two_close_points(params, model.points_arr[i], model.points_arr[model.points_alen - 4 - 1]);

        render_two_close_points(params, model.points_arr[i], model.points_arr[i + 1]);
    }

    for (size_t i = model.points_alen - 4; i < model.points_alen - 1; i++) {
        if (i == model.points_alen - 4)
            params.scene->addLine(model.points_arr[i].x, model.points_arr[i].y, model.points_arr[model.points_alen - 1].x,
                                  model.points_arr[model.points_alen - 1].y);

        params.scene->addLine(model.points_arr[i].x, model.points_arr[i].y, model.points_arr[i + 1].x, model.points_arr[i + 1].y);
    }
}

error_t render_model(model_t &model, render_t &params) {
    if (!model.points_arr)
        return NO_MODEL_ERROR;

    clear_scene(params);
    render_all_points(params, model);

    return SUCCESS;
}

void render_ellipse_point(render_t &params, point_t &p, QColor color) {
    double size = 8;
    params.scene->addEllipse(p.x - size / 2, p.y - size / 2, size, size, color);

    QPen pen;
    pen.setColor(color);

    // QGraphicsTextItem *text = new QGraphicsTextItem(QString("%1, %2").arg(p.x).arg(p.y), 0, 0);

    // QGraphicsTextItem text;
    // text.setPlainText(QString("%1, %2").arg(p.x).arg(p.y));
    // text.setPos(50, 50);
    // text.setDefaultTextColor(QColor(0, 0, 128));
    // params.scene->addItem(&text);

    QGraphicsTextItem *text = new QGraphicsTextItem;
    text->setPos(p.x, p.y);
    text->setPlainText(QString("%1, %2").arg(p.x).arg(p.y));
    params.scene->addItem(text);
}

// v/*oid render_outline_rectangle(render_t &params, model_t &model) {
//     size_t rect_h = 30;
//     size_t rect_w = 50;

//     int min_y = get_min_y_point(model.points_arr, model.points_alen).y;
//     int min_y = get_max_y_point(model.points_arr, model.points_alen).y;

//     for (int i = min_y; i <= max_y; i++) {
//         params.scene->addLine()
//     }
// }*/

void render_extras(render_t &params) {
    params.scene->addLine(0, -320, 0, 320, QColor(0, 0, 255));
    params.scene->addLine(-430, 0, 430, 0, QColor(0, 0, 255));

    render_ellipse_point(params, params.rotate_center, QColor(0, 200, 0));
    render_ellipse_point(params, params.scale_center, QColor(255, 0, 255));
}

void clear_scene(render_t &params) { params.scene->clear(); }
