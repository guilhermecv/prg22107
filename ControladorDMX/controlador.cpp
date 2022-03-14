#include "controlador.h"
#include <QDebug>
#include <QMessageBox>
#include <QThread>

Controlador::Controlador(QObject *parent)
    : QObject{parent}
{
    timer = new QTimer;

    usb = new InterfaceUSB;
    usbConnected = usb->connect();

    controlState = false;   // Inicia com o controlador desligado

    updateFrequency = 1;

    // configura o timer
    timer->setInterval(1000 / updateFrequency);
    timer->setTimerType(Qt::PreciseTimer);

    connect(timer, &QTimer::timeout, this, &Controlador::timerAction);

    clearBuffer();
}

bool Controlador::getState()
{
    return controlState;
}

void Controlador::setState(bool state)
{
    controlState = state;

    if(controlState == true)
        timer->start();
    else
        timer->stop();

    emit stateChanged(controlState);
}

int Controlador::getBufferSize()
{
    return m_dmxBuffer.size();
}

void Controlador::setUpdateFrequency(int freq)
{
    updateFrequency = freq;
    timer->setInterval(1000 / updateFrequency);
    qDebug() << "Taxa de atualização " << QString::number(updateFrequency, 10) << " Hz";
}

void Controlador::toggleRunningState()
{
    controlState = !controlState;
    setState(controlState);
    emit stateChanged(controlState);
}

void Controlador::timerAction()
{
    if(usbConnected == false)
    {
        setState(false);
        QMessageBox msgBox;
        msgBox.warning(nullptr, "Controlador DMX", "Nenhuma interface USB detectada!");
    }
    else
    {
        writeFrame();
    }
}

void Controlador::writeFrame()
{
    if(!usb->serialPort()->setBreakEnabled(false))   setState(false);

    QThread::usleep(88);
    if(!usb->serialPort()->setBreakEnabled(true))   setState(false);
    QThread::usleep(8);
    if(!usb->serialPort()->setBreakEnabled(false))   setState(false);

    usb->serialPort()->setRequestToSend(true);
    unsigned char startCode[] = {DMX_START_CODE};
    usb->write((const char *)startCode);
    usb->serialPort()->write(m_dmxBuffer);

    usb->serialPort()->setRequestToSend(false);
    usb->serialPort()->setBreakEnabled(false);
}

void Controlador::clearBuffer()
{
    qDebug() << "Limpando buffer";

    m_dmxBuffer.fill(0x00, DMX_MAX_SIZE);
    for(int i = 0; i < DMX_MAX_SIZE; i++)
        dmxBuffer[i] = 0;
}

void Controlador::setChannel(int channel, int value)
{
    qDebug() << "Channel " << channel << " changed to " << value;

    dmxBuffer[channel] = value;
    m_dmxBuffer[channel] = static_cast<int>(value);
}

void Controlador::printBuffer()
{
    qDebug() << "Exibindo conteudo do buffer";

    for(int i = 0; i < DMX_MAX_SIZE; i++)
        qDebug() << "["<<i<<"] : "<<dmxBuffer[i];
}


