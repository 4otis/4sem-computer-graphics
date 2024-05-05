#include "my_ellipse.h"

ellipse_t init_ellipse() {
    ellipse_t tmp;
    tmp.centerX = 0;
    tmp.centerY = 0;
    tmp.rX = 0;
    tmp.rY = 0;
    tmp.color = QColor(Qt::black);
}

bool is_ellipse_empty(ellipse_t &ellipse) {
    if (ellipse.rX == 0 && ellipse.rY == 0)
        return true;
    return false;
}

error_t build_ellipse(ellipse_t &ellipse, build_ellipse_t &data) {
    error_t rc = SUCCESS;

    ellipse.centerX = data.centerX;
    ellipse.centerY = data.centerY;
    ellipse.rX = data.rX;
    ellipse.rY = data.rY;
    ellipse.color = data.color;

    return rc;
}

error_t alloc_ellipses(ellipses_t &ellipses, size_t amount) {
    error_t rc = SUCCESS;

    ellipses.arr = (ellipse_t *)malloc(sizeof(ellipse_t) * amount);
    if (!ellipses.arr)
        rc = MEMORY_ALLOCATION_ERROR;

    return rc;
}

void destroy_ellipses(ellipses_t &ellipses) { free(ellipses.arr); }

ellipses_t init_ellipses() {
    ellipses_t tmp;
    tmp.arr = nullptr;
    tmp.alen = 0;
    tmp.color = QColor(Qt::black);
    return tmp;
}

bool is_ellipses_empty(ellipses_t &ellipses) {
    if (ellipses.arr)
        return false;
    return true;
}
error_t build_ellipses(ellipses_t &ellipses, build_ellipses_t &data) {
    error_t rc = SUCCESS;

    if (is_ellipses_empty(ellipses))
        rc = MEMORY_ALLOCATION_ERROR;
    else {
        ellipses.arr[0].centerX = data.centerX;
        ellipses.arr[0].centerY = data.centerY;
        ellipses.arr[0].rX = data.basic_rX;
        ellipses.arr[0].rY = data.basic_rY;

        for (size_t i = 1; i < data.amount; ++i) {
            ellipses.arr[i].centerX = data.centerX;
            ellipses.arr[i].centerY = data.centerY;
            ellipses.arr[0].rX = ellipses.arr[i - 1].rX + data.step;
            ellipses.arr[0].rY = ellipses.arr[i - 1].rY + data.step;
        }

        ellipses.alen = data.amount;
        ellipses.color = data.color;
    }

    return rc;
}
