#include "material.h"

/*!
 * \brief Material::Material Creates a new Material
 * there are no shaders compiled or liked or bound
 *
 * \param context openGl context for the Material
 * \param vShaderFile Vertex-Shader file name and location
 * \param fShaderFile Fragment-Shader file name and location
 * \param parent
 */
Material::Material(QOpenGLContext *context, QString vShaderFile, QString fShaderFile, QObject *parent)
    : QObject(parent) ,
      diffuseColor(1.0,1.0,1.0,1.0),
      ambientColor(0.5,0.5,0.5,1.0)
{
    contextDevice = context;
    vertexShaderFileName = vShaderFile;
    fragmentShaderFileName = fShaderFile;

    diffuseColorLocation = -1;
    ambientColorLocation = -1;

    this->vertexShader = NULL;
    this->fragmentShader = NULL;
    this->programm = NULL;

    //...
}
/*!
 * \brief Material::Create reads the shader files, compiles them and adds them to a programm
 */
void Material::Create()
{
    vertexShader = new  QOpenGLShader(QOpenGLShader::Vertex,this);
    fragmentShader = new QOpenGLShader(QOpenGLShader::Fragment,this);
    programm = new QOpenGLShaderProgram(this);

    vertexShader->compileSourceFile(vertexShaderFileName);
    fragmentShader->compileSourceFile(fragmentShaderFileName);

    if(!programm->addShader(vertexShader))
        qErrnoWarning("VertexShaderError");

    if(!programm->addShader(fragmentShader))
        qErrnoWarning("FragmentShaderError");
}
/*!
 * \brief Material::Link links the shader programm
 * override to add attributes
 */
void Material::Link()
{
    programm->link();

    vertexLocation = programm->attributeLocation("glPostion");
    ambientColorLocation = programm->attributeLocation("glAmbientColor");
    diffuseColorLocation = programm->attributeLocation("glDiffuseColor");
}
/*!
 * \brief Material::Destroy
 * deletes the shaders and programm
 */
void Material::Destroy()
{
    if(vertexShader)vertexShader->deleteLater();
    if(fragmentShader)fragmentShader->deleteLater();
    if(programm)programm->deleteLater();

    vertexShader=NULL;
    fragmentShader=NULL;
    programm=NULL;
}

/*!
 * \brief Material::CreateVertexLayout binds Material to a VertexBuffer and sets up the data structure
 * \param vertexBuffer QOpenGLBuffer with the VertexBuffer
 * \param format VertexFormat says what format the Buffer has with color etc
 */
void Material::CreateVertexLayout(QOpenGLBuffer* vertexBuffer,  VertexFormat format)
{
    vertexBuffer->bind();
    programm->bind();

    programm->enableAttributeArray(vertexLocation);

    int offset = 0;
    int tupel = 0;
    int stride = 0;

    giveVertexDataStruct(format,offset,tupel,stride);

    programm->setAttributeBuffer(vertexLocation,GL_FLOAT,offset,tupel,stride);


    programm->release();
    vertexBuffer->release();
}

/*!
 * \brief Material::Setup Setup shader values for the hole material livetime
 */
void Material::Setup()
{
    programm->bind();

    if(diffuseColorLocation != -1)
        programm->setAttributeValue(diffuseColorLocation,diffuseColor);
    if(ambientColorLocation != -1)
        programm->setAttributeValue(ambientColorLocation,ambientColor);

    programm->release();
}

/*!
 * \brief Material::SetupPerObject Setup values that needed to be setup for one object for one time
 * \param matWorld \link{QMatrix4x4}* The World matrix for that object
 * \param matWorldView \link{QMatrix4x4}* The WorldView matrix for that object
 * \param matWorldViewProjection \link{QMatrix4x4}* The WorldViewProjection matrix for that object
 */
void Material::SetupPerObject(const QMatrix4x4 *matWorld, const QMatrix4x4 *matWorldView, const QMatrix4x4 *matWorldViewProjection)
{
    programm->bind();

    programm->setAttributeValue("glmWorld",matWorld->data(),4,4);
    programm->setAttributeValue("glmWorldView",matWorldView->data(),4,4);
    programm->setAttributeValue("glmWorldViewProjection", matWorldViewProjection->data(),4,4);

    programm->release();
}

void Material::giveVertexDataStruct(const VertexFormat format, int &offset, int &tupel, int &stride)
{
    switch (format) {
    case Vert2D:
        offset = 0;
        tupel = 2;
        stride = 0;
        break;

    case Vert3D:
        offset = 0;
        tupel = 3;
        stride = 0;
        break;

    case Vert4D:
        offset = 0;
        tupel = 4;
        stride = 0;
        break;

    case Vert2DCol3D:
        offset = 0;
        tupel = 2;
        stride = sizeof(GLfloat)*tupel + sizeof(GLfloat) *3;
        break;

    case Vert2DCol4D:
        offset = 0;
        tupel = 2;
        stride = sizeof(GLfloat)*tupel + sizeof(GLfloat) *4;
        break;

    case Vert3DCol3D:
        offset = 0;
        tupel = 3;
        stride = sizeof(GLfloat)*tupel + sizeof(GLfloat) *3;
        break;

    case Vert3DCol4D:
        offset = 0;
        tupel = 3;
        stride = sizeof(GLfloat)*tupel + sizeof(GLfloat) *4;
        break;

    case Vert4DCol4D:
        offset = 0;
        tupel = 4;
        stride = sizeof(GLfloat)*tupel + sizeof(GLfloat) *4;
        break;

    default: //If you land here you are wrong and create an error!!
        offset = -1;
        tupel = -1;
        stride = 0;
        break;
    }
}

