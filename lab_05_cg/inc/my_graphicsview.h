#ifndef MY_GRAPHICSVIEW_H
#define MY_GRAPHICSVIEW_H

#include <QGraphicsView>

class MyGraphicsView : public QGraphicsView {
    Q_OBJECT

public:
    MyGraphicsView(QWidget *parent = nullptr) : QGraphicsView(parent) {}

protected:
    void mousePressEvent(QMouseEvent *event);
};

#endif // MYGRAPHICSVIEW_H
