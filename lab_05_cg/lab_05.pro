QT       += core gui
QT       += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

DEPENDPATH += ./src
INCLUDEPATH += ./inc

SOURCES += \
    src/errorcodes.cpp \
    src/mainwindow.cpp \
    src/main.cpp \
    src/my_point.cpp \
    src/rendering.cpp

HEADERS += \
    inc/errorcodes.h \
    inc/mainwindow.h \
    inc/my_point.h \
    inc/mygraphicsview.h \
    inc/rendering.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
