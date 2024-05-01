#include "rendering.h"

render_circle_canonic(render_t &data, circle_t &circle) {}

error_t render_circle(render_t &data, circle_t &circle) {
    error_t rc = SUCCESS;

    if (is_circle_empty(circle))
        rc = CIRCLE_NOT_BUILDED;
    else {
        QList<point_t> points;
        switch (data.algorithm) {
        case CANONIC:
            render_circle_canonic(data, circle);
            break;
        default:
            break;
        }
    }

    return rc;
}
