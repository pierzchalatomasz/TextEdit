#-------------------------------------------------
#
# Project created by QtCreator 2015-06-09T07:52:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TextEdit
TEMPLATE = app


SOURCES += main.cpp\
        textedit.cpp \
    syntaxhighlighter.cpp

HEADERS  += textedit.h \
    syntaxhighlighter.h

FORMS    += textedit.ui
