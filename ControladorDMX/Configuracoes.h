/**
 * @file configuracoes.h
 * @author Guilherme Camargo Valese
 * @brief
 * @version 0.1
 * @date 2022-03-01
 */
#ifndef CONFIGURACOES_H
#define CONFIGURACOES_H

#include <QDialog>
#include "ControladorDMX.h"

namespace Ui
{
  class Configuracoes;
}

class Configuracoes : public QDialog
{
  Q_OBJECT

public:
  explicit Configuracoes(QWidget *parent = nullptr, ControladorDMX *dmx = nullptr);
  ~Configuracoes();

private slots:
  void on_checkBox_stateChanged(int arg1);
  void on_TimerInput_valueChanged(int arg1);

private:
  Ui::Configuracoes *ui;

  ControladorDMX *dmxcontrol;
};

#endif // CONFIGURACOES_H
