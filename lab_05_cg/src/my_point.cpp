#include "my_point.h"

points_t init_points() {
    points_t tmp;
    tmp.arr = nullptr;
    tmp.alen = 0;
    tmp.capacity = 0;
    tmp.color = QColor(Qt::black);
    return tmp;
}

error_t alloc_points(points_t &points, size_t amount) {
    error_t rc = SUCCESS;

    point_t *tmp = (point_t *)realloc(points.arr, sizeof(point_t) * amount);
    if (!tmp)
        rc = MEMORY_ALLOCATION_ERROR;
    else {
        points.arr = tmp;
        points.capacity = amount;
    }
    return rc;
}

void destroy_points(points_t &points) {
    points.alen = 0;
    points.capacity = 0;
    free(points.arr);
}

bool is_points_empty(points_t &points) {
    if (points.arr)
        return false;
    return true;
}

error_t add_point(points_t &points, point_t &point) {
    error_t rc = SUCCESS;

    if (is_points_empty(points) || points.capacity == points.alen)
        rc = alloc_points(points, points.capacity + 1);

    if (rc == SUCCESS)
        points.arr[points.alen++] = point;

    return rc;
}
