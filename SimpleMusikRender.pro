#-------------------------------------------------
#
# Project created by QtCreator 2016-05-31T13:02:51
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SimpleMusikRender
TEMPLATE = app


SOURCES += main.cpp \
    musikquadrender.cpp \
    Primitives/shapegenerator.cpp \
    audiospec.cpp \
    generator.cpp \
    driver.cpp \
    EngineCore/renderable.cpp \
    EngineCore/material.cpp \
    EngineCore/scene.cpp \
    EngineCore/entity.cpp

HEADERS  += \
    musikquadrender.h \
    Primitives/shapedata.h \
    Primitives/shapegenerator.h \
    Primitives/vertex.h \
    audiospec.h \
    ffft/Array.h \
    ffft/Array.hpp \
    ffft/def.h \
    ffft/DynArray.h \
    ffft/DynArray.hpp \
    ffft/FFTReal.h \
    ffft/FFTReal.hpp \
    ffft/FFTRealFixLen.h \
    ffft/FFTRealFixLen.hpp \
    ffft/FFTRealFixLenParam.h \
    ffft/FFTRealPassDirect.h \
    ffft/FFTRealPassDirect.hpp \
    ffft/FFTRealPassInverse.h \
    ffft/FFTRealPassInverse.hpp \
    ffft/FFTRealSelect.h \
    ffft/FFTRealSelect.hpp \
    ffft/FFTRealUseTrigo.h \
    ffft/FFTRealUseTrigo.hpp \
    ffft/OscSinCos.h \
    ffft/OscSinCos.hpp \
    generator.h \
    driver.h \
    EngineCore/renderable.h \
    EngineCore/material.h \
    EngineCore/scene.h \
    EngineCore/entity.h


DISTFILES += \
    vshader.vsh \
    fshader.fsh \
    texvshader.vsh \
    texfshader.fsh \

SUBDIRS += \


#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../.lib/qrealfourier-0.3.0-amd64/usr/lib/release/ -lqrealfourier
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../.lib/qrealfourier-0.3.0-amd64/usr/lib/debug/ -lqrealfourier
#else:unix: LIBS += -L$$PWD/../../.lib/qrealfourier-0.3.0-amd64/usr/lib/ -lqrealfourier

#INCLUDEPATH += $$PWD/../../.lib/qrealfourier-0.3.0-amd64/usr/include
#DEPENDPATH += $$PWD/../../.lib/qrealfourier-0.3.0-amd64/usr/include
