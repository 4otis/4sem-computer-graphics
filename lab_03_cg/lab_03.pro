QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

DEPENDPATH += ./src
INCLUDEPATH += ./inc

SOURCES += \
    src/controller.cpp \
    src/errorcodes.cpp \
    src/geometry.cpp \
    src/lines.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/rendering_lines.cpp

HEADERS += \
    inc/controller.h \
    inc/errorcodes.h \
    inc/geometry.h \
    inc/lines.h \
    inc/mainwindow.h \
    inc/rendering_lines.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
