#include "shapegenerator.h"
#include <QVector3D>
#include "Primitives/vertex.h"

#define NUM_ARRAY_ELEMENTS(a) sizeof(a) / sizeof(*a)


ShapeData ShapeGenerator::makeTriangle()
{

    ShapeData tri;
    Vertex genTri[] =
    {
       Vertex(QVector3D(+0.0f, +0.9f, +0.0f),//idx 0
              QVector3D(+1.0f, +0.0f, +0.0f)),

       Vertex(QVector3D(+0.9f, -0.9f, +0.0f),//idx 1
              QVector3D(+0.0f, +1.0f, +0.0f)),

       Vertex(QVector3D(-0.9f, -0.9f, +0.0f),//idx 2
              QVector3D(+0.0f, +0.0f, +1.0f)),

    };
    tri.numVertices = NUM_ARRAY_ELEMENTS(genTri);
    tri.vertices = new Vertex[tri.numVertices];
    memcpy(tri.vertices,genTri,sizeof(genTri));

    GLushort genIndices[] = {0,1,2};
    tri.numIndices = NUM_ARRAY_ELEMENTS(genIndices);
    tri.indices = new GLushort[tri.numIndices];
    memcpy(tri.indices,genIndices,sizeof(genIndices));

    return tri;
}

ShapeData ShapeGenerator::makeCube() {
    ShapeData ret;
    Vertex stackVerts[] =
    {
        Vertex(QVector3D(-1.0f, +1.0f, +1.0f), // 0
        QVector3D(+1.0f, +0.0f, +0.0f)), // Color
        Vertex(QVector3D(+1.0f, +1.0f, +1.0f), // 1
        QVector3D(+0.0f, +1.0f, +0.0f)), // Color
        Vertex(QVector3D(+1.0f, +1.0f, -1.0f), // 2
        QVector3D(+0.0f, +0.0f, +1.0f)), // Color
        Vertex(QVector3D(-1.0f, +1.0f, -1.0f), // 3
        QVector3D(+1.0f, +1.0f, +1.0f)), // Color

        Vertex(QVector3D(-1.0f, +1.0f, -1.0f), // 4
        QVector3D(+1.0f, +0.0f, +1.0f)), // Color
        Vertex(QVector3D(+1.0f, +1.0f, -1.0f), // 5
        QVector3D(+0.0f, +0.5f, +0.2f)), // Color
        Vertex(QVector3D(+1.0f, -1.0f, -1.0f), // 6
        QVector3D(+0.8f, +0.6f, +0.4f)), // Color
        Vertex(QVector3D(-1.0f, -1.0f, -1.0f), // 7
        QVector3D(+0.3f, +1.0f, +0.5f)), // Color

        Vertex(QVector3D(+1.0f, +1.0f, -1.0f), // 8
        QVector3D(+0.2f, +0.5f, +0.2f)), // Color
        Vertex(QVector3D(+1.0f, +1.0f, +1.0f), // 9
        QVector3D(+0.9f, +0.3f, +0.7f)), // Color
        Vertex(QVector3D(+1.0f, -1.0f, +1.0f), // 10
        QVector3D(+0.3f, +0.7f, +0.5f)), // Color
        Vertex(QVector3D(+1.0f, -1.0f, -1.0f), // 11
        QVector3D(+0.5f, +0.7f, +0.5f)), // Color

        Vertex(QVector3D(-1.0f, +1.0f, +1.0f), // 12
        QVector3D(+0.7f, +0.8f, +0.2f)), // Color
        Vertex(QVector3D(-1.0f, +1.0f, -1.0f), // 13
        QVector3D(+0.5f, +0.7f, +0.3f)), // Color
        Vertex(QVector3D(-1.0f, -1.0f, -1.0f), // 14
        QVector3D(+0.4f, +0.7f, +0.7f)), // Color
        Vertex(QVector3D(-1.0f, -1.0f, +1.0f), // 15
        QVector3D(+0.2f, +0.5f, +1.0f)), // Color

        Vertex(QVector3D(+1.0f, +1.0f, +1.0f), // 16
        QVector3D(+0.6f, +1.0f, +0.7f)), // Color
        Vertex(QVector3D(-1.0f, +1.0f, +1.0f), // 17
        QVector3D(+0.6f, +0.4f, +0.8f)), // Color
        Vertex(QVector3D(-1.0f, -1.0f, +1.0f), // 18
        QVector3D(+0.2f, +0.8f, +0.7f)), // Color
        Vertex(QVector3D(+1.0f, -1.0f, +1.0f), // 19
        QVector3D(+0.2f, +0.7f, +1.0f)), // Color

        Vertex(QVector3D(+1.0f, -1.0f, -1.0f), // 20
        QVector3D(+0.8f, +0.3f, +0.7f)), // Color
        Vertex(QVector3D(-1.0f, -1.0f, -1.0f), // 21
        QVector3D(+0.8f, +0.9f, +0.5f)), // Color
        Vertex(QVector3D(-1.0f, -1.0f, +1.0f), // 22
        QVector3D(+0.5f, +0.8f, +0.5f)), // Color
        Vertex(QVector3D(+1.0f, -1.0f, +1.0f), // 23
        QVector3D(+0.9f, +1.0f, +0.2f)), // Color
    };

    ret.numVertices = NUM_ARRAY_ELEMENTS(stackVerts);
    ret.vertices = new Vertex[ret.numVertices];
    memcpy(ret.vertices, stackVerts, sizeof(stackVerts));

    unsigned short stackIndices[] =
    {
        0,   1,  2,  0,  2,  3, // Top
        4,   5,  6,  4,  6,  7, // Front
        8,   9, 10,  8, 10, 11, // Right
        12, 13, 14, 12, 14, 15, // Left
        16, 17, 18, 16, 18, 19, // Back
        20, 22, 21, 20, 23, 22, // Bottom
    };

    ret.numIndices = NUM_ARRAY_ELEMENTS(stackIndices);
    ret.indices = new GLushort[ret.numIndices];
    memcpy(ret.indices, stackIndices, sizeof(stackIndices));

    return ret;
}

