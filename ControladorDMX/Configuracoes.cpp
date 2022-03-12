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
#include <QDebug>

Configuracoes::Configuracoes(QWidget *parent, ControladorDMX *dmx) : QDialog(parent),
                                                                     ui(new Ui::Configuracoes)
{
  ui->setupUi(this);

  dmxcontrol = dmx;

  _interfaceUSB = dmxcontrol->getSerialPort();

  if (_interfaceUSB->getPortInfo() != nullptr)
  {
    QSerialPortInfo *serialInfo;
    serialInfo = _interfaceUSB->getPortInfo();

    ui->Fabricante->setText(serialInfo->manufacturer());
    ui->Serial->setText(serialInfo->serialNumber());
    ui->Descricao->setText(serialInfo->description());
    ui->Localizacao->setText(serialInfo->portName());
  }
  else
  {
    
  }

  // Atualiza o estado atual
  ui->TimerInput->setValue(dmx->getUpdateFrequency());

  QString s = QString::number(dmx->dmxBuffer.size());
  ui->BufferSize->setText(s);
  ui->progressBar->setValue(dmxcontrol->getBufferUsage());
  ui->StatusDMX->setText("Desconhecido");

  connect(dmx, SIGNAL(stateChanged()), this, SLOT(updateControlState()));
  connect(ui->pushButton2, SIGNAL(clicked()), dmx, SLOT(sendFrame()));
}

Configuracoes::~Configuracoes()
{
  delete ui;
}

void Configuracoes::on_TimerInput_valueChanged(int arg1)
{
  dmxcontrol->setUpdateFrequency(arg1);
}

void Configuracoes::on_pushButton_clicked()
{
  dmxcontrol->togleState();
}

void Configuracoes::updateControlState()
{
  error_t state = dmxcontrol->getState();

  switch (state)
  {
  case em_espera:
    ui->pushButton->setText("Ativar controlador");
    ui->StatusDMX->setText("Em espera");
    break;

  case executando:
    ui->pushButton->setText("Parar controlador");
    ui->StatusDMX->setText("Em execução");
    break;

  case Falha_envio_buffer:
    ui->pushButton->setText("Ativar controlador");
    ui->StatusDMX->setText("Falha envio buffer");
    break;

  case Erro_de_interface_usb:
    ui->pushButton->setText("Ativar controlador");
    ui->StatusDMX->setText("Erro interface USB");
    break;

  default:
    ui->pushButton->setText("Ativar controlador");
    ui->StatusDMX->setText("Desconhecido");
    break;
  }
}
