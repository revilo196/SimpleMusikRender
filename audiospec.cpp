#include "audiospec.h"
#include <QAudioBuffer>
#include "ffft/FFTReal.h"

/*!
 * \brief AudioSpec::AudioSpec Initilize the AudioInterface and sets the audio Input
 * \param AudioName QString name of the audioInputDevice
 * \param parent QObject* Parent
 */
AudioSpec::AudioSpec(QString AudioName, QObject *parent) : QObject(parent)
{

    QList<QAudioDeviceInfo> list = QAudioDeviceInfo::availableDevices(QAudio::AudioInput);

    QAudioDeviceInfo found;
    foreach (QAudioDeviceInfo str, list) {
        //qInfo() << str.deviceName();

    if(str.deviceName() == AudioName )
            found = str;
    }

/*
     //DEBUG
    qInfo()<< "SampleSizes"<<found.supportedSampleSizes();
    qInfo() << "SampleRate" << found.supportedSampleRates();
    qInfo() << "SampleType" << found.supportedSampleTypes();
    qInfo() << "Codecs" << found.supportedCodecs();
    qInfo() << "Channels" << found.supportedChannelCounts();
    qInfo() << "ByteOrder" << found.supportedByteOrders();
*/

    QAudioFormat form;

    form.setByteOrder(QAudioFormat::LittleEndian);
    form.setChannelCount(2);
    form.setSampleType(QAudioFormat::Float);
    form.setSampleRate(22050);
    form.setSampleSize(32);
    form.setCodec("audio/pcm");

    if (!found.isFormatSupported(form)) {
        qWarning() << "Default format not supported, trying to use the nearest.";
        form = found.nearestFormat(form);
    }

    audioFormat = new QAudioFormat(form);
    audioIn = new QAudioInput(found,*audioFormat,this);

/*
    qInfo() << "ByteOrder" << form.byteOrder();
    qInfo() << "Channels" <<form.channelCount();
    qInfo() << "Codecs" << form.codec();
    qInfo() << "SampleType" <<form.sampleType();
    qInfo() << "SampleRate" << form.sampleRate();
    qInfo()<< "SampleSizes"<< form.sampleSize();
    qInfo() << "Vol:" << audioIn->volume();
    qInfo() << "per:" << audioIn->periodSize();

    qInfo() << audioIn->state();
 */
}

void AudioSpec::startListen()
{
    audioIn->setBufferSize(20000);


    audioIn->setNotifyInterval(1000);

    connect(audioIn,SIGNAL(notify()),this,SLOT(notified()));

    audioInDev = audioIn->start();

    connect(audioInDev,SIGNAL(readyRead()),this,SLOT(sound()));



}
/*!
 * \brief AudioSpec::sound uses currently ready audio data to calulate RMS and Spectrum
 *
 * is automaticly called after \link(startListen()) was used when data is ready
 */
void AudioSpec::sound()
{
    const int fSize = 2048; //max buffer size in float and for each channel
    const qint64 bytesReady = audioIn->bytesReady();
    const qint64 maxBuffer = fSize * sizeof(float) * audioFormat->channelCount();
    const qint64 bufferSpace = maxBuffer - dataBuffer.size();

    //fill the audio Buffer
    if(bytesReady <= bufferSpace)
        dataBuffer += audioInDev->read(bytesReady);
    else
        dataBuffer += audioInDev->read(bufferSpace);


    //Only Calulate when the audioBuffer is full
    if(dataBuffer.size() == maxBuffer)
    {

        QAudioBuffer buffer(dataBuffer,*audioFormat);


        dataBuffer.remove(0,dataBuffer.size()/2);


        //qInfo() << bytesReady <<" || " << maxBuffer;
        QAudioBuffer::S32F * rawData = (QAudioBuffer::S32F*)buffer.data();
        int size = buffer.frameCount();

        //CalculateRMS-----------
        int i;
        double sumsquared;
        double RMS;
        float x[fSize];
        sumsquared = 0;
        for (i = 0; i < size; i++)
        {
            float inR = rawData[i].right;
            float inL = rawData[i].left;

            x[i] = rawData[i].right;

            if(inR < 0)
                inR = -inR;

            if(inL < 0)
                inL =-inL;

            sumsquared += inR*inR;
        }
        RMS = sqrt((double(1)/size)*(sumsquared));
        //Save for output-----------
        this->RMS = RMS;

        //calculate fft---------------
        ffft::FFTReal<float> fftBase(size);
        float erg[fSize];
        fftBase.do_fft(erg,x);


        Spectro.resize(fSize/2);//constant because of the fixed audioBufferSize

        for(int j = 0; j < size/2;j++){

            double mag =  sqrt((erg[j]* erg[j]) + (erg[(j + 1) + (size/2) ]*erg[(j + 1) + (size/2)]));

            //Save for output
            Spectro.replace(j,mag);
        }


    }

}

/*!
 * \brief AudioSpec::notified
 * Dummy is called after every second of audioData
 */
void AudioSpec::notified()
{
    qInfo() << "NOTI";;
}


