#QT += gui-private core-private
QT += gui core

HEADERS += NormalMapTest.h \
    utils.h \
    vertex.h \
    basiclight.h \
    directionallight.h

SOURCES += NormalMapTest.cpp main.cpp \
    utils.cpp \
    vertex.cpp \
    basiclight.cpp \
    directionallight.cpp

OTHER_FILES += \
    vshader.txt \
    fshader_color.txt \
    fshader_texture.txt

RESOURCES += \
    shaders.qrc

