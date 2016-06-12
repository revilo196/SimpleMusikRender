#ifndef SCENE_H
#define SCENE_H

#include <QObject>
#include "renderable.h"

/*!
 * \brief The Scene class
 *
 * Describes a Scene of renderable Objects
 * and holds dem in a Layer togehtner
 *
 * a scene can be rendered in a // Future RENDER class
 */
class Scene : public QObject
{
    Q_OBJECT
public:
    explicit Scene(QObject *parent = 0);

signals:

public slots:
};

#endif // SCENE_H
