#ifndef CONTROLADORDMX_H
#define CONTROLADORDMX_H

#include <QObject>
#include "InterfaceUSB.h"

#define DMX_MAX_SIZE    20
#define DMX_OUT_FREQ    30
#define DMX_MAX_FREQ    60
#define FTDI_VID        1027
#define FTDI_PID        24577
#define FTDI_BAUDRATE   250000


// Definicoes dos erros
#define TIMER_NAO_CONFIGURADO     10
#define DMX_INTERFACE_NOT_OPEN    20
#define DMX_INTERFACE_OPEN        21
#define FALHA_ENVIO_BUFFER        30
#define SUCCESS                   0


class ControladorDMX
{
public:
  ControladorDMX();
  ~ControladorDMX();

  int getState(void);
  void setState(bool state);

  void setTimerValue(int value);
  int getTimerValue(void);

private:
  bool _state;
  int _timerValue;

  QTimer *timer;
  InterfaceUSB *usb;

  unsigned char dmxBuffer[DMX_MAX_SIZE];
};

#endif // CONTROLADORDMX_H
