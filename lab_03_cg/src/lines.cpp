#include "lines.h"
#include <QDebug>
#include <cstdbool>

lines_t init_lines() {
    lines_t tmp;
    tmp.arr = nullptr;
    tmp.alen = 0;
    tmp.color = QColor(0, 0, 0);

    return tmp;
}

line_t *alloc_lines(size_t len) {
    line_t *tmp = (line_t *)malloc(sizeof(line_t) * len);
    if (!tmp)
        return NULL;

    return tmp;
}

void destroy_lines(lines_t &lines) {
    if (!is_lines_empty(lines))
        free(lines.arr);
}

bool is_lines_empty(lines_t &lines) {
    if (lines.arr)
        return false;
    return true;
}

void add_coords_to_line(lines_t &lines, build_line_t &data) {
    two_points_t points_data;
    points_data = {.p1 = data.p1, .p2 = data.p2};

    add_two_points_to_line(lines.arr[0], points_data);
}

error_t create_line(lines_t &lines, build_line_t &data) {
    error_t rc = SUCCESS;

    lines.alen = 1;
    lines.arr = alloc_lines(lines.alen);

    if (is_lines_empty(lines))
        rc = MEMORY_ALLOCATION_ERROR;
    else {
        add_coords_to_line(lines, data);
        change_lines_color(lines, data.color);
    }

    return rc;
}

void add_coords_to_all_lines(lines_t &lines, build_lines_t &data) {
    two_points_t points_data;
    points_data = {.p1 = data.p1, .p2 = data.p2};
    add_two_points_to_line(lines.arr[0], points_data);

    for (size_t i = 1; i < lines.alen; i++) {
        rotate_two_points(points_data, data.angle);
        add_two_points_to_line(lines.arr[i], points_data);
        qDebug() << lines.arr[i].p1.x << lines.arr[i].p1.x << lines.arr[i].p2.x << lines.arr[i].p2.y;
    }
}

int calc_lines_amount_by_angle(double angle) {
    if (!angle || angle > 360 || angle < -360)
        return 0;
    int res = (int)(360 / angle);
    return ((res > 0) ? res : -res);
}

error_t create_lines(lines_t &lines, build_lines_t &data) {
    error_t rc = SUCCESS;

    int tmp_calc = calc_lines_amount_by_angle(data.angle);
    if (tmp_calc == 0)
        rc = WRONG_ANGLE_ERROR;
    else {
        qDebug() << "alen: " << tmp_calc;
        if ((360 % (int)data.angle) != 0)
            ++tmp_calc;
        lines.alen = tmp_calc;
        qDebug() << "alen: " << tmp_calc;
        lines.arr = alloc_lines(lines.alen);

        if (is_lines_empty(lines))
            rc = MEMORY_ALLOCATION_ERROR;
        else {
            add_coords_to_all_lines(lines, data);
            change_lines_color(lines, data.color);
        }
    }

    return rc;
}

error_t change_lines_color(lines_t &lines, QColor &color) {
    lines.color = color;
    return SUCCESS;
}

error_t change_fill_color(lines_t &lines, change_color_t &data) { return change_lines_color(lines, data.color); }
