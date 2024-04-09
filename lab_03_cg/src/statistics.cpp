#include "statistics.h"
#include "draw_algorithms.h"
#include "geometry.h"
#include <QDebug>
#include <QtTypes>
#include <chrono>
// #include <QtCharts>

#define ANGLES_AMOUNT 91

qreal get_time_drawline_dda(line_t &line) {
    size_t tmp = 0;
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    for (size_t i = 0; i < 1000; ++i)
        draw_line_dda(line, tmp, true);

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    return (qreal)(std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()) / 1000;
}

qreal get_time_drawline_bresenham_int(line_t &line) {
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    for (size_t i = 0; i < 1000; ++i) {
        draw_line_bresenham_int(line, true);
    }
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    return (qreal)(std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()) / 1000;
}

qreal get_time_drawline_bresenham_float(line_t &line) {
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    for (size_t i = 0; i < 1000; ++i)
        draw_line_bresenham_float(line, true);

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    return (qreal)(std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()) / 1000;
}

qreal get_time_drawline_bresenham_smooth(line_t &line) {
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    for (size_t i = 0; i < 1000; ++i)
        draw_line_bresenham_smooth(line, true);

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    return (qreal)(std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()) / 1000;
}

void count_steps_line_dda(size_t &steps, line_t &line) {
    float x1 = line.p1.x, y1 = line.p1.y;
    float x2 = line.p2.x, y2 = line.p2.y;

    int dx = (int)x2 - x1;
    int dy = (int)y2 - y1;

    int step = (fabs(dx) > fabs(dy)) ? fabs(dx) : fabs(dy);

    float x_inc = (float)dx / step;
    float y_inc = (float)dy / step;

    for (int i = 0; i < step; i++) {
        if (round(x1 + x_inc) != round(x1) && round(y1 + y_inc) != round(y1))
            ++steps;

        x1 += x_inc;
        y1 += y_inc;
    }
}

void count_steps_line_bresenham_int(size_t &steps, line_t &line) {
    int x1 = (int)line.p1.x, y1 = (int)line.p1.y;
    int x2 = (int)line.p2.x, y2 = (int)line.p2.y;

    const int deltaX = fabs(x2 - x1);
    const int deltaY = fabs(y2 - y1);

    const int signX = x1 < x2 ? 1 : -1;
    const int signY = y1 < y2 ? 1 : -1;
    int error = deltaX - deltaY;

    int prev_x = x1, prev_y = y1;

    while (x1 != x2 || y1 != y2) {

        if (prev_x != x1 && prev_y != y1) {
            ++steps;
            prev_x = x1;
            prev_y = y1;
        }

        int error2 = error * 2;
        if (error2 > -deltaY) {
            error -= deltaY;
            x1 += signX;
        }
        if (error2 < deltaX) {
            error += deltaX;
            y1 += signY;
        }
    }
}

void count_steps_line_bresenham_float(size_t &steps, line_t &line) {
    float x1 = line.p1.x, y1 = line.p1.y;
    float x2 = line.p2.x, y2 = line.p2.y;

    float dx = x2 - x1;
    float dy = y2 - y1;

    float fsteps = std::max(fabs(dx), fabs(dy));

    float xIncrement = dx / fsteps;
    float yIncrement = dy / fsteps;
    float x = x1;
    float y = y1;

    float prev_x = x, prev_y = y;

    for (int i = 0; i <= steps; i++) {
        if (round(prev_x) != round(x) && round(prev_y) != round(y)) {
            ++steps;
            prev_x = x;
            prev_y = y;
        }

        x += xIncrement;
        y += yIncrement;
    }
}

void count_steps_line_bresenham_smooth(size_t &steps, line_t &line) {
    int x1 = (int)line.p1.x, y1 = (int)line.p1.y;
    int x2 = (int)line.p2.x, y2 = (int)line.p2.y;

    int deltaX = fabs(x2 - x1);
    int deltaY = fabs(y2 - y1);

    int signX = x1 < x2 ? 1 : -1;
    int signY = y1 < y2 ? 1 : -1;

    float intensivity = 1;
    int was_swaped;

    float m = (float)deltaY / deltaX;
    if (m > 1) {
        m = (float)1 / (float)m;

        was_swaped = 2;
    } else
        was_swaped = 0;

    m *= intensivity;
    float w = intensivity - m;
    float e = intensivity / 2;

    int x = x1, y = y1;

    int prev_x = x1, prev_y = y1;

    while (x != x2 || y != y2) {
        if (e < w) {
            if (was_swaped) // dx < dy
                y += signY;
            else
                x += signX;
            e += m;
        } else {
            x += signX;
            y += signY;
            e -= w;
            ++steps;
        }

        if (prev_x != x && prev_y != y) {
            prev_x = x;
            prev_y = y;
            ++steps;
        }
    }
}

