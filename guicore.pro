#-------------------------------------------------
#
# Project created by QtCreator 2010-05-13T17:37:37
#
#-------------------------------------------------

QT -= core \
    gui \
    network
TARGET = guicore
TEMPLATE = lib

DEFINES += GUICORE_LIBRARY

SOURCES += \
    src/dt_button.cpp \
    src/dt_cachebmp.cpp \
    src/dt_combox.cpp \
    src/dt_commctrl.cpp \
    src/dt_ctrl.cpp \
    src/dt_edit.cpp \
    src/dt_icon.cpp \
    src/dt_icongroup.cpp \
    src/dt_listbox.cpp \
    src/dt_listview.cpp \
    src/dt_skinbutton.cpp \
    src/dt_skinchkbutton.cpp \
    src/dt_skinctrl.cpp \
    src/dt_skinlable.cpp \
    src/dt_static.cpp \
    src/SkinForm.cpp \
    src/dt_ipaddr.cpp \
    src/GuiEng.cpp \
    src/dt_font.cpp

INCLUDEPATH += ../mgi/mgiinc ../../../../include/guicore ../../../../include/utils

LIB_PATH=../../../../../lib
TMPOBJ=../../../../../tmpobj
linux-arm-g++ {
    message(g++ = linux-arm-g++)
    LIBS += -L$$LIB_PATH/mx27lib/ -L$$LIB_PATH/libmx27
    DESTDIR += $$LIB_PATH/libmx27
    OBJECTS_DIR = $$TMPOBJ/arm
}
linux-g++{
    message(g++ = linux-g++)
    DESTDIR += $$LIB_PATH/libpc
    OBJECTS_DIR = $$TMPOBJ/x86
}
