#-------------------------------------------------
#
# Project created by QtCreator 2014-12-01T17:03:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HandGusture
TEMPLATE = app


SOURCES += main.cpp\
        hanggusturecontrol.cpp

HEADERS  += hanggusturecontrol.h

FORMS    += hanggusturecontrol.ui
INCLUDEPATH += D:\OpenCV\opencv\build\include \
               D:\OpenCV\opencv\build\include\opencv \
               D:\OpenCV\opencv\build\include\opencv2



RC_FILE += sdu.rc

OTHER_FILES += \
    sdu.rc \
    sdu.ico
RESOURCES += \
    HandGusture.qrc

