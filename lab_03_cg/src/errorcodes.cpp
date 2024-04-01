#include "errorcodes.h"
#include <QMessageBox>

void show_error(error_t error_code) {
    switch (error_code) {
    case MEMORY_ALLOCATION_ERROR:
        QMessageBox::critical(NULL, "Ошибка", "Не удалось выделить память.");
        break;
    case WRONG_ANGLE_ERROR:
        QMessageBox::critical(NULL, "Ошибка",
                              "Значение шага поворота линий "
                              "должно быть отлично от нуля и"
                              " по модулю <= 360 градусов.");
        break;
    case LINES_NOT_BUILDED:
        QMessageBox::critical(NULL, "Ошибка", "Необходимо сначала построить линию/линии.");
        break;
    case INVALID_REQUEST_ERROR:
        QMessageBox::critical(NULL, "Ошибка", "Поступивший запрос не является валидным.");
        break;
    }
}
