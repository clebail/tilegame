#-------------------------------------------------
#
# Project created by QtCreator 2017-04-05T10:35:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = spriteEdit
TEMPLATE = app
INCLUDEPATH += .. .
LIBS +=  -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system -lX11

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        CMainWindow.cpp \
    CWidgetSpriteSheet.cpp \
    ../CSprite.cpp \
    ../CSpriteFrame.cpp \
    CSpriteFrameWidget.cpp \
    CSpritePreview.cpp

HEADERS  += CMainWindow.h \
    CWidgetSpriteSheet.h \
    ../CSprite.h \
    ../CSpriteFrame.h \
    CSpriteFrameWidget.h \
    CSpritePreview.h

FORMS    += CMainWindow.ui \
    CWidgetSpriteSheet.ui

RESOURCES += \
    spriteedit.qrc
