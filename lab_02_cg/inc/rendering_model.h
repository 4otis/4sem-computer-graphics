#ifndef RENDERING_MODEL_H
#define RENDERING_MODEL_H

#include <QGraphicsScene>

#include "geometry.h"
#include "model.h"

struct render {
    QGraphicsScene *scene;
    size_t width;
    size_t height;

    point_t rotate_center;
    point_t scale_center;
};
using render_t = struct render;

error_t render_model(model_t &model, render_t &params);
void clear_scene(render_t &params);
void render_extras(render_t &params);

#endif // RENDERING_MODEL_H
