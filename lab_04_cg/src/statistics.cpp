#include <QDebug>
#include <QtTypes>
#include <chrono>

#include "rendering.h"
#include "statistics.h"

#define TIMES 100

void stat_canonic_circle(circle_t &circle) {

    int powered_r = circle.radius * circle.radius;

    double limit = round((double)circle.radius / sqrt(2));

    for (double x = 0.; x <= limit; ++x) {
        double y = sqrt(powered_r - x * x);
        (circle.centerX + x, circle.centerY + y);
    }
}

void stat_param_circle(circle_t &circle) {

    double step = (double)1 / (double)circle.radius;

    for (double angle = 0.; angle <= M_PI_4 + step; angle += step)
        (circle.centerX + circle.radius * cos(angle),
         circle.centerY + circle.radius * sin(angle));
}

void stat_midpoint_circle(circle_t &circle) {

    double x = circle.radius;
    double y = 0;
    double delta = 1 - x;

    while (x >= y) {
        (circle.centerX + x, circle.centerY + y);
        ++y;

        if (delta > 0) {
            --x;
            delta -= 2 * x + 1;
        }

        delta += 2 * y + 1;
    }
}

void stat_bresenham_circle(circle_t &circle) {

    int x = 0;
    int y = circle.radius;
    int f = 1 - circle.radius;
    int incrE = 3, incrSE = 5 - 2 * circle.radius;

    (circle.centerX + x, circle.centerY + y);
    while (x <= y) {
        if (f > 0) {
            --y;
            f += incrSE;
            incrSE += 4;
        } else {
            f += incrE;
            incrSE += 2;
        }
        incrE += 2;
        ++x;
        (circle.centerX + x, circle.centerY + y);
    }
}

qreal get_time_canonic_circle(circle_t &circle) {
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    for (size_t i = 0; i < TIMES; ++i)
        stat_canonic_circle(circle);

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    return (qreal)(std::chrono::duration_cast<std::chrono::microseconds>(end - begin)
                       .count()) /
           TIMES;
}

qreal get_time_param_circle(circle_t &circle) {
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    for (size_t i = 0; i < TIMES; ++i) {
        stat_param_circle(circle);
    }
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    return (qreal)(std::chrono::duration_cast<std::chrono::microseconds>(end - begin)
                       .count()) /
           TIMES;
}

qreal get_time_midpoint_circle(circle_t &circle) {
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    for (size_t i = 0; i < TIMES; ++i)
        stat_midpoint_circle(circle);

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    return (qreal)(std::chrono::duration_cast<std::chrono::microseconds>(end - begin)
                       .count()) /
           TIMES;
}

qreal get_time_bresenham_circle(circle_t &circle) {
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    for (size_t i = 0; i < TIMES; ++i)
        stat_bresenham_circle(circle);

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    return (qreal)(std::chrono::duration_cast<std::chrono::microseconds>(end - begin)
                       .count()) /
           TIMES;
}

void show_time_bar_circles(QHBoxLayout *layout) {
    circle_t circle = init_circle();

    size_t min_r = 1000, max_r = 10000;
    size_t step = 100;

    QPen pen;
    pen.setWidthF(1.3);

    QChart *chart = new QChart();
    chart->setTitle("Графики временных замеров (окружн.)");
    chart->legend()->setAlignment(Qt::AlignTop);

    QLineSeries *canonicSeries = new QLineSeries();
    pen.setStyle(Qt::SolidLine);
    pen.setColor(Qt::blue);
    canonicSeries->setPen(pen);
    for (size_t r = min_r; r <= max_r; r += step) {
        circle.radius = r;
        canonicSeries->append(r, get_time_canonic_circle(circle));
    }
    canonicSeries->setName("Каноническое уравнение");

    QLineSeries *paramSeries = new QLineSeries();
    pen.setStyle(Qt::DashDotLine);
    pen.setColor(Qt::green);
    paramSeries->setPen(pen);
    for (size_t r = min_r; r <= max_r; r += step) {
        circle.radius = r;
        paramSeries->append(r, get_time_param_circle(circle));
    }
    paramSeries->setName("Параметрическое уравнение");

    QLineSeries *midpointSeries = new QLineSeries();
    pen.setStyle(Qt::SolidLine);
    pen.setColor(Qt::red);
    midpointSeries->setPen(pen);
    for (size_t r = min_r; r <= max_r; r += step) {
        circle.radius = r;
        midpointSeries->append(r, get_time_midpoint_circle(circle));
    }
    midpointSeries->setName("Алгоритм средней точки");

    QLineSeries *bresenhamSeries = new QLineSeries();
    pen.setStyle(Qt::DotLine);
    pen.setColor(Qt::darkMagenta);
    bresenhamSeries->setPen(pen);
    for (size_t r = min_r; r <= max_r; r += step) {
        circle.radius = r;
        bresenhamSeries->append(r, get_time_bresenham_circle(circle));
    }
    bresenhamSeries->setName("Алгоритм Брезенхема");

    chart->addSeries(canonicSeries);
    chart->addSeries(paramSeries);
    chart->addSeries(midpointSeries);
    chart->addSeries(bresenhamSeries);

    chart->createDefaultAxes();
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignRight);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    layout->addWidget(chartView);
}

