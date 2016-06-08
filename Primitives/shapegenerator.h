#ifndef SHAPEGENERATOR_H
#define SHAPEGENERATOR_H
#include "Primitives/shapedata.h"

class ShapeGenerator
{
public:
    static ShapeData makeTriangle();
    static ShapeData makeCube();
    static ShapeData makeQuad();
    static ShapeData makeQuadTex();
};

#endif // SHAPEGENERATOR_H
