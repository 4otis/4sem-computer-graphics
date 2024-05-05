#include "my_circle.h"

circle_t init_circle() {
    circle_t tmp;
    tmp.centerX = 0;
    tmp.centerY = 0;
    tmp.radius = 0;
    tmp.color = QColor(Qt::black);
    return tmp;
}

// bool is_circle_empty(circle_t &circle) { return ((circle.radius == 0) ? true : false);
// }

bool is_circle_empty(circle_t &circle) {
    if (circle.radius == 0)
        return true;
    return false;
}

error_t build_circle(circle_t &circle, build_circle_t &data) {
    error_t rc = SUCCESS;

    circle.centerX = data.centerX;
    circle.centerY = data.centerY;
    circle.radius = data.radius;
    circle.color = data.color;

    return rc;
}

error_t alloc_circles(circles_t &circles, size_t amount) {
    error_t rc = SUCCESS;

    circles.arr = (circle_t *)malloc(sizeof(circle_t) * amount);
    if (!circles.arr)
        rc = MEMORY_ALLOCATION_ERROR;

    return rc;
}

void destroy_circles(circles_t &circles) { free(circles.arr); }

circles_t init_circles() {
    circles_t tmp;
    tmp.arr = nullptr;
    tmp.alen = 0;
    tmp.color = QColor(Qt::black);
    return tmp;
}

bool is_circles_empty(circles_t &circles) {
    if (circles.arr)
        return false;
    return true;
}

error_t build_circles(circles_t &circles, build_circles_t &data) {
    error_t rc = SUCCESS;

    if (is_circles_empty(circles))
        rc = MEMORY_ALLOCATION_ERROR;
    else {
        circles.arr[0].centerX = data.centerX;
        circles.arr[0].centerY = data.centerY;
        circles.arr[0].radius = data.basic_radius;

        for (size_t i = 1; i < data.amount; ++i) {
            circles.arr[i].centerX = data.centerX;
            circles.arr[i].centerY = data.centerY;
            circles.arr[i].radius = circles.arr[i - 1].radius + data.step;
        }

        circles.alen = data.amount;
        circles.color = data.color;
    }

    return rc;
}
