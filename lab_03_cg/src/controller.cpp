#include "controller.h"
#include <QDebug>

error_t handle_action(request_t &req) {
    static lines_t lines = init_lines();
    error_t rc = SUCCESS;

    switch (req.action) {
    case CREATE_LINE:
        rc = create_line(lines, req.build_line);
        break;
    case CREATE_LINES:
        rc = create_lines(lines, req.build_lines);
        break;
    case RENDER:
        rc = render_lines(req.render, lines);
        break;
    case CHANGE_COLOR:
        rc = change_fill_color(lines, req.new_color);
        break;
    default:
        rc = INVALID_REQUEST_ERROR;
        break;
    }

    return rc;
}
