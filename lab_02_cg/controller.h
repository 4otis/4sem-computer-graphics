#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "errorcodes.h"
#include "model.h"
#include "rendering_model.h"

enum action { BUILD, MOVE, ROTATE, SCALE, RESET, PREV, RENDER };
using action_t = enum action;

struct request {
    action_t action;
    union {
        build_t build_data;
        move_t move_data;
        rotate_t rotate_data;
        scale_t scale_data;
        render_t render_data;
    };
};
using request_t = struct request;

error_t action_handler(request_t &req);

#endif
