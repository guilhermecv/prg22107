#include "ControladorDMX.h"
#include <QDebug>

ControladorDMX::ControladorDMX()
{
  timer = nullptr;

  for(int i=0; i<DMX_MAX_SIZE; i++)
    dmxBuffer[i] = 0;

  qDebug() << "ControladorDMX construtor";
}

ControladorDMX::~ControladorDMX()
{
  qDebug() << "ControladorDMX destrutor";
}

bool ControladorDMX::getState()
{
  return _state;
}

void ControladorDMX::setState(bool state)
{
  _state = state;
}

void ControladorDMX::setTimerValue(int value)
{
  _timerValue = value;
  qDebug() << "Timer " + QString::number(_timerValue, 10);
}

int ControladorDMX::getTimerValue()
{
  return _timerValue;
}
