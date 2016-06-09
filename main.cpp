#include <QApplication>
#include "musikquadrender.h"
#include "audiospec.h"
#include "generator.h"
#include "driver.h"
//#include <qfouriercalculator.h>
//#include <qfouriertransformer.h>
#include <QAudioInput>
#include <QIODevice>
#include <QThread>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MusikQuadRender w;
    AudioSpec * as;
    Generator gen(32);
    QThread * musik = new QThread();

    if(argc > 1)
        as = new AudioSpec(QString(argv[1]));
    else
        as = new AudioSpec(QString("alsa_output.pci-0000_00_1b.0.analog-stereo.monitor"));
    as->moveToThread(musik);

    musik->start();

    qInfo() << as->thread();
    qInfo() << musik;


    as->startListen();

    w.setGeometry(0,0,1200,700);

    w.show();


    Driver d;
    d.start(as,&gen,&w);

    int extc =a.exec();
    delete as;
    return extc;
}

