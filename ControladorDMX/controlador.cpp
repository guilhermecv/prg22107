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
    connect(usb->serialPort(), &QSerialPort::errorOccurred, this, &Controlador::handleInterfaceError);

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
    return sizeof(dmxBuffer);
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

void Controlador::handleInterfaceError()
{
    qDebug() << "handle Serial Error";

    setState(false);
    usbConnected = false;
    emit interfaceError();

    qDebug() << usb->serialPort()->errorString();

    QMessageBox msgBox;
    msgBox.critical(0, "Erro de interface USB", usb->serialPort()->errorString());
}

void Controlador::writeFrame()
{
    if(usbConnected)    usb->serialPort()->setBreakEnabled(false);
    QThread::usleep(88);
    if(usbConnected)    usb->serialPort()->setBreakEnabled(true);
    QThread::usleep(8);
    if(usbConnected)    usb->serialPort()->setBreakEnabled(false);

    if(usbConnected)    usb->serialPort()->setRequestToSend(true);

    dmxBuffer[0] = DMX_START_CODE;
    if(usbConnected)    usb->write((const char*)dmxBuffer, sizeof(dmxBuffer));
    if(usbConnected)    usb->serialPort()->flush();

    if(usbConnected)    usb->serialPort()->setRequestToSend(false);
    if(usbConnected)    usb->serialPort()->setBreakEnabled(false);
}

void Controlador::clearBuffer()
{
    for(int i = 0; i < DMX_MAX_SIZE; i++)
        dmxBuffer[i] = 0;
}

void Controlador::setChannel(int channel, int value)
{
    qDebug() << "Channel " << channel << " changed to " << value;
    dmxBuffer[channel] = static_cast<unsigned char>(value);
}

void Controlador::printBuffer()
{
    qDebug() << "Exibindo conteudo do buffer";

    for(int i = 0; i < DMX_MAX_SIZE; i++)
        qDebug() << "["<<i<<"] : "<<dmxBuffer[i];
}


