TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        bombo.cpp \
        equipo.cpp \
        estadisticasequipo.cpp \
        gestordatos.cpp \
        grupo.cpp \
        jugador.cpp \
        main.cpp \
        partido.cpp

HEADERS += \
    bombo.h \
    equipo.h \
    estadisticasequipo.h \
    gestordatos.h \
    grupo.h \
    jugador.h \
    lista.h \
    nodo.h \
    partido.h
