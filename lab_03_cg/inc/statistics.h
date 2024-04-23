#ifndef STATISTICS_H
#define STATISTICS_H

#include "draw_algorithms.h"
#include <QBarSet>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QtCharts>

// struct my_stat
// {
//     QLayoutItem *ParentLayout;
// };

void show_time_bar(QHBoxLayout *layout, size_t len);
void show_step_bar(QGridLayout *layout, size_t len);

void get_stat_drawline_algorithms();

#endif // STATISTICS_H
