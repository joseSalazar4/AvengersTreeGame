QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS


SOURCES += \
    creadorpersonas.cpp \
    main.cpp \
    mainwindow.cpp \
    mundo.cpp \
    smtp.cpp

HEADERS += \
    Deportes.h \
    FechaNacimiento.h \
    Heap.h \
    Longevidad.h \
    MundoThanos.h \
    Persona.h \
    creadorpersonas.h \
    mainwindow.h \
    mundo.h \
    registroIDs.h \
    smtp.h \
    templateAVL.h \
    templateLista.h

FORMS += \
    creadorpersonas.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Recursos.qrc

