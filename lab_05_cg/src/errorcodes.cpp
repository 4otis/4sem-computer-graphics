#include "errorcodes.h"
#include <QMessageBox>

void show_error(error_t error_code) {
    switch (error_code) {
    case MEMORY_ALLOCATION_ERROR:
        QMessageBox::critical(NULL, "Ошибка", "Не удалось выделить память.");
        break;
    }
}
