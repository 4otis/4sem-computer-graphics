#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "errorcodes.h"
#include "geometry.h"
#include "lines.h"
#include "rendering_lines.h"

enum actions { CREATE_LINE, CREATE_LINES, CHANGE_COLOR, RENDER };
using action_t = enum actions;

struct request {
    action_t action;

    build_line_t build_line;
    build_lines_t build_lines;
    change_color_t new_color;
    render_t render;
};
using request_t = struct request;

error_t handle_action(request_t &req);

#endif // CONTROLLER_H
