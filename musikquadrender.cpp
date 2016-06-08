#include "musikquadrender.h"
#include "Primitives/shapedata.h"
#include "Primitives/shapegenerator.h"
#include <QMatrix4x4>
#include <QTimer>
#include <QtMath>

static const Vertex sg_vertexes[] = {
  Vertex( QVector3D( 0.00f,  0.75f, 1.0f), QVector3D(1.0f, 0.0f, 0.0f) ),
  Vertex( QVector3D( 0.75f, -0.75f, 1.0f), QVector3D(0.0f, 1.0f, 0.0f) ),
  Vertex( QVector3D(-0.75f, -0.75f, 1.0f), QVector3D(0.0f, 0.0f, 1.0f) )
};

MusikQuadRender::MusikQuadRender(QWidget *parent) : QOpenGLWidget(parent) ,vIndex(QOpenGLBuffer::IndexBuffer)
{
    quadTransforms =0;
    quadColors =0;
    numQuads = 0;
    numColor = 0;

    timer = new QBasicTimer();

    nframe = 0;

}

void MusikQuadRender::sendSizeData(QVector3D *quadSize, int arrSize)
{

    if(quadTransforms == 0 && numQuads == 0){

        quadTransforms = new QMatrix4x4[arrSize];
        numQuads = arrSize;

    } else if(quadTransforms != 0 && numQuads > arrSize){
        numQuads = arrSize;
    } else if(quadTransforms != 0 && numQuads < arrSize){
        delete [] quadTransforms;
        quadTransforms = new QMatrix4x4[arrSize];
        numQuads = arrSize;
    }

    for(int i = 0 ; i < numQuads ; i++){

        float x_move = (float)(i /(numQuads*0.5))-1;
        quadTransforms[i] = QMatrix4x4();
        quadTransforms[i].translate(x_move,0,0);
        quadTransforms[i].scale(quadSize[i]);

    }

}

void MusikQuadRender::sendColorData(QVector3D *color, int arrSize)
{

    if(quadColors == 0 && numColor == 0){

        quadColors = new QVector3D[arrSize];
        numColor = arrSize;

    } else if(quadColors != 0 && numColor > arrSize){
        numQuads = arrSize;
    } else if(quadColors != 0 && numColor < arrSize){
        delete [] quadColors;
        quadColors = new QVector3D[arrSize];
        numColor = arrSize;
    }

    for(int i = 0 ; i < numColor ; i++){
        quadColors[i] = QVector3D(color[i]);
    }


}

void MusikQuadRender::initializeGL()
{
    initializeOpenGLFunctions();

    //glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    initializeShader();
    initializeTexShader();
    initializeGeometry();
    initializeTexGeometry();
    initializeFrameBuffer();
    glEnable(GL_DEPTH_TEST);


  //  timer->start(25,this);
}

void MusikQuadRender::initializeShader()
{

    programm = new QOpenGLShaderProgram(this);
    programm->addShaderFromSourceFile(QOpenGLShader::Vertex,"vshader.vsh");
    programm->addShaderFromSourceFile(QOpenGLShader::Fragment,"fshader.fsh");
    programm->link();
    programm->bind();

    vposAttr = programm->attributeLocation("position");
    vcolAttr = programm->attributeLocation("color");
    vmatrixAttr = programm->attributeLocation("modelMatrix");
    vprojUniform = programm->uniformLocation("projMatrix");
}
void MusikQuadRender::initializeTexShader()
{

    programmTex = new QOpenGLShaderProgram(this);
    programmTex->addShaderFromSourceFile(QOpenGLShader::Vertex,"texvshader.vsh");
    programmTex->addShaderFromSourceFile(QOpenGLShader::Fragment,"texfshader.fsh");
    programmTex->link();

    texVpos = programmTex->attributeLocation("qt_Vertex");
    texIDuniform = programmTex->uniformLocation("qt_Texture0");

}


void MusikQuadRender::initializeGeometry()
{
    ShapeData shape = ShapeGenerator::makeQuad();

    vVertex.create();
    vVertex.bind();
    vVertex.setUsagePattern(QOpenGLBuffer::StaticDraw);
    vVertex.allocate(shape.vertices,shape.numVertices*sizeof(Vertex));

    vObject.create();
    vObject.bind();

    programm->enableAttributeArray(vposAttr);

    programm->setAttributeBuffer(vposAttr,GL_FLOAT,Vertex::positionOffset(),Vertex::PositionTupleSize,Vertex::stride());


//    programmTex->enableAttributeArray(texVpos);
 //   programmTex->setAttributeBuffer(texVpos,GL_FLOAT,Vertex::positionOffset(),Vertex::PositionTupleSize,Vertex::stride());

    vIndex.create();
    vIndex.bind();

    vIndex.setUsagePattern(QOpenGLBuffer::StaticDraw);
    vIndex.allocate(shape.indices,shape.indexBufferSize());

    numIndx = shape.numIndices;

    vVertex.release();
    vObject.release();

    vTransform.create();
    vTransform.bind();
    vTransform.setUsagePattern(QOpenGLBuffer::DynamicDraw);
    vTransform.allocate(quadTransforms,sizeof(QMatrix4x4)*numQuads);

    vObject.bind();

    programm->enableAttributeArray(vmatrixAttr);
    programm->enableAttributeArray(vmatrixAttr+1);
    programm->enableAttributeArray(vmatrixAttr+2);
    programm->enableAttributeArray(vmatrixAttr+3);

    programm->setAttributeBuffer(vmatrixAttr,GL_FLOAT,sizeof(QVector4D)*0,4,sizeof(QMatrix4x4));
    programm->setAttributeBuffer(vmatrixAttr+1,GL_FLOAT,sizeof(QVector4D)*1,4,sizeof(QMatrix4x4));
    programm->setAttributeBuffer(vmatrixAttr+2,GL_FLOAT,sizeof(QVector4D)*2,4,sizeof(QMatrix4x4));
    programm->setAttributeBuffer(vmatrixAttr+3,GL_FLOAT,sizeof(QVector4D)*3,4,sizeof(QMatrix4x4));


    glVertexAttribDivisor(vmatrixAttr,1);
    glVertexAttribDivisor(vmatrixAttr+1,1);
    glVertexAttribDivisor(vmatrixAttr+2,1);
    glVertexAttribDivisor(vmatrixAttr+3,1);

    vColor.create();
    vColor.bind();
    vColor.setUsagePattern(QOpenGLBuffer::DynamicDraw);
    vColor.allocate(quadColors,sizeof(QVector3D)*numQuads);


    programm->setAttributeBuffer(vcolAttr,GL_FLOAT,0,3,sizeof(QVector3D));
    programm->enableAttributeArray(vcolAttr);

    glVertexAttribDivisor(vcolAttr,1);
    vObject.release();
    vTransform.release();

    shape.cleanup();
}


