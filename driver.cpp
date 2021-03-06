#include "driver.h"
#include <QTimerEvent>

void Driver::timerEvent(QTimerEvent *e)
{


    if(!init){
        connect(a,SIGNAL(sendRMS(double)),gen,SLOT(reciveRMS(double)));
        connect(a,SIGNAL(sendSpec(QVector<float>*)),gen,SLOT(reciveSpec(QVector<float>*)));
        init = true;
    }


    QVector<QVector3D> scales = gen->calcSize();
    QVector<QVector3D> colors = gen->calcColor();

    const int sizeVec = 32;

    QVector3D data[sizeVec];
    QVector3D color[sizeVec];

    for(int i = 0; i<sizeVec; i++){

        data[i] = scales.at(i);
        color[i] = QVector3D(1.0,0.1,0.1);
    }

    w->sendSizeData(data,sizeVec);
    w->sendColorData(colors.data(),colors.size());

    w->update();

    //qInfo() << 1000.0/fpsMon->elapsed();

    fpsMon->restart();

}
