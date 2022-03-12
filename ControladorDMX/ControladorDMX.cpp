#include "ControladorDMX.h"
#include <QDebug>
#include <QMessageBox>
#include <QThread>

ControladorDMX::ControladorDMX()
{
    timer = new QTimer();

    usb = new InterfaceUSB();
    USBConnected = usb->connect();

    _updateFrequency = 1;

    timer->setInterval(1000 / _updateFrequency);
    timer->setTimerType(Qt::PreciseTimer);

    connect(timer, &QTimer::timeout, this, &ControladorDMX::updateValues);
    // limpa o buffer do DMX
    dmxBuffer.fill(0x1, DMX_MAX_SIZE);
    for (int i = 0; i < DMX_MAX_SIZE; i++)
        m_dmx[i] = 0;

    // connect(usb, SIGNAL(error(QSerialPort::SerialPortError)), this, &ControladorDMX::handleSerialError);
    //connect(usb,
    qDebug() << "ControladorDMX construtor";
}

ControladorDMX::~ControladorDMX()
{
    delete timer;
    delete usb;
}

error_t ControladorDMX::getState()
{
  return _state;
/*
    if (_state == true)
    {
        return noError;
    }
    else
    {
        if(timer->isActive() == false)  return Timer_nao_configurado;
        if(USBConnected == false)   return Erro_de_interface_usb;
    }*/

}

void ControladorDMX::setState(error_t state)
{
    _state = state;

    if(_state == executando)
    {
        timer->start();
    }
    else
    {
        timer->stop();
    }

    emit stateChanged();
}

void ControladorDMX::setUpdateFrequency(int value)
{
    _updateFrequency = value;
    timer->setInterval(1000 / _updateFrequency);

    qDebug() << "Taxa de atualização " + QString::number(_updateFrequency, 10) << " Hz";
}

int ControladorDMX::getUpdateFrequency()
{
    return _updateFrequency;
}

int ControladorDMX::getBufferUsage()
{
    return dmxBuffer.size();
}

/**
 * @brief ControladorDMX::setChannel
 * @param channel
 * @param value
 */
void ControladorDMX::setChannel(int channel, char value)
{
    if (channel > dmxBuffer.size())
        return;

    dmxBuffer[channel] = value;
    m_dmx[channel] = static_cast<unsigned char>(value);

    qDebug() << "set channel[" << channel << "] : " << value;
}

void ControladorDMX::sendFrame(unsigned char *data)
{
    if (usb->serialPort()->setBreakEnabled(false) == false)
    {
        handleSerialError(usb->serialPort()->error());
        setState(Erro_de_interface_usb);
        return;
    }
    QThread::usleep(88);
    usb->serialPort()->setBreakEnabled(true);
    QThread::usleep(8);
    usb->serialPort()->setBreakEnabled(false);

    usb->serialPort()->setRequestToSend(true);
    unsigned char startCode[] = {DMX_START_CODE};
    usb->write((const char *)startCode);
    usb->write(dmxBuffer);

    usb->serialPort()->setRequestToSend(false);
    usb->serialPort()->setBreakEnabled(false);
}

void ControladorDMX::togleState()
{
    if(_state == em_espera) _state = executando;
    else _state = em_espera;

    setState(_state);
}

void ControladorDMX::updateControlState(bool state)
{
    //_state = state;
    //setState(_state);
}

/**
 * @brief
 */
void ControladorDMX::updateValues()
{
    qDebug() << "Send DMX buffer";
    if (USBConnected == false)
    {
        qDebug() << "Interface não conectada!";
        setState(Erro_de_interface_usb);
    }
    else
    {
        sendFrame(m_dmx);
    }
}

void ControladorDMX::handleSerialError(QSerialPort::SerialPortError error)
{
    qDebug() << "handle serial error";
    switch (error)
    {
    case QSerialPort::SerialPortError::NoError:
        break;

    case QSerialPort::SerialPortError::DeviceNotFoundError:
        qDebug() << "Dispositivo não encontrado";
        break;

    case QSerialPort::SerialPortError::OpenError:
        qDebug() << "Erro na abertura da serial";
        break;

    case QSerialPort::SerialPortError::WriteError:
        qDebug() << "Erro ao escrever na serial";
        break;

    case QSerialPort::SerialPortError::ResourceError:
        qDebug() << "resource error";
        break;

    case QSerialPort::SerialPortError::TimeoutError:
        qDebug() << "Timeout error";
        break;

    case QSerialPort::SerialPortError::NotOpenError:
        qDebug() << "not open error";
        break;
    }
}
