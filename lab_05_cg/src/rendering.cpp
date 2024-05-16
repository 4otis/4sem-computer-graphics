#include "rendering.h"

error_t render_point(render_t &data, point_t &point, QColor color) {
    error_t rc = SUCCESS;

    QPixmap pixmap = QPixmap(data.width, data.height);
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);

    qDebug() << color;

    data.p = &painter;
    data.p->setPen(color);

    data.p->drawPoint(point.x, point.y);

    data.scene->addPixmap(pixmap);

    return rc;
}

error_t render_edge(render_t &data, point_t &p1, point_t &p2) {
    error_t rc = SUCCESS;

    QPainter painter(&data.pixmap);

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

edges_t get_edges_from_points(points_t &points) {
    edges_t edges;

    // edges.min_y = std::min(points.arr[0].y, points.arr[points.alen - 1].y);
    // edges.max_y = std::max(points.arr[0].y, points.arr[points.alen - 1].y);
    edges.min_x = std::min(points.arr[0].x, points.arr[points.alen - 1].x);
    edges.max_x = std::max(points.arr[0].x, points.arr[points.alen - 1].x);

    edge_t new_edge;
    new_edge = {.p1 = points.arr[points.alen - 1], .p2 = points.arr[0]};
    edges.list.append(new_edge);

    for (size_t i = 0; i < (points.alen - 1); ++i) {
        // if (edges.min_y > points.arr[i].y)
        //     edges.min_y = points.arr[i].y;

        // if (edges.max_y < points.arr[i].y)
        //     edges.max_y = points.arr[i].y;

        if (edges.min_x > points.arr[i].x)
            edges.min_x = points.arr[i].x;

        if (edges.max_x < points.arr[i].x)
            edges.max_x = points.arr[i].x;

        new_edge = {.p1 = points.arr[i], .p2 = points.arr[i + 1]};
        edges.list.append(new_edge);
    }

    return edges;
}

void destroy_buffer(bool **buf, size_t size) {
    if (buf) {
        for (size_t i = 0; i < size && buf[i]; ++i)
            free(buf[i]);
        free(buf);
    }
}

bool **alloc_buffer(size_t rows, size_t columns) {
    bool **tmp = (bool **)malloc(sizeof(bool *) * rows);
    if (tmp)
        for (size_t i = 0; i < columns; ++i) {
            tmp[i] = (bool *)malloc(sizeof(bool) * columns);
            if (!tmp[i]) {
                destroy_buffer(tmp, rows);
                return nullptr;
            }
        }
    return tmp;
}

void init_buffer(bool ***buf, size_t rows, size_t columns) {
    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < columns; ++j)
            (*buf)[i][j] = false;
}

error_t render_fill_by_edges(render_t &data, edges_t &edges) {
    int min_x, max_x, min_y, max_y;

    point_t p;

    max_x = edges.max_x;

    bool **buffer = alloc_buffer(data.height, data.width);
    if (!buffer)
        destroy_buffer(buffer, data.height);

    init_buffer(&buffer, data.height, data.width);

    foreach (edge_t cur_edge, edges.list) {
        min_x = (cur_edge.p1.x <= cur_edge.p2.x) ? cur_edge.p1.x : cur_edge.p2.x;

        if (cur_edge.p1.y <= cur_edge.p2.y) {
            min_y = cur_edge.p1.y;
            max_y = cur_edge.p2.y;
        } else {
            min_y = cur_edge.p2.y;
            max_y = cur_edge.p1.y;
        }

        for (int y = min_y; y < max_y; ++y) {
            for (int x = min_x + 1; x < max_x; ++x) {
                buffer[x][y] = !buffer[x][y];
                p = {.x = x, .y = y};
                render_point(data, p, QColor(((buffer[x][y]) ? Qt::red : Qt::blue)));
                // render_point(data, p, Qt::red);
            }
        }
    }

    return SUCCESS;
}
