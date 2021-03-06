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
    vshader_color.txt \
    vshader_texture.txt \
    fshader_texture_normalmap.txt \
    vshader_texture_normalmap.txt \
    fshader_texture.txt \
    vshader_texture.txt \
    fshader_td_texture.txt \
    vshader_td_texture.txt

RESOURCES += \
    shaders.qrc

