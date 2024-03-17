#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "errorcodes.h"
#include "lines.h"

enum actions { BUILD_LINE, BUILD_LINES, CHANGE_COLOR };
using action_t = enum actions;

struct request {
    action_t action;
    union action_data {
        build_line_t build_line;
        build_lines_t build_lines;
    };
};

error_t build_model();

#endif // CONTROLLER_H
