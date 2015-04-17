#QT += gui-private core-private
QT += gui core

HEADERS += NormalMapTest.h \
    utils.h \
    vertex.h \
    basiclight.h \
    directionallight.h \
    vertexcol.h \
    vertextex.h

SOURCES += NormalMapTest.cpp main.cpp \
    utils.cpp \
    vertex.cpp \
    basiclight.cpp \
    directionallight.cpp \
    vertexcol.cpp \
    vertextex.cpp

OTHER_FILES += \
    fshader_color.txt \
    fshader_texture.txt \
    vshader_color.txt \
    vshader_texture.txt

RESOURCES += \
    shaders.qrc

