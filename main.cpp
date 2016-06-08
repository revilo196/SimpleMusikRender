#include <QApplication>
#include "musikquadrender.h"
#include "audiospec.h"
#include "generator.h"
#include "driver.h"
//#include <qfouriercalculator.h>
//#include <qfouriertransformer.h>
#include <QAudioInput>
#include <QIODevice>

main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MusikQuadRender w;
    AudioSpec as(QString("alsa_output.pci-0000_00_1b.0.analog-stereo.monitor"));
    Generator gen(16);

    as.startListen();

    w.setGeometry(0,0,1200,700);

    w.show();

    Driver d;
    d.start(&as,&gen,&w);

    return a.exec();
}

