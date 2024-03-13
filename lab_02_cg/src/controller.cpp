#include "controller.h"

error_t action_handler(request_t &req) {
    static model_t model = init_model();
    static model_t model_base = init_model();
    static model_t model_prev = init_model();

    error_t rc = SUCCESS;

    switch (req.action) {
    case BUILD:
        rc = build_model(model, req.build_data);

        if (rc == SUCCESS)
            rc = build_model(model_base, req.build_data);

        if (rc == SUCCESS)
            rc = build_model(model_prev, req.build_data);

        break;
    case MOVE:
        rc = copy_model(model_prev, model);

        if (rc == SUCCESS)
            rc = move_model(model, req.move_data);

        break;
    case ROTATE:
        rc = copy_model(model_prev, model);

        if (rc == SUCCESS)
            rc = rotate_model(model, req.rotate_data);

        break;
    case SCALE:
        rc = copy_model(model_prev, model);

        if (rc == SUCCESS)
            rc = scale_model(model, req.scale_data);

        break;
    case RESET:
        rc = copy_model(model, model_base);
        break;
    case PREV:
        rc = swap_models(model, model_prev);
        break;
    case RENDER:
        rc = render_model(model, req.render_data);

        if (rc == SUCCESS)
            render_extras(req.render_data);

        break;
    default:
        break;
    }

    return rc;
}
