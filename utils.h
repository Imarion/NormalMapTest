#ifndef UTILS_H
#define UTILS_H

#include "vertex.h"

class utils
{
public:
    utils();

    static void CalcNormals(const unsigned int* pIndices, unsigned int IndexCount,
                            Vertex *pVertices, unsigned int VertexCount);

};

#endif // UTILS_H
