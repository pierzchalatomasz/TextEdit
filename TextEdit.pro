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
    syntaxhighlighter.cpp \
    files.cpp \
    styles.cpp

HEADERS  += textedit.h \
    syntaxhighlighter.h \
    files.h \
    styles.h

FORMS    += textedit.ui
