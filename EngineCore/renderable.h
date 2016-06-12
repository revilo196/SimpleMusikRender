#ifndef RENDERABLE_H
#define RENDERABLE_H

#include <QObject>
#include <QOpenGLContext>
#include <QMatrix4x4>

/*!
 * \brief The {abstract} Renderable class
 *
 * abstract class for an Object that is renderable with openGL
 *
 * Create(), Destroy(), Render() and update() needs at least to be implemented
 */
class Renderable : public QObject
{
    Q_OBJECT
protected:
    QOpenGLContext* contextDevice;
    QMatrix4x4 matWorld;

    QString name;
public:
    explicit Renderable(QOpenGLContext * context,
                        const QMatrix4x4* pWorld ,
                        const QString strName = "Renderable",
                        QObject *parent = 0);
    virtual ~Renderable(){}

    /*!
     * \brief Create
     *
     * Creates the Renderable and initialize all openGL values
     */
    virtual void Create() = 0;

    /*!
     * \brief Destroy
     *
     * Destroies the Renderable
     */
    virtual void Destroy() = 0;

    /*!
     * \brief Render renders the object to the openGl contex
     * \param drawOrder
     * \param pView \link{QMatrix4x4}* view matrix;
     * \param pProj \link[QMatrix4x4]* projection matrix
     */
    virtual void Render(GLuint drawOrder,
                        const QMatrix4x4* pView,
                        const QMatrix4x4* pProj) = 0;


    virtual void update(double fTime, double fElapsedTime){}

    virtual QMatrix4x4* getWorldMatrix();
    virtual void setWorldMatrix(const QMatrix4x4& nWorld);

    inline QString getName(){return name;}
    inline void setName(QString nName){this->name = nName;}

signals:

public slots:
};

#endif // RENDERABLE_H
