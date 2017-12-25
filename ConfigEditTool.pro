#-------------------------------------------------
#
# Project created by QtCreator 2017-12-25T19:01:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ConfigEditTool
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += _USE_MATH_DEFINES

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    dollarone.cpp \
    qgraphicsviewwithmouseevent.cpp \
    statemachine.cpp \
    gestureitem.cpp \
    gesturetreeitem.cpp

HEADERS  += mainwindow.h \
    dollarone.h \
    publictools.h \
    qgraphicsviewwithmouseevent.h \
    statemachine.h \
    gestureitem.h \
    gesturetreeitem.h

FORMS    += mainwindow.ui

# OpenCV 3.1.0 config
INCLUDEPATH += "C:/Libs/OpenCV31/opencv/build/include"
CONFIG(debug)
{
    LIBS += "C:/Libs/OpenCV31/opencv/build/x64/vc14/lib/opencv_world310d.lib"
}
CONFIG(release)
{
    LIBS += "C:/Libs/OpenCV31/opencv/build/x64/vc14/lib/opencv_world310.lib"
}

# Windows Kits
LIBS += "C:/Program Files (x86)/Windows Kits/8.1/Lib/winv6.3/um/x64/user32.lib"
