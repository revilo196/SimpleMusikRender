#ifndef MATERIAL_H
#define MATERIAL_H

#include <QObject>
#include <QOpenGLContext>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QVector4D>
#include <QOpenGLBuffer>

//Better way ??
//Add Texture coordianten
/*!
 * \brief The VertexFormat enum
 *
 * Title for the Differnet Vertex DataTypes
 */
enum VertexFormat { Vert4DCol4D=0  , Vert4D=1,
                    Vert3DCol3D=2  , Vert3D=3,
                    Vert2DCol3D=4  , Vert2D=5,
                    Vert3DCol4D=6  ,
                    Vert2DCol4D=8};

/*!
 * \brief The Material class
 *
 * This Class manages a material for a Object.
 * A Material contains vertex and fragment shader and manages the connection to them
 */
class Material : public QObject
{
private:
    Q_OBJECT
protected:

    QOpenGLContext* contextDevice;

    QString vertexShaderFileName;
    QString fragmentShaderFileName;

    QOpenGLShader* vertexShader;
    QOpenGLShader* fragmentShader;

    QOpenGLShaderProgram* programm;

    QVector4D diffuseColor;
    QVector4D ambientColor;

    int diffuseColorLocation;
    int ambientColorLocation;
    int vertexLocation;

    //protected helper
    static void giveVertexDataStruct(VertexFormat format, int &offsets, int &tupelSize, int &stride);

public:
    explicit Material(QOpenGLContext* context,
                      QString vShaderFile,
                      QString fShaderFile, QObject *parent = 0);

    virtual void Create();
    virtual void Link();
    virtual void Destroy();
    virtual void CreateVertexLayout(QOpenGLBuffer *vertexBuffer, VertexFormat format);
    virtual void Setup();

    virtual void SetupPerObject(const QMatrix4x4* matWorld, const QMatrix4x4* matWorldView,
                                const QMatrix4x4* matWorldViewProjection);
    virtual void SetupPerFrame(){}

    inline QOpenGLShader* getVertexShader(){return vertexShader;}
    inline QOpenGLShader* getFragmentShader(){return fragmentShader;}
    inline QOpenGLShaderProgram* getShaderProgramm(){return programm;}

    //QVector4D getDiffuseColor() const;
    void setDiffuseColor(const QVector4D &value){diffuseColor = value;}

    //QVector4D getAmbientColor() const;
    void setAmbientColor(const QVector4D &value){ambientColor = value;}


signals:

public slots:
};

#endif // MATERIAL_H