void stat_canonic_ellipse(ellipse_t &ellipse) {

    int powered_rX = ellipse.rX * ellipse.rX;
    int powered_rY = ellipse.rY * ellipse.rY;

    int limit = int(ellipse.centerX +
                    ((double)ellipse.rX / sqrt(1 + ((double)powered_rY / powered_rX))));

    for (int x = ellipse.centerX; x <= limit; ++x) {
        int y = round(
            (double)sqrt(powered_rX * powered_rY -
                         (x - ellipse.centerX) * (x - ellipse.centerX) * powered_rY) /
                (double)ellipse.rX +
            ellipse.centerY);
    }

    limit = int(ellipse.centerY +
                ((double)ellipse.rY / sqrt(1 + ((double)powered_rX / powered_rY))));

    for (int y = limit; y >= ellipse.centerY; --y) {
        int x = round(sqrt(powered_rX * powered_rY -
                           (y - ellipse.centerY) * (y - ellipse.centerY) * powered_rX) /
                          (double)ellipse.rY +
                      ellipse.centerX);
    }
}

void stat_param_ellipse(ellipse_t &ellipse) {

    double step = (double)1 / (double)(ellipse.rX > ellipse.rY ? ellipse.rX : ellipse.rY);

    for (double angle = 0.; angle <= M_PI_2; angle += step)

        (ellipse.centerX + ellipse.rX * cos(angle),
         ellipse.centerY + ellipse.rY * sin(angle));
}

void stat_midpoint_ellipse(ellipse_t &ellipse) {

    double x = 0.;
    double y = ellipse.rY;

    double powered_rX = ellipse.rX * ellipse.rX;
    double powered_rY = ellipse.rY * ellipse.rY;

    double delta = powered_rY - powered_rX * powered_rY + 0.25 * powered_rX;
    double dx = 2 * powered_rY * x;
    double dy = 2 * powered_rX * y;

    while (dx <= dy) {
        (ellipse.centerX + x, ellipse.centerY + y);

        ++x;
        dx += 2 * powered_rY;

        if (delta >= 0) {
            --y;
            dy -= 2 * powered_rX;
            delta -= dy;
        }

        delta += dx + powered_rY;
    }

    delta = powered_rY * (x + 0.5) * (x * 0.5) + powered_rX * (y - 1) * (y - 1) -
            powered_rX * powered_rY;

    while (y >= 0) {
        (ellipse.centerX + x, ellipse.centerY + y);

        --y;
        dy -= 2 * powered_rX;

        if (delta <= 0) {
            ++x;
            dx += 2 * powered_rY;
            delta += dx;
        }

        delta -= dy - powered_rX;
    }
}

void stat_bresenham_ellipse(ellipse_t &ellipse) {

    double x = 0., y = ellipse.rY;

    double powered_rX = ellipse.rX * ellipse.rX;
    double powered_rY = ellipse.rY * ellipse.rY;

    double delta = powered_rY - powered_rX * (2 * ellipse.rY + 1);

    while (y >= 0) {
        (ellipse.centerX + x, ellipse.centerY + y);

        if (delta < 0) {
            auto temp = 2 * delta + powered_rX * (2 * y - 1);
            ++x;
            delta += powered_rY * (2 * x + 1);
            if (temp > 0) {
                --y;
                delta += powered_rX * (-2 * y + 1);
            }
        } else if (0 == delta) {
            ++x;
            --y;
            delta += powered_rY * (2 * x + 1) + (1 - 2 * y) * powered_rX;
        } else {
            auto temp = 2 * delta + powered_rY * (-2 * x - 1);
            --y;
            delta += powered_rX * (-2 * y + 1);
            if (temp < 0) {
                ++x;
                delta += powered_rY * (2 * x + 1);
            }
        }
    }
}

