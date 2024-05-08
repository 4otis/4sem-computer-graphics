#ifndef ERRORCODES_H
#define ERRORCODES_H

enum errors {
    SUCCESS,
    MEMORY_ALLOCATION_ERROR

};
using error_t = enum errors;

void show_error(error_t error_code);

#endif // ERRORCODES_H
