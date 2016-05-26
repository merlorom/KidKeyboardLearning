######################################################################
# Automatically generated by qmake (2.01a) lun. mai 9 07:22:44 2016
# Edited to allow subdirectories to be parsed automatically
######################################################################

TEMPLATE = app
CONFIG += windows
DEPENDPATH += . core ui
INCLUDEPATH += . core ui
DESTDIR = bin
OBJECTS_DIR = build
UI_DIR = ui
QMAKE_CXXFLAGS += -Werror

# Input main
SOURCES += main.cpp

# Input core
HEADERS += \
           core/tile.h \
           core/labyrinth.h
SOURCES += \
           core/tile.cpp \
           core/labyrinth.cpp

# Input ui
FORMS += ui/editor.ui
HEADERS += \
           ui/main_window.h \
           ui/editor.h \
           ui/labyrinth_widget.h \
           ui/tile_item.h
SOURCES += \
           ui/main_window.cpp \
           ui/editor.cpp \
           ui/labyrinth_widget.cpp \
           ui/tile_item.cpp

