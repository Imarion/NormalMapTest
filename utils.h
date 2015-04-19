#ifndef UTILS_H
#define UTILS_H

#include "vertextex.h"

class utils
{
public:
    utils();

    static void CalcNormals(const unsigned int* pIndices, unsigned int IndexCount,
                            VertexTex *pVertices, unsigned int VertexCount);
    static void CalcTangent(const unsigned int* pIndices, unsigned int IndexCount,
                            VertexTex *pVertices, unsigned int VertexCount);

};

#endif // UTILS_H
