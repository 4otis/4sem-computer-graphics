#ifndef ERRORCODES_H
#define ERRORCODES_H

enum errors { SUCCESS, MEMORY_ALLOCATION_ERROR, WRONG_DATA_ERROR, LINES_NOT_BUILDED };
using error_t = enum errors;

void hello(void);

#endif // ERRORCODES_H
