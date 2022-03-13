#include "dispositivoDMX.h"
#include "ui_dispositivodmx.h"

DispositivoDMX::DispositivoDMX(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DispositivoDMX)
{
    ui->setupUi(this);

    channels = 0;
    address = 0;
}

DispositivoDMX::~DispositivoDMX()
{
    delete ui;
}

void DispositivoDMX::on_nameInput_textChanged(const QString &arg1)
{
    if(arg1 != "")
    {
        ui->addressInput->setEnabled(true);
    }
    else
    {
        ui->addressInput->setEnabled(false);
    }
}


void DispositivoDMX::on_comboBoxMode_highlighted(int index)
{
    ui->deviceInfo->clear();

    switch(index)
    {
    case 0:
        ui->deviceInfo->clear();
        break;

    case 1:
        channels = 3;
        ui->deviceInfo->append("Canal 1: Vermelho");
        ui->deviceInfo->append("Canal 2: Verde");
        ui->deviceInfo->append("Canal 3: Azul");
        break;

    case 2:
        channels = 4;
        ui->deviceInfo->append("Canal 1: Vermelho");
        ui->deviceInfo->append("Canal 2: Verde");
        ui->deviceInfo->append("Canal 3: Azul");
        ui->deviceInfo->append("Canal 4: Branco");
        break;

    case 3:
        channels = 8;
        ui->deviceInfo->append("Canal 1: Vermelho");
        ui->deviceInfo->append("Canal 2: Verde");
        ui->deviceInfo->append("Canal 3: Azul");
        ui->deviceInfo->append("Canal 4: Branco");
        ui->deviceInfo->append("Canal 7: Efeito");
        ui->deviceInfo->append("Canal 8: Velocidade");
        break;

    default:
        break;
    }
}


void DispositivoDMX::on_addressInput_valueChanged(int arg1)
{
    address = arg1;
}

