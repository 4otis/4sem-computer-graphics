#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "errorcodes.h"
#include "model.h"

enum actions { BUILD, ROTATE };
using action_t = enum actions;

struct request {
    action_t action;
    union action_data {};
};

error_t build_model();

#endif // CONTROLLER_H
