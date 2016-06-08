#include "driver.h"

void Driver::timerEvent(QTimerEvent *e)
{

    gen->setSpectrum(a->getSpectro());
    gen->setRMS(a->getRMS());


    QVector<QVector3D> scales = gen->calcSize();

    const int sizeVec = 16;

    QVector3D data[sizeVec];
    QVector3D color[sizeVec];

    for(int i = 0; i<sizeVec; i++){

        data[i] = scales.at(i);
        color[i] = QVector3D(1.0,0.1,0.1);
    }

    w->sendSizeData(data,sizeVec);
    w->sendColorData(color,sizeVec);

    w->update();

}