ShapeData ShapeGenerator::makeQuad() {
    ShapeData quad;

    Vertex genQuad[] =
    {
        Vertex(QVector3D(-1.0f, +1.0f, -0.0f),//idx 0
               QVector3D(+0.0f, +1.0f, +0.0f)),

        Vertex(QVector3D(+1.0f, +1.0f, -0.0f),//idx 1
               QVector3D(+1.0f, +1.0f, +0.0f)),

        Vertex(QVector3D(+1.0f, -1.0f, -0.0f),//idx 2
               QVector3D(+1.0f, +0.0f, +0.0f)),



        Vertex(QVector3D(+1.0f, -1.0f, -0.0f),//idx 3
               QVector3D(+1.0f, +0.0f, +0.0f)),

        Vertex(QVector3D(-1.0f, -1.0f, -0.0f),//idx 4
               QVector3D(+0.0f, +1.0f, +0.0f)),

        Vertex(QVector3D(-1.0f, +1.0f, -0.0f),//idx 5
               QVector3D(+0.0f, +1.0f, +0.0f)),

    };
    quad.numVertices = NUM_ARRAY_ELEMENTS(genQuad);
    quad.vertices = new Vertex[quad.numVertices];
    memcpy(quad.vertices,genQuad,sizeof(genQuad));

    GLushort genIndices[] = {0,1,2, 3,4,5};
    quad.numIndices = NUM_ARRAY_ELEMENTS(genIndices);
    quad.indices = new GLushort[quad.numIndices];
    memcpy(quad.indices,genIndices,sizeof(genIndices));


    return quad;

}

ShapeData ShapeGenerator::makeQuadTex()
{
    ShapeData quad;

    Vertex genQuad[] =
    {
        Vertex(QVector3D(-1.0f, +1.0f, -0.0f),//idx 0
               QVector3D(+0.0f, +1.0f, +0.0f)),

        Vertex(QVector3D(+1.0f, +1.0f, -0.0f),//idx 1
               QVector3D(+1.0f, +1.0f, +0.0f)),

        Vertex(QVector3D(+1.0f, -1.0f, -0.0f),//idx 2
               QVector3D(+1.0f, +0.0f, +0.0f)),



        Vertex(QVector3D(+1.0f, -1.0f, -0.0f),//idx 3
               QVector3D(+1.0f, +0.0f, +0.0f)),

        Vertex(QVector3D(-1.0f, -1.0f, -0.0f),//idx 4
               QVector3D(+0.0f, +0.0f, +0.0f)),

        Vertex(QVector3D(-1.0f, +1.0f, -0.0f),//idx 5
               QVector3D(+0.0f, +1.0f, +0.0f)),

    };
    quad.numVertices = NUM_ARRAY_ELEMENTS(genQuad);
    quad.vertices = new Vertex[quad.numVertices];
    memcpy(quad.vertices,genQuad,sizeof(genQuad));

    GLushort genIndices[] = {0,1,2, 3,4,5};
    quad.numIndices = NUM_ARRAY_ELEMENTS(genIndices);
    quad.indices = new GLushort[quad.numIndices];
    memcpy(quad.indices,genIndices,sizeof(genIndices));


    return quad;
}