void show_time_bar(QHBoxLayout *layout, size_t len) {
    QList<qreal> time_list;

    line_t line;
    line.p1 = {.x = 100, .y = 100};
    line.p2 = {.x = 100, .y = 100 + len};

    time_list.push_back(get_time_drawline_dda(line));
    time_list.push_back(get_time_drawline_bresenham_int(line));
    time_list.push_back(get_time_drawline_bresenham_float(line));
    time_list.push_back(get_time_drawline_bresenham_smooth(line));
    // time_list.push_back(get_time_drawline_wu(line));

    qDebug() << time_list;

    auto set0 = new QBarSet("");
    *set0 << time_list[0] << time_list[1] << time_list[2] << time_list[3];

    QBarSeries *series = new QBarSeries;
    series->append(set0);

    auto chart = new QChart;
    chart->addSeries(series);
    chart->setTitle("Исследование времени работы алгоритмов построения");

    QStringList categories{"ЦДА", "Брезенхем\n(целые)", "Брезенхем(веществ.)", "Брезенхем с устр.ступ."};
    auto axisX = new QBarCategoryAxis;
    axisX->append(categories);

    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    auto axisY = new QValueAxis;
    axisY->setTitleText(QString("Миллисекунды (длина линии = %1 )").arg(len));
    auto min = *std::min_element(time_list.begin(), time_list.end());
    auto max = *std::max_element(time_list.begin(), time_list.end());
    qDebug() << min << max;
    axisY->setRange(0, max);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    layout->addWidget(chartView);
}

void show_step_bar(QGridLayout *layout, size_t len) {
    size_t DDA_steps[ANGLES_AMOUNT] = {0};
    size_t Bresenham_int_steps[ANGLES_AMOUNT] = {0};
    size_t Bresenham_float_steps[ANGLES_AMOUNT] = {0};
    size_t Bresenham_smooth_steps[ANGLES_AMOUNT] = {0};
    size_t angles[ANGLES_AMOUNT] = {0};

    line_t line;
    line.p1 = {.x = 100, .y = 100};
    line.p2 = {.x = 100 + len, .y = 100};

    rotate_t rotation_data;
    rotation_data.angle = 1;
    rotation_data.center_p = line.p1;

    for (size_t cur_angle = 0; cur_angle < ANGLES_AMOUNT; ++cur_angle) {
        angles[cur_angle] = cur_angle;
        count_steps_line_dda(DDA_steps[cur_angle], line);
        count_steps_line_bresenham_int(Bresenham_int_steps[cur_angle], line);
        count_steps_line_bresenham_float(Bresenham_float_steps[cur_angle], line);
        count_steps_line_bresenham_smooth(Bresenham_float_steps[cur_angle], line);
        // draw_line_dda(line, DDA_steps[cur_angle], false);
        rotate_point(line.p2, rotation_data);
    }

    QChart *chart1 = new QChart();
    QLineSeries *DDAseries = new QLineSeries();
    for (quint32 i = 0; i < ANGLES_AMOUNT; i++)
        DDAseries->append(angles[i], DDA_steps[i]);

    chart1->addSeries(DDAseries);
    chart1->setTitle("ЦДА");
    chart1->setMaximumWidth(285);
    chart1->setMaximumHeight(315);
    chart1->createDefaultAxes();
    QChartView *chartView1 = new QChartView(chart1);
    // chartView->setRenderHint(QPainter::Antialiasing);

    QChart *chart2 = new QChart();
    chart2->setTitle("Брезенхем(целые)");
    //, "Брезенхем\n(целые)", "Брезенхем(веществ.)", "Брезенхем с устр.ступ."
    chart2->setMaximumWidth(285);
    chart2->setMaximumHeight(315);
    QLineSeries *Bresenham_int_series = new QLineSeries();
    for (quint32 i = 0; i < ANGLES_AMOUNT; i++)
        Bresenham_int_series->append(angles[i], Bresenham_int_steps[i]);
    chart2->addSeries(Bresenham_int_series);
    chart2->createDefaultAxes();
    QChartView *chartView2 = new QChartView(chart2);

    QChart *chart3 = new QChart();
    chart3->setTitle("Брезенхем(веществ.)");
    //, "Брезенхем\n(целые)", "Брезенхем(веществ.)", "Брезенхем с устр.ступ."
    chart3->setMaximumWidth(285);
    chart3->setMaximumHeight(315);
    QLineSeries *Bresenham_float_series = new QLineSeries();
    for (quint32 i = 0; i < ANGLES_AMOUNT; i++)
        Bresenham_float_series->append(angles[i], Bresenham_float_steps[i]);
    chart3->addSeries(Bresenham_float_series);
    chart3->createDefaultAxes();
    QChartView *chartView3 = new QChartView(chart3);

    QHBoxLayout *l1 = new QHBoxLayout();
    layout->addLayout(l1, 0, 0);
    l1->addWidget(chartView1);
    l1->addWidget(chartView2);
    l1->addWidget(chartView3);

    QChart *chart4 = new QChart();
    chart4->setTitle("Брезенхем с устр.ступ.");
    //, "Брезенхем\n(целые)", "Брезенхем(веществ.)", "Брезенхем с устр.ступ."
    chart4->setMaximumWidth(285);
    chart4->setMaximumHeight(315);
    QLineSeries *Bresenham_smooth_series = new QLineSeries();
    for (quint32 i = 0; i < ANGLES_AMOUNT; i++)
        Bresenham_smooth_series->append(angles[i], Bresenham_smooth_steps[i]);
    chart4->addSeries(Bresenham_smooth_series);
    chart4->createDefaultAxes();
    QChartView *chartView4 = new QChartView(chart4);

    QHBoxLayout *l2 = new QHBoxLayout();
    layout->addLayout(l2, 1, 0);
    l2->addWidget(chartView4);
    // l2->addWidget(chartView5);
    // l2->addWidget(chartView6);
}
