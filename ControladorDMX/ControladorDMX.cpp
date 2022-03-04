#include "ControladorDMX.h"
#include <QDebug>
#include <QMessageBox>

ControladorDMX::ControladorDMX()
{
  timer = nullptr;
  usb = nullptr;

  // limpa o buffer do DMX
  for (int i = 0; i < DMX_MAX_SIZE; i++)
    dmxBuffer[i] = 0;

  qDebug() << "ControladorDMX construtor";
}

ControladorDMX::~ControladorDMX()
{
  qDebug() << "ControladorDMX destrutor";
}

int ControladorDMX::getState()
{
  /*
  if(timer == nullptr)
  {
    QMessageBox::about(nullptr, "erro", "timer não configurado");
    return TIMER_NAO_CONFIGURADO;
  }*/

  if(usb == nullptr)
  {
    QMessageBox::about(nullptr, "erro", "Nenhuma interface USB detectada");
    return DMX_INTERFACE_NOT_OPEN;
  }
  return 0;
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
