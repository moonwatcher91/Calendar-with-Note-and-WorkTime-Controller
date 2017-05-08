#-------------------------------------------------
#
# Project created by QtCreator 2017-05-02T14:10:01
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = organizer
TEMPLATE = app

TRANSLATIONS += QtLanguage_ru.ts

SOURCES += main.cpp \
    mycalendar.cpp \
    mycalendarwidget.cpp \
    mynote.cpp \
    myworktime.cpp \
    mylabel.cpp \
    mylistview.cpp \
    mybutton.cpp

HEADERS  += \
    mycalendar.h \
    mycalendarwidget.h \
    mynote.h \
    mystyle.h \
    myworktime.h \
    mylabel.h \
    mylistview.h \
    mybutton.h

RC_FILE = icon.rc

RESOURCES += \
    res_pixmap.qrc

QMAKE_CXXFLAGS += -std=c++11
