TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        handlefiles.cpp \
        lexico.cpp \
        main.cpp \
        sintactico.cpp

HEADERS += \
    handlefiles.h \
    lexico.h \
    sintactico.h
