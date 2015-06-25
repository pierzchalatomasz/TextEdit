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
    styles.cpp \
    file.cpp

HEADERS  += textedit.h \
    syntaxhighlighter.h \
    styles.h \
    textblockuserdata.h \
    textblock.h \
    file.h

FORMS    += textedit.ui

RESOURCES += \
    icons.qrc
