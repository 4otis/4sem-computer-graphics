#include "model.h"
#include <cstdbool>

model_t &init_model() {
    static model_t tmp;
    tmp.points_arr = nullptr;
    tmp.points_alen = 0;
    return tmp;
}

bool is_model_empty(model_t &model) {
    if (!model.points_arr)
        return true;
    return false;
}

error_t alloc_model(model_t &model, size_t points_amount) {
    model.points_arr = alloc_points(points_amount);
    if (!model.points_arr)
        return MEMORY_ALLOCATION_ERROR;
    return SUCCESS;
}

void free_model(model_t &model) { destroy_points(model.points_arr); }

error_t build_model(model_t &model, build_t &data) {
    destroy_points(model.points_arr);

    model.points_alen = 360 * get_amount_of_rotations_for_epicycloid(data.a, data.b) + 4;
    error_t rc = alloc_model(model, model.points_alen);

    if (rc == SUCCESS)
        calc_all_points(data, model.points_arr, model.points_alen);

    return rc;
}

error_t move_model(model_t &model, move_t &data) {
    error_t rc = move_all_points(data, model.points_arr, model.points_alen);
    return rc;
}

error_t rotate_model(model_t &model, rotate_t &data) {
    error_t rc = rotate_all_points(data, model.points_arr, model.points_alen);
    return rc;
}

error_t scale_model(model_t &model, scale_t &data) {
    error_t rc = scale_all_points(data, model.points_arr, model.points_alen);
    return rc;
}

error_t copy_model(model_t &dst, model_t &src) {
    if (is_model_empty(dst) || is_model_empty(src))
        return NO_MODEL_ERROR;

    for (size_t i = 0; i < src.points_alen; i++)
        dst.points_arr[i] = src.points_arr[i];

    return SUCCESS;
}

error_t swap_models(model_t &m1, model_t &m2) {
    if (is_model_empty(m1) || is_model_empty(m2))
        return NO_MODEL_ERROR;

    model_t tmp = m2;
    m2 = m1;
    m1 = tmp;

    return SUCCESS;
}
