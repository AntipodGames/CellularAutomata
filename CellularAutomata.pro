LIBS += -L/usr/local/lib/ -lX11 -lsfml-window -lsfml-system -lsfml-graphics -lsfml-audio

INCLUDEPATH += /usr/include/boost/

CONFIG += c++11
QT += widgets

SOURCES += \
    Main.cpp \
    automaton.cpp \
    world.cpp \
    qsfml.cpp \
    qsfcanvas.cpp \
    displaymanager.cpp \
    gui.cpp \
    maingui.cpp

HEADERS += \
    automaton.h \
    world.h \
    qsfml.h \
    qsfcanvas.h \
    displaymanager.h \
    gui.h \
    maingui.h
