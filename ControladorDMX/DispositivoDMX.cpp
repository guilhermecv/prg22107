#include "DispositivoDMX.h"
#include "ui_dispositivodmx.h"
#include <QDebug>

DispositivoDMX::DispositivoDMX(QWidget *parent, ControladorDMX *dmxControl) : QDialog(parent),
                                                                              ui(new Ui::DispositivoDMX)
{
  ui->setupUi(this);

  ui->channels_edit->setEnabled(false);
  ui->address_edit->setEnabled(false);

  DeviceAddress = 0;
}

DispositivoDMX::~DispositivoDMX()
{
  delete ui;
}

void DispositivoDMX::editDevice()
{
  qDebug() << "Editando dispositivo";
}

void DispositivoDMX::on_name_edit_editingFinished()
{

  if (ui->name_edit->text() != "")
  {
    DeviceName = ui->name_edit->text();
    ui->channels_edit->setEnabled(true);
    ui->address_edit->setEnabled(true);
  }
  else
  {
    ui->channels_edit->setEnabled(false);
    ui->address_edit->setEnabled(false);
  }
}

bool DispositivoDMX::isDeviceValid(void)
{
  if (DeviceName != "")
    return true;
  else
    return false;
}