void MusikQuadRender::initializeTexGeometry()
{
    ShapeData shape = ShapeGenerator::makeQuadTex();

    tVertex.create();
    tVertex.bind();
    tVertex.setUsagePattern(QOpenGLBuffer::StaticDraw);
    tVertex.allocate(shape.vertices,shape.numVertices*sizeof(Vertex));

    tObject.create();
    tObject.bind();

    programm->enableAttributeArray(vposAttr);
    programm->enableAttributeArray(vcolAttr);
    programm->setAttributeBuffer(vposAttr,GL_FLOAT,Vertex::positionOffset(),Vertex::PositionTupleSize,Vertex::stride());
    programm->setAttributeBuffer(vcolAttr,GL_FLOAT,Vertex::colorOffset(),Vertex::ColorTupleSize,Vertex::stride());

    tIndex.create();
    tIndex.bind();

    tIndex.setUsagePattern(QOpenGLBuffer::StaticDraw);
    tIndex.allocate(shape.indices,shape.indexBufferSize());

    numIndx = shape.numIndices;

    tVertex.release();
    tObject.release();

    tTransform.create();
    tTransform.bind();
    tTransform.setUsagePattern(QOpenGLBuffer::StaticDraw);
    tTransform.allocate(quadTransforms,sizeof(QMatrix4x4)*numQuads);

    tObject.bind();



    programm->setAttributeBuffer(vmatrixAttr,GL_FLOAT,sizeof(QVector4D)*0,4,sizeof(QMatrix4x4));

    QMatrix4x4 mat;
    programm->setAttributeValue(vmatrixAttr,mat.data(),4,4);



    tObject.release();
    tTransform.release();

    shape.cleanup();
}



void MusikQuadRender::initializeFrameBuffer()
{

    frame = new QOpenGLFramebufferObject(400,300);
    frame->addColorAttachment(400,300);
    frame->bindDefault();
}

void MusikQuadRender::paintGL()
{
    // Clear
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    vTransform.bind();
    //vTransform.setUsagePattern(QOpenGLBuffer::StaticDraw);
    vTransform.allocate(quadTransforms,sizeof(QMatrix4x4)*numQuads);

    vColor.bind();
    vColor.allocate(quadColors,sizeof(QVector3D)*numQuads);



    // Render using our shader
    programm->bind();
    {
      vObject.bind();

      //Set Perspctive;

      QMatrix4x4 prj;
      //prj.perspective(60,(float)(width()/height()),0.1,10);
      programm->setUniformValue(vprojUniform,prj);

      glViewport(0,0,400,300);

      frame->bind();
      programm->setUniformValue("dos",false);

      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_2D,frame->texture());
      glClear(GL_COLOR_BUFFER_BIT);
      glDrawElementsInstanced(GL_TRIANGLES, numIndx, GL_UNSIGNED_SHORT,0, numQuads);


      frame->bindDefault();


      vObject.release();

      tObject.bind();

      programmTex->bind();

      glViewport(0,0,1200,700);
            glClear(GL_COLOR_BUFFER_BIT);

      glDrawArrays(GL_TRIANGLES,0,6);




      tObject.release();

    }
    programm->release();



}
/* Test the Render animation
void MusikQuadRender::timerEvent(QTimerEvent *e)
{
    nframe++;
    nframe++;

    const int sizeVec = 16;

    QVector3D data[sizeVec];
    QVector3D color[sizeVec];

    for(int i = 0; i<sizeVec; i++){


        float height = sin((float)((i+(nframe/3))) / (sizeVec*1)) * sin(((float)nframe/30.0)) * cos((i+(nframe/3.0))/5.0) *0.8;
        float width  = 1.0f/(float)sizeVec;

        data[i] = QVector3D(width,height,1);
        color[i] = QVector3D(height*height,0.05,0.1);
    }

    sendSizeData(data,sizeVec);
    sendColorData(color,sizeVec);

    this->update();
}
*/


