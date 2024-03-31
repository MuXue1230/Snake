#include "VertexArray.h"

VertexArray::VertexArray(const float* verts, unsigned int numVerts, const unsigned int* indices, unsigned int numIndices)
{
    glGenVertexArrays(1, &this->vertxArray);
    glBindVertexArray(this->vertxArray);
    glGenBuffers(1, &this->vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, numVerts * 3 * sizeof(float), verts, GL_STATIC_DRAW);
    glGenBuffers(1, &this->indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(unsigned int), indices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
}

VertexArray::~VertexArray()
{
    glDeleteBuffers(1, &this->vertexBuffer);
    glDeleteBuffers(1, &this->indexBuffer);
    glDeleteVertexArrays(1, &this->vertxArray);
}

void VertexArray::SetActive()
{
    glBindVertexArray(this->vertxArray);
}
