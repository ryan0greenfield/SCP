#-------------------------------------------------
#
# Project created by QtCreator 2015-05-16T17:45:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = scp
TEMPLATE = app


SOURCES += main.cpp\
    clearance.cpp \
    LinePrinter.cpp \
    scpbpsc1.cpp \
    stdafx.cpp

HEADERS  += mainwindow.h \
    clearance.h \
    ForIcon.h \
    LinePrinter.h \
    Resource.aps \
    resource.h \
    scpbpsc1.h \
    stdafx.h \
    USBInterface.h

FORMS    += \
    clearance.ui \
    scpbpsc1.ui

RESOURCES += \
    scpbpsc1.qrc

DISTFILES += \
    scp.pro.user

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/ -lUSBInterface
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/ -lUSBInterface

INCLUDEPATH += $$PWD/
DEPENDPATH += $$PWD/
