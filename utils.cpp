#include "utils.h"

#include <cstring>

#include <QVector3D>
#include <QDebug>

// Code based on ogldev tutorials (http://ogldev.atspace.co.uk/)

utils::utils()
{
}

void utils::CalcNormals(const unsigned int* pIndices, unsigned int IndexCount,
                        VertexTex *pVertices, unsigned int VertexCount)
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

void utils::CalcTangent(const unsigned int* pIndices, unsigned int IndexCount,
                        VertexTex *pVertices, unsigned int VertexCount)
{
    unsigned int Index0;
    unsigned int Index1;
    unsigned int Index2;

    for (unsigned int i=0; i<IndexCount; i += 3)
    {
        Index0 = pIndices[i];
        Index1 = pIndices[i+1];
        Index2 = pIndices[i+2];

        QVector3D v0 = pVertices[Index0].getPos();
        QVector3D v1 = pVertices[Index1].getPos();
        QVector3D v2 = pVertices[Index2].getPos();

        QVector3D Edge1 = v1 - v0;  // = q1
        QVector3D Edge2 = v2 - v0;  // = q2

        float DeltaU1 = pVertices[Index1].getTexCoord().x() - pVertices[Index0].getTexCoord().x(); // v1.u - v0.u; = s1
        float DeltaV1 = pVertices[Index1].getTexCoord().y() - pVertices[Index0].getTexCoord().y(); // v1.v - v0.v; = t1
        float DeltaU2 = pVertices[Index2].getTexCoord().x() - pVertices[Index0].getTexCoord().x(); // v2.u - v0.u; = s2
        float DeltaV2 = pVertices[Index2].getTexCoord().y() - pVertices[Index0].getTexCoord().y(); // v2.v - v0.v; = t2

        float f = 1.0f / (DeltaU1 * DeltaV2 - DeltaU2 * DeltaV1);

        QVector3D Tangent;
        Tangent   = f * ((DeltaV2 * Edge1)  - (DeltaV1 * Edge2));
        //Bitangent = f * (-(DeltaU2 * Edge1) - (DeltaU1 * Edge2)); // Bitangent calculation for info

        pVertices[Index0].setTangent(pVertices[Index0].getTangent()+Tangent);
        pVertices[Index1].setTangent(pVertices[Index1].getTangent()+Tangent);
        pVertices[Index2].setTangent(pVertices[Index2].getTangent()+Tangent);
    }

    for (unsigned int i=0; i<VertexCount; i++)
    {
        pVertices[i].setTangent(pVertices[i].getTangent().normalized());
    }
}
