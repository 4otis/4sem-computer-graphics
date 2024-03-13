#ifndef MODEL_H
#define MODEL_H

#include "geometry.h"
#include <errorcodes.h>

struct my_model {
    point_t *points_arr;
    size_t points_alen;
};
using model_t = struct my_model;

model_t &init_model();
error_t build_model(model_t &model, build_t &data);
error_t move_model(model_t &model, move_t &data);
error_t rotate_model(model_t &model, rotate_t &data);
error_t scale_model(model_t &model, scale_t &data);
error_t copy_model(model_t &dst, model_t &src);
error_t swap_models(model_t &m1, model_t &m2);

#endif
