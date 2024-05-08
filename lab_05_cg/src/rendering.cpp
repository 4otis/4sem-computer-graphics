#include "rendering.h"

error_t render_point(render_t &data, point_t &point, QColor color) {
    error_t rc = SUCCESS;

    QPixmap pixmap = QPixmap(data.width, data.height);
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);

    data.p = &painter;
    data.p->setPen(color);

    data.p->drawPoint(point.x, point.y);

    if (rc == SUCCESS)
        data.scene->addPixmap(pixmap);

    return rc;
}

error_t render_edge(render_t &data, point_t &p1, point_t &p2) {
    error_t rc = SUCCESS;

    QPixmap pixmap = QPixmap(data.width, data.height);
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);

    data.p = &painter;
    data.p->setPen(Qt::black);

    data.p->drawLine(QPoint(p1.x, p1.y), QPoint(p2.x, p2.y));

    if (rc == SUCCESS)
        data.scene->addPixmap(pixmap);

    return rc;
}

error_t render_all_connecting_edges(render_t &data, points_t &points) {
    return render_edge(data, points.arr[0], points.arr[points.alen - 1]);
}
