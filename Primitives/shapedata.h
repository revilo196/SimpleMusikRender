#ifndef SHAPEDATA_H
#define SHAPEDATA_H
#include <QtOpenGL/QGL>
#include "Primitives/vertex.h"

struct ShapeData
{
  ShapeData() : vertices(NULL), numVertices(0), indices(NULL), numIndices(0) {}

  Vertex * vertices;
  GLuint numVertices;
  GLushort * indices;
  GLuint numIndices;

  GLsizeiptr vertexBufferSize() const
  {
      return numVertices * sizeof(Vertex);
  }

  GLsizeiptr indexBufferSize() const
  {
      return numIndices * sizeof(GLushort);
  }

  void cleanup()
  {
      delete [] vertices;
      delete [] indices;
      numIndices = 0;
      numVertices = 0;
      vertices = NULL;
      indices = NULL;
  }
};

#endif // SHAPEDATA_H
