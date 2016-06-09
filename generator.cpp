#include "generator.h"
#include <QDebug>
/*!
 * \brief Generator::Generator init the new Generator
 * \param numQuads number of ouputs
 * \param parent QObject
 */
Generator::Generator(int numQuads, QObject *parent) : QObject(parent)
{
    rms = 1;
    numQuades = numQuads;
    quadMapedSpec.resize(numQuads);

    highCol.setRgb(255,5,5);
    lowCol.setRgb(80,180,10);
}
/*!
 * \brief Generator::calcPos Calculates the position of the Quads
 * \return QVector<QVector3D> a number of positions
 */
QVector<QVector3D> Generator::calcPos()
{

    QVector<QVector3D> positions(numQuades);

    QVector3D startPos(-1.0,0.0,0.0);

    float width = 2.0/numQuades;

    for(int i = 0; i < numQuades; i++) {

         float x = startPos.x() + (width*i);
         float y = startPos.y();
         float z = startPos.z();

         positions.data()[i] = QVector3D(x,y,z);
    }

    return positions; //deep copy
}

/*!
 * \brief Generator::calcPos Calculates the position of the Quads
 * \return QVector<QVector3D> a number of positions
 */
QVector<QVector3D> Generator::calcSize()
{
    if(needUpdate) {
        mapToCube(); //recalculate the Spectrum to match the size of the quads
    }


    QVector<QVector3D> scales(numQuades);

    float width = 2.0/numQuades;

    QVector3D stdScale(width,0.01,1.0);

    for(int i = 0; i < numQuades; i++) {

         //qInfo() << quadMapedSpec.at(i);

         float x = stdScale.x();
         float y = stdScale.y() * (log10(quadMapedSpec.at(i)+1) *20);
         float z = stdScale.z();

         scales.data()[i] = QVector3D(x,y,z);
    }

    return scales; //deep copy
}

/*!
 * \brief Generator::calcColor Calulates the Colors for each Quad
 * \return  QVector<QVector3D> a number of colors as RGB
 */
QVector<QVector3D> Generator::calcColor()
{
    QVector<QVector3D> colors(numQuades);

    for(int i = 0; i < numQuades; i++) {
        colors.data()[i] = QVector3D(1.0,0.1,0.1);
    }

    return colors;
}
//Private
/*!
 * \brief Generator::mapToCube Calulates the x number of input values to numQuads values
 */
void Generator::mapToCube()
{
    if (spectrum.size() < numQuades)
    {
        //not enougth spectum data
    }
    else if (spectrum.size() == numQuades)
    {
        //nothing to map
        quadMapedSpec = spectrum;
    }
    else if(spectrum.size() > numQuades)
    {
        int a = (float)spectrum.size()/ ((float)numQuades*(float)numQuades);

        if(( a == (float)spectrum.size()/ ((float)numQuades*(float)numQuades)))
        {


            int lastSpec = 0;
            for(int i = 0; i<numQuades;i++)
            {
                int thisSpec = a * ((i)*(i));

               quadMapedSpec.data()[i] = 0;

                for(int j = lastSpec; j<= thisSpec; j++)
                {
                    if(j < 0 || j >= spectrum.size())
                    {
                        //ERROR
                        return;
                    }
                    quadMapedSpec.data()[i] += spectrum.at(j);

                }

                quadMapedSpec.data()[i] =  quadMapedSpec.data()[i] / (thisSpec-lastSpec);


                lastSpec = thisSpec;
                //qInfo() <<  quadMapedSpec.data()[i];
            }
        }
    }
}
