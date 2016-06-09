#ifndef DRIVER_H
#define DRIVER_H
#include "audiospec.h"
#include "generator.h"
#include "musikquadrender.h"
#include <QBasicTimer>
#include <QElapsedTimer>

#include <QObject>

class Driver : public QObject
{
    Q_OBJECT


    QBasicTimer * timer;
    QElapsedTimer * fpsMon;
    int nframe;
    AudioSpec * a;
    Generator * gen;
    MusikQuadRender * w;

    bool init;
public:
    void start(AudioSpec *a, Generator *gen, MusikQuadRender *w){
        timer = new QBasicTimer();
        timer->start(20,this);
        fpsMon = new QElapsedTimer();
        fpsMon->start();
        this->a = a;
        this->gen = gen;
        this->w = w;
    }

signals:

public slots:
    void timerEvent(QTimerEvent * e);
};

#endif // DRIVER_H
