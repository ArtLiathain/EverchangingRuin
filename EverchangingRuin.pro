TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    sources/Character.cpp \
    sources/Command.cpp \
    sources/CommandWords.cpp \
    sources/Parser.cpp \
    sources/Room.cpp \
    sources/ZorkUL.cpp \
    sources/item.cpp \

HEADERS += \
    headers/Character.h \
    headers/Command.h \
    headers/CommandWords.h \
    headers/Parser.h \
    headers/Room.h \
    headers/ZorkUL.h \
    headers/item.h

FORMS +=
