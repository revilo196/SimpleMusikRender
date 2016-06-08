#ifndef MUSIKQUADRENDER_H
#define MUSIKQUADRENDER_H
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLFunctions_4_3_Core>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLFramebufferObject>
#include <QBasicTimer>


class MusikQuadRender : public QOpenGLWidget , protected QOpenGLFunctions_4_3_Core
{
public:
    MusikQuadRender(QWidget *parent = 0);

    void sendSizeData(QVector3D* quadSize, int arrSize);
    void sendColorData(QVector3D* color, int arrSize);

protected:
    void initializeGL();
    void paintGL();
    void timerEvent(QTimerEvent *e);
    QBasicTimer * timer;
private:
    void initializeShader();
    void initializeGeometry();
    void initializeTexShader();
    void initializeTexGeometry();
    void initializeFrameBuffer();

    //Shader Values
    QOpenGLShaderProgram* programm;
    GLuint vposAttr;
    GLuint vcolAttr;
    GLuint vmatrixAttr;
    GLuint vprojUniform;
    //Geomety Values;
    QOpenGLBuffer vIndex;
    QOpenGLBuffer vVertex;
    QOpenGLBuffer vTransform;
    QOpenGLBuffer vColor;
    QOpenGLVertexArrayObject vObject;

    //Fullscreen Quad shader;
    QOpenGLShaderProgram* programmTex;
    GLuint texVpos;
    GLuint texIDuniform;
    //Fullscreen Quad gemety
    QOpenGLBuffer tIndex;
    QOpenGLBuffer tVertex;
    QOpenGLBuffer tTransform;
    QOpenGLVertexArrayObject tObject;


    QOpenGLFramebufferObject *frame;
    GLuint frameBuffer;

    GLuint numIndx;

    QMatrix4x4 * quadTransforms;
    QVector3D * quadColors;
    int numQuads;
    int numColor;

    unsigned long nframe;
};

#endif // MUSIKQUADRENDER_H
