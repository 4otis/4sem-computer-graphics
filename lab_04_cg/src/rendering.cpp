#include "rendering.h"
#include <QDebug>

void render_point(render_t &data, point_t &point) {
    data.p->drawPoint(round(point.x), round(point.y));
}

void render_builtin_circle(render_t &data, circle_t &circle) {
    data.p->drawEllipse(QPoint(circle.centerX, circle.centerY), circle.radius,
                        circle.radius);
}

void render_builtin_ellipse(render_t &data, ellipse_t &ellipse) {
    data.p->drawEllipse(QPoint(ellipse.centerX, ellipse.centerY), ellipse.rX, ellipse.rY);
}

// void render_point(render_t &data, point_t &point) { data.p->drawPoint(point.x,
// point.y); }

error_t render_circle(render_t &data, circle_t &circle) {
    error_t rc = SUCCESS;

    QPixmap pixmap = QPixmap(data.width, data.height);
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);

    data.p = &painter;
    // lines.color.setAlphaF();
    // data.fill_color = circle.color;
    data.p->setPen(circle.color);

    if (is_circle_empty(circle))
        rc = CIRCLE_NOT_BUILDED;
    else {
        QList<point_t> points;
        switch (data.algorithm) {
        case CANONIC:
            points = canonic_circle(circle);
            break;
        case PARAMETRIC:
            points = param_circle(circle);
            break;
        case MIDPOINT:
            points = midpoint_circle(circle);
            break;
        case BRESENHAM:
            points = bresenham_circle(circle);

            break;
        case BUILT_IN:
            render_builtin_circle(data, circle);
            break;
        default:
            break;
        }

        foreach (point_t point, points) {
            // qDebug() << "x: " << point.x << "y: " << point.y;
            render_point(data, point);
        }
    }

    if (rc == SUCCESS)
        data.scene->addPixmap(pixmap);

    return rc;
}

error_t render_circles(render_t &data, circles_t &circles) {
    error_t rc = SUCCESS;

    for (size_t i = 0; i < circles.alen && rc == SUCCESS; ++i)
        rc = render_circle(data, circles.arr[i]);

    return rc;
}

error_t render_ellipse(render_t &data, ellipse_t &ellipse) {
    error_t rc = SUCCESS;

    QPixmap pixmap = QPixmap(data.width, data.height);
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);

    data.p = &painter;
    data.p->setPen(ellipse.color);

    if (is_ellipse_empty(ellipse)) {

        rc = ELLIPSE_NOT_BUILDED;
    } else {
        QList<point_t> points;
        switch (data.algorithm) {
        case CANONIC:
            points = canonic_ellipse(ellipse);
            break;
        case PARAMETRIC:
            points = param_ellipse(ellipse);
            break;
        case MIDPOINT:
            points = midpoint_ellipse(ellipse);
            break;
        case BRESENHAM:
            points = bresenham_ellipse(ellipse);
            break;
        case BUILT_IN:
            render_builtin_ellipse(data, ellipse);
            break;
        default:
            break;
        }

        foreach (point_t point, points)
            render_point(data, point);
    }

    if (rc == SUCCESS)
        data.scene->addPixmap(pixmap);

    return rc;
}

error_t render_ellipses(render_t &data, ellipses_t &ellipses) {
    error_t rc = SUCCESS;

    for (size_t i = 0; i < ellipses.alen && rc == SUCCESS; ++i)
        rc = render_ellipse(data, ellipses.arr[i]);

    return rc;
}
