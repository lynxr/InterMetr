#-------------------------------------------------
#
# Project created by QtCreator 2012-04-14T01:41:33
#
#-------------------------------------------------

QT       += core gui

TARGET = CircleMetr
TEMPLATE = app

LIBS += /usr/lib/libqwt.so

SOURCES += main.cpp\
        mainclass.cpp \
    picture.cpp \
    postoperations.cpp \
    parser.cpp \
    graphics.cpp

HEADERS  += mainclass.h \
    picture.h \
    postoperations.h \
    parser.h \
    graphics.h

FORMS    += mainclass.ui \
    postoperations.ui \
    graphics.ui

TRANSLATIONS = ru_RU.ts
