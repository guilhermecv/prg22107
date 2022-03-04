/**
 * @file configuracoes.cpp
 * @author Guilherme Camargo Valese
 * @brief
 * @version 0.1
 * @date 2022-03-01
 */
#include "Configuracoes.h"
#include "ui_configuracoes.h"
#include "ControladorDMX.h"
#include "InterfaceUSB.h"

Configuracoes::Configuracoes(QWidget *parent, ControladorDMX *dmx) : QDialog(parent),
                                                                     ui(new Ui::Configuracoes)
{
  qDebug() << "configuracoes construtor";
  ui->setupUi(this);
  dmxcontrol = dmx;
  bool initialState = false;
  //dmx->getState();

  // Atualiza o estado atual
  ui->checkBox->setChecked(initialState);
  ui->TimerInput->setValue(dmx->getTimerValue());
  ui->USB_info->append(InterfaceUSB::getDeviceInfo("COM5"));
}

Configuracoes::~Configuracoes()
{
  qDebug() << "configuracoes destrutor";
  delete ui;
}

void Configuracoes::on_checkBox_stateChanged(int arg1)
{
  if (arg1 == 0)
    dmxcontrol->setState(false);
  else
    dmxcontrol->setState(true);
}

void Configuracoes::on_TimerInput_valueChanged(int arg1)
{
  dmxcontrol->setTimerValue(arg1);
}
