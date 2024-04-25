#ifndef ERRORCODES_H
#define ERRORCODES_H

enum errors {
    SUCCESS,
    MEMORY_ALLOCATION_ERROR,
    CIRCLE_NOT_BUILDED,
    CIRCLES_NOT_BUILDED,
    ELLIPSE_NOT_BUILDED,
    ELLIPSES_NOT_BUILDED,
    INVALID_REQUEST_ERROR,
    INVALID_LINE_COORDS_ERROR
};
using error_t = enum errors;

void show_error(error_t error_code);

#endif // ERRORCODES_H
