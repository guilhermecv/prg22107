/**
 * @file InterfaceUSB.h
 * @author Guilherme Camargo Valese
 * @brief Gerencia a comunicação com a porta serial
 * @version 0.1
 * @date 2022-03-01
 */
#ifndef INTERFACEUSB_H
#define INTERFACEUSB_H

#include <QDebug>
#include <QStringList>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>


class InterfaceUSB
{
public:
  InterfaceUSB();
  InterfaceUSB(QSerialPort *dev);

  ~InterfaceUSB();

  QString getDeviceInfo(void);

  bool write(const QByteArray& data);
  qint64 write(const char *data);
  
protected:
  QSerialPort *device = NULL;

private:
  QString _serialNumber;
  QString _description;
  QString _manufacturer;
};

#endif // INTERFACEUSB_H
