#include "utils.h"

#include <cstring>

#include <QVector3D>
#include <QDebug>

utils::utils()
{
}

void utils::CalcNormals(const unsigned int* pIndices, unsigned int IndexCount,
                        Vertex *pVertices, unsigned int VertexCount)
{
    unsigned int Index0;
    unsigned int Index1;
    unsigned int Index2;

    // Accumulate each triangle normal into each of the triangle vertices
    for (unsigned int i = 0; i < IndexCount; i += 3)
    {
        Index0 = pIndices[i];
        Index1 = pIndices[i+1];
        Index2 = pIndices[i+2];
        QVector3D v1 = pVertices[Index1].getPos() - pVertices[Index0].getPos();
        QVector3D v2 = pVertices[Index2].getPos() - pVertices[Index0].getPos();
        QVector3D Normal = QVector3D::crossProduct(v1, v2);
        Normal.normalize();

        pVertices[Index0].setNormal(pVertices[Index0].getNormal()+Normal);
        pVertices[Index1].setNormal(pVertices[Index1].getNormal()+Normal);
        pVertices[Index2].setNormal(pVertices[Index2].getNormal()+Normal);
    }

    // Normalize all the vertex normals
    for (unsigned int i = 0; i < VertexCount; i++) {
        pVertices[i].setNormal(pVertices[i].getNormal().normalized());
        qDebug() << "normal " << pVertices[i].getNormal();
    }
}
