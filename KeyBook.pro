#-------------------------------------------------
#
# Project created by QtCreator 2014-04-16T21:41:02
#
#-------------------------------------------------

QT       += core gui widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = KeyBook
TEMPLATE = app
LIBS += -lcrypto -lssl



SOURCES += main.cpp\
        mainwindow.cpp \
    parser.cpp \
    list.cpp \
    cripter.cpp \
    base64.cpp \
    cryptfiledevice.cpp

HEADERS  += mainwindow.h \
    parser.h \
    list.h \
    cripter.h \
    base64.h \
    cryptfiledevice.h

FORMS    += mainwindow.ui
