/**
 * @file InterfaceUSB.cpp
 * @author Guilherme Camargo Valese
 * @brief Gerencia a comunicação com a porta serial
 * @version 0.1
 * @date 2022-03-01
 */
#include "interfaceUSB.h"
#include <QMessageBox>
#include "controlador.h"

/**
 * @brief Construct a new InterfaceUSB::InterfaceUSB object
 */
InterfaceUSB::InterfaceUSB()
{
    _device = new QSerialPort();
    portInfo = nullptr;
}

/**
 * @brief Destroy the InterfaceUSB::InterfaceUSB object
 */
InterfaceUSB::~InterfaceUSB()
{
    _device->close();
    delete _device;
}

/**
 * @brief Busca pelo dispositivo com o vid e pid fornecidos
 *
 * @param vid
 * @param pid
 * @return QString porta serial encontrada
 */
QString InterfaceUSB::findPort(uint32_t vid, uint32_t pid)
{
    bool found = false;

    foreach (const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts())
    {
        if (vid != 0 && pid != 0 &&
            serialPortInfo.hasVendorIdentifier() && serialPortInfo.hasProductIdentifier() &&
            serialPortInfo.vendorIdentifier() == vid && serialPortInfo.productIdentifier() == pid)
        {
            found = true;
        }

        if (vid != 0 && pid == 0 &&
            serialPortInfo.hasVendorIdentifier() &&
            serialPortInfo.vendorIdentifier() == vid)
        {
            found = true;
        }

        if (found)
        {
            return serialPortInfo.portName();
        }
    }
    return "";
}

/**
 * @brief
 * @param portName porta serial
 * @return true sucesso na conexão
 * @return false falha na conexão
 */
bool InterfaceUSB::connect(QString portName)
{
    _device->setPortName(portName);
    _device->setBaudRate(FTDI_BAUDRATE);
    _device->setFlowControl(QSerialPort::NoFlowControl);
    _device->setDataBits(QSerialPort::Data8);
    _device->setParity(QSerialPort::NoParity);
    _device->setStopBits(QSerialPort::TwoStop);

    _connected = _device->open(QIODevice::ReadWrite);

    if (_connected)
    {
        qDebug() << "Conectado corretamente";
        portInfo = new QSerialPortInfo(portName);
        return true;
    }
    else
    {
        qDebug() << "Falha na conexao";
        qDebug() << "Erro: " << _device->error();
        return false;
    }
}

bool InterfaceUSB::connect()
{
    QString portName = findPort(FTDI_VID, FTDI_PID);
    return connect(portName);
}

/**
 * @brief
 *
 * @param data
 * @return true dados enviados corretamente
 * @return false falha no envio dos dados
 */
bool InterfaceUSB::write(const QByteArray &data)
{
    if (_device == nullptr)
        return false;

    qDebug() << "Write QByteArray: " << _device->write(data);
    if (_device->write(data) != 0)
        return false;

    return true;
}

void InterfaceUSB::write(const char *data)
{
    qDebug() << "write" << _device->write(data, qstrlen(data));
}
