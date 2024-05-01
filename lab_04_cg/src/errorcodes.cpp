#include "errorcodes.h"
#include <QMessageBox>

void show_error(error_t error_code) {
    switch (error_code) {
    case MEMORY_ALLOCATION_ERROR:
        QMessageBox::critical(NULL, "Ошибка", "Не удалось выделить память.");
        break;
    case CIRCLE_NOT_BUILDED:
        QMessageBox::critical(NULL, "Ошибка", "Необходимо сначала построить окружность.");
        break;
    case CIRCLES_NOT_BUILDED:
        QMessageBox::critical(NULL, "Ошибка",
                              "Необходимо сначала построить спектор окружностей.");
        break;
    case ELLIPSE_NOT_BUILDED:
        QMessageBox::critical(NULL, "Ошибка", "Необходимо сначала построить эллипс.");
        break;
    case ELLIPSES_NOT_BUILDED:
        QMessageBox::critical(NULL, "Ошибка",
                              "Необходимо сначала построить спектор эллипсов.");
        break;
    case INVALID_REQUEST_ERROR:
        QMessageBox::critical(NULL, "Ошибка", "Поступивший запрос не является валидным.");
        break;
    case INVALID_LINE_COORDS_ERROR:
        QMessageBox::critical(NULL, "Ошибка", "Невырожденный отрезок.");
        break;
    }
}
