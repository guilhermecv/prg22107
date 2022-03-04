/**
 * @file InterfaceUSB.cpp
 * @author Guilherme Camargo Valese
 * @brief Gerencia a comunicação com a porta serial
 * @version 0.1
 * @date 2022-03-01
 */
#include "InterfaceUSB.h"
#include <QMessageBox>
#include "ControladorDMX.h"

/**
 * @brief Construct a new InterfaceUSB::InterfaceUSB object
 */
InterfaceUSB::InterfaceUSB()
{
    qDebug() << "InterfaceUSB construtor 1";
    _device = new QSerialPort();
}

/**
 * @brief Destroy the InterfaceUSB::InterfaceUSB object
 */
InterfaceUSB::~InterfaceUSB()
{
    qDebug() << "InterfaceUSB destrutor";
    _device->close();
    delete _device;
}

/**
 * @brief Retorna as informações do dispositivo
 * @return QString
 */
QString InterfaceUSB::getDeviceInfo(QString portName)
{
    QString info;
    QSerialPortInfo portInfo(portName);

    info += portInfo.description() + "\n";
    info += "Fabricante: " + portInfo.manufacturer() + "\n";
    info += "S/N: " + portInfo.serialNumber() + "\n";

    return info;
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
            return serialPortInfo.portName();
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
    _connected = _device->open(QIODevice::ReadWrite);

    if (_connected)
    {
        // Configura a porta serial
        _device->setBaudRate(FTDI_BAUDRATE);
        _device->setFlowControl(QSerialPort::NoFlowControl);
        _device->setDataBits(QSerialPort::Data8);
        _device->setParity(QSerialPort::NoParity);
        _device->setStopBits(QSerialPort::TwoStop);
        return true;
    }
    return false;
}
