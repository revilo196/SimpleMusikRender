#ifndef GENERATOR_H
#define GENERATOR_H

#include <QObject>
#include <QVector>
#include <QVector3D>
#include <QColor>
/*!
 * \brief The Generator class Generates Transformation and Color values for rendering from a Spectum
 * and the RMS value
 *
 * //In Future is shoud also handel animating the data and calulating a dapening effect etc
 * //AudioSpec and The Generator shoud be linked via signal/ slot so that the generator Takes each calculated frame
 * //And AudioSpec and Generator shoud be Arraged on differnt Theads for speed
 */
class Generator : public QObject
{
    Q_OBJECT

    double rms;
    QVector<float> spectrum;

    int numQuades;
    QVector<float> quadMapedSpec;

    QColor highCol;
    QColor lowCol;

    bool needUpdate;

public:
    explicit Generator(int numQuads, QObject *parent = 0);

    /*!
     * \brief setSpectrum gives the Generator new Spectrum data
     * the Size shoud be larger than the number of Quads to calculate
     * and the size shoud be:  size = numQuads^2 * n  (n is an int)
     *
     * \param spec QVector<float> new Spectrtum data
     */
    void setSpectrum(QVector<float> spec){spectrum = spec; needUpdate = true;}

    /*!
     * \brief setRMS gives the Generator a new RMS value
     * \param rmsN new RMS value (double)
     */
    void setRMS(double rmsN){rms = rmsN;}

    /*!
     * \brief setHighColor gives the Generator a new color to use for high values
     * \param high QColor
     */
    void setHighColor(QColor high){this->highCol = high;}

    /*!
     * \brief setLowColor gives the Generator a new color to use for low values
     * \param low QColor
     */
    void setLowColor(QColor low){this->lowCol = low;}

    QVector<QVector3D> calcPos();
    QVector<QVector3D> calcSize();
    QVector<QVector3D> calcRot();
    QVector<QVector3D> calcColor();

    //TODO:
    //QVector<Quad> calcQuads();

signals:

public slots:

private:
    void mapToCube();
};

#endif // GENERATOR_H
