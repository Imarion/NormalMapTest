#ifndef VERTEXTEX_H
#define VERTEXTEX_H

#include <QVector3D>
#include <QVector2D>

#include "vertex.h"

class VertexTex : public Vertex
{
public:
    VertexTex();
    VertexTex(QVector3D pos, QVector2D tex);

    QVector2D getTexCoord();

private:
    QVector2D m_tex;
};

#endif // VERTEXTEX_H
