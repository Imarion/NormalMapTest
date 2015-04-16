#QT += gui-private core-private
QT += gui core

HEADERS += DemoLight.h \
    utils.h \
    vertex.h \
    basiclight.h \
    pointlight.h \
    directionallight.h \
    spotlight.h

SOURCES += DemoLight.cpp main.cpp \
    utils.cpp \
    vertex.cpp \
    basiclight.cpp \
    pointlight.cpp \
    directionallight.cpp \
    spotlight.cpp

OTHER_FILES += \
    vshader.txt \
    fshader.txt

RESOURCES += \
    shaders.qrc

