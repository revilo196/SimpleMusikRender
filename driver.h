#ifndef DRIVER_H
#define DRIVER_H
#include "audiospec.h"
#include "generator.h"
#include "musikquadrender.h"
#include <QBasicTimer>

#include <QObject>

class Driver : public QObject
{
    Q_OBJECT


    QBasicTimer * timer;
    int nframe;
    AudioSpec * a;
    Generator * gen;
    MusikQuadRender * w;
public:
    void start(AudioSpec *a, Generator *gen, MusikQuadRender *w){
        timer = new QBasicTimer();
        timer->start(20,this);
        this->a = a;
        this->gen = gen;
        this->w = w;
    }

signals:

public slots:
    void timerEvent(QTimerEvent * e);
};

#endif // DRIVER_H