qreal get_time_canonic_ellipse(ellipse_t &ellipse) {
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    for (size_t i = 0; i < TIMES; ++i)
        stat_canonic_ellipse(ellipse);

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    return (qreal)(std::chrono::duration_cast<std::chrono::microseconds>(end - begin)
                       .count()) /
           TIMES;
}

qreal get_time_param_ellipse(ellipse_t &ellipse) {
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    for (size_t i = 0; i < TIMES; ++i) {
        stat_param_ellipse(ellipse);
    }
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    return (qreal)(std::chrono::duration_cast<std::chrono::microseconds>(end - begin)
                       .count()) /
           TIMES;
}

qreal get_time_midpoint_ellipse(ellipse_t &ellipse) {
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    for (size_t i = 0; i < TIMES; ++i)
        stat_midpoint_ellipse(ellipse);

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    return (qreal)(std::chrono::duration_cast<std::chrono::microseconds>(end - begin)
                       .count()) /
           TIMES;
}

qreal get_time_bresenham_ellipse(ellipse_t &ellipse) {
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    for (size_t i = 0; i < TIMES; ++i)
        stat_bresenham_ellipse(ellipse);

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    return (qreal)(std::chrono::duration_cast<std::chrono::microseconds>(end - begin)
                       .count()) /
           TIMES;
}

void show_time_bar_ellipses(QHBoxLayout *layout) {
    ellipse_t ellipse = init_ellipse();

    size_t min_r = 1000, max_r = 10000;
    size_t step = 100;

    QPen pen;
    pen.setWidthF(1.3);

    QChart *chart = new QChart();
    chart->setTitle("Графики временных замеров (эллипс.)");
    chart->legend()->setAlignment(Qt::AlignTop);

    QLineSeries *canonicSeries = new QLineSeries();
    pen.setStyle(Qt::SolidLine);
    pen.setColor(Qt::blue);
    canonicSeries->setPen(pen);
    for (size_t r = min_r; r <= max_r; r += step) {
        ellipse.rX = r;
        ellipse.rY = r;
        canonicSeries->append(r, get_time_canonic_ellipse(ellipse));
    }
    canonicSeries->setName("Каноническое уравнение");

    QLineSeries *paramSeries = new QLineSeries();
    pen.setStyle(Qt::DashDotLine);
    pen.setColor(Qt::green);
    paramSeries->setPen(pen);
    for (size_t r = min_r; r <= max_r; r += step) {
        ellipse.rX = r;
        ellipse.rY = r;
        paramSeries->append(r, get_time_param_ellipse(ellipse));
    }
    paramSeries->setName("Параметрическое уравнение");

    QLineSeries *midpointSeries = new QLineSeries();
    pen.setStyle(Qt::SolidLine);
    pen.setColor(Qt::red);
    midpointSeries->setPen(pen);
    for (size_t r = min_r; r <= max_r; r += step) {
        ellipse.rX = r;
        ellipse.rY = r;
        midpointSeries->append(r, get_time_midpoint_ellipse(ellipse));
    }
    midpointSeries->setName("Алгоритм средней точки");

    QLineSeries *bresenhamSeries = new QLineSeries();
    pen.setStyle(Qt::DotLine);
    pen.setColor(Qt::darkMagenta);
    bresenhamSeries->setPen(pen);
    for (size_t r = min_r; r <= max_r; r += step) {
        ellipse.rX = r;
        ellipse.rY = r;
        bresenhamSeries->append(r, get_time_bresenham_ellipse(ellipse));
    }
    bresenhamSeries->setName("Алгоритм Брезенхема");

    chart->addSeries(canonicSeries);
    chart->addSeries(paramSeries);
    chart->addSeries(midpointSeries);
    chart->addSeries(bresenhamSeries);

    chart->createDefaultAxes();
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignRight);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    layout->addWidget(chartView);
}
