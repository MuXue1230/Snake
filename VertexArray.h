#pragma once
#include "sdl_include.h"

class VertexArray
{
public:
    VertexArray(const float* verts, unsigned int numVerts, const unsigned int* indices, unsigned int numIndices);
    ~VertexArray();

    void SetActive();

    unsigned int GetNumIndices() const { return this->numIndices; }
    unsigned int GetNumVerts() const { return this->numVerts; }
private:
    unsigned int numVerts;
    unsigned int numIndices;
    unsigned int vertexBuffer;
    unsigned int indexBuffer;
    unsigned int vertxArray;
};

