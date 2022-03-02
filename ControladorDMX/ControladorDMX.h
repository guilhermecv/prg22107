#ifndef CONTROLADORDMX_H
#define CONTROLADORDMX_H

#include <QObject>


#define DMX_MAX_SIZE    20
#define DMX_OUT_FREQ    30
#define FTDI_VID        1027
#define FTDI_PID        24577
#define FTDI_BAUDRATE   250000

class ControladorDMX
{
public:
  ControladorDMX();
  ~ControladorDMX();


  bool getState(void);
  void setState(bool state);

  void setTimerValue(int value);
  int getTimerValue(void);

private:
  bool _state;
  int _timerValue;

  QTimer *timer;

  unsigned char dmxBuffer[DMX_MAX_SIZE];
};

#endif // CONTROLADORDMX_H
