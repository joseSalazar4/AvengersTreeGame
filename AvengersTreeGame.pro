QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS


SOURCES += \
    ListaPersonas.cpp \
    Persona.cpp \
    main.cpp \
    mainwindow.cpp \
    smtp.cpp

HEADERS += \
    ListaPersonas.h \
    Persona.h \
    mainwindow.h \
    smtp.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Files.qrc
