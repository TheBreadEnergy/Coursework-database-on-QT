QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = kyrsach
TEMPLATE = app

SOURCES += main.cpp\
    AddDialogWindow.cpp \
    Database.cpp \
    MainWindow.cpp \
    ChangeDialogWindow.cpp

HEADERS  += \
    AddDialogWindow.h \
    Database.h \
    MainWindow.h \
    ChangeDialogWindow.h

DISTFILES +=

RESOURCES += \
    res.qrc
