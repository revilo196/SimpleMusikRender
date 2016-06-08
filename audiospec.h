#ifndef AUDIOSPEC_H
#define AUDIOSPEC_H

#include <QObject>
#include <QAudioInput>
#include <QIODevice>
#include <QDebug>

/*!
 * \brief The AudioSpec class that calulates RMS and Spectum of an AudioInput
 *
 *
 */
class AudioSpec : public QObject
{
    Q_OBJECT

    QAudioInput* audioIn;
    QIODevice * audioInDev;
    QAudioFormat * audioFormat;

    QByteArray dataBuffer;

    double RMS;
    QVector<float> Spectro;

public:
    explicit AudioSpec(QString audioName, QObject *parent = 0);


    /*!
     * \brief startListen starts the audioProccessing loop
     *
     * calulates a spectrum live from audio stream
     */
    void startListen();


    /*!
     * \brief getRMS gets the current audio RMS
     * \return double current RMS
     */
    double getRMS(){return RMS;}
    /*!
     * \brief getSpectro
     * \return
     */
    QVector<float> getSpectro(){return Spectro;}


public slots:

    void sound();
    void notified();


private:

};

#endif // AUDIOSPEC_H
