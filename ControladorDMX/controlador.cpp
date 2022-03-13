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

    clearBuffer();
}

bool Controlador::getState()
{
    return controlState;
}

void Controlador::setState(bool state)
{
    controlState = state;
    emit stateChanged(controlState);
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
    emit stateChanged(controlState);
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


