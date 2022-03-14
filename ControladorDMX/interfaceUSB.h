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

typedef struct
{
  QString serial;
  QString vendor;
  QString description;
  QString portName;
}InterfaceInfo_t;


class InterfaceUSB : public QObject
{
public:
  InterfaceUSB();
  ~InterfaceUSB();

  QSerialPortInfo* getPortInfo() {return portInfo;};
  QSerialPort* serialPort() {return _device;};          // obtem o ponteiro para a porta serial

  static QString findPort(uint32_t vid, uint32_t pid);   // Procura por uma porta com o pid/vid especificados
  bool connect(QString portName);
  bool connect();

  bool write(const QByteArray &data);
  void write(const char *data);
  void write(const char *data, int length);

private:
  QSerialPort *_device;
  QSerialPortInfo *portInfo = nullptr;

  bool _connected;
};

#endif // INTERFACEUSB_H
