/**
 * @file InterfaceUSB.cpp
 * @author Guilherme Camargo Valese
 * @brief Gerencia a comunicação com a porta serial
 * @version 0.1
 * @date 2022-03-01
 */
#include "InterfaceUSB.h"
#include <QMessageBox>


/**
 * @brief Construct a new InterfaceUSB::InterfaceUSB object
 */
InterfaceUSB::InterfaceUSB()
{
}

InterfaceUSB::InterfaceUSB(QSerialPort *dev)
{
  device = dev;
}

/**
 * @brief Destroy the InterfaceUSB::InterfaceUSB object
 */
InterfaceUSB::~InterfaceUSB()
{
    if (device->isOpen())
        device->close();
}

QString InterfaceUSB::getDeviceInfo(void)
{
    QString info;

    if (device == NULL)
    {
        info = "Nenhum dipositivo conectado!";
    }
    else
    {
        info += "S/N: " + _serialNumber + "\n";
        info += "Fabricante: " + _manufacturer + "\n";
    }
    return info;
}

bool InterfaceUSB::write(const QByteArray &data)
{
  return false;
}

qint64 InterfaceUSB::write(const char *data)
{
  return 0;
}
