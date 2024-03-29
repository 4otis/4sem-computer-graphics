#include "errorcodes.h"

void show_error(error_t error_code) {
    switch (error_code) {
    case MEMORY_ALLOCATION_ERROR:
        QMessageBox::critical(NULL, "Ошибка", "Не удалось выделить память.");
        break;
    case WRONG_DATA_ERROR:
        QMessageBox::critical(NULL, "Ошибка", "Некорректный формат данных, описывающих фигуру.");
        break;
    case NO_MODEL_ERROR:
        QMessageBox::critical(NULL, "Ошибка", "Необходимо сначала построить фигуру.");
        break;
    default:
        QMessageBox::critical(NULL, "Ошибка", "Smth goes wrong (;-( )");
    }
}
