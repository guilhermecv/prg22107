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


class InterfaceUSB : public QObject
{
public:
  InterfaceUSB();
  ~InterfaceUSB();

  QString getDeviceInfo(QString portName);
  QString findPort(uint32_t vid, uint32_t pid);   // Procura por uma porta com o pid/vid especificados
  bool connect(QString portName);

protected:


private:
  QSerialPort *_device;
  bool _connected;
};

#endif // INTERFACEUSB_H
