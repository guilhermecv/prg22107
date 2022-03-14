#include "configuracoes.h"
#include "ui_configuracoes.h"

Configuracoes::Configuracoes(QWidget *parent, Controlador *control) :
    QDialog(parent),
    ui(new Ui::Configuracoes)
{
    ui->setupUi(this);

    dmxControl = control;
    _interfaceUSB = dmxControl->getSerialPort();

    updateControlState(dmxControl->getState());

    connect(ui->clearBuffer, SIGNAL(clicked()), dmxControl, SLOT(clearBuffer()));
    connect(ui->showBuffer, SIGNAL(clicked()), dmxControl, SLOT(printBuffer()));
    connect(ui->TimerInput, SIGNAL(valueChanged(int)), dmxControl, SLOT(setUpdateFrequency(int)));
    connect(dmxControl, SIGNAL(stateChanged(bool)), this, SLOT(updateControlState(bool)));
    connect(ui->bControl, SIGNAL(clicked()), dmxControl, SLOT(toggleRunningState()));
    connect(ui->sendFrame, SIGNAL(clicked()), dmxControl, SLOT(writeFrame()));

    if (_interfaceUSB->getPortInfo() != nullptr)
    {
        QSerialPortInfo *serialInfo;
        serialInfo = _interfaceUSB->getPortInfo();

        ui->Fabricante->setText(serialInfo->manufacturer());
        ui->Serial->setText(serialInfo->serialNumber());
        ui->Descricao->setText(serialInfo->description());
        ui->Localizacao->setText(serialInfo->portName());
    }

    ui->TimerInput->setValue(dmxControl->getUpdateFrequency());
    QString s = QString::number(dmxControl->getBufferSize());
    ui->BufferSize->setText(s);
    ui->progressBar->setValue(dmxControl->getBufferSize());

}

Configuracoes::~Configuracoes()
{
    delete ui;
}

void Configuracoes::updateControlState(bool state)
{
    if(state == true)
    {
        ui->bControl->setText("Parar Controle");
        ui->StatusDMX->setText("Em execução");
    }
    else
    {
        ui->bControl->setText("Iniciar Controle");
        ui->StatusDMX->setText("Em espera");
    }
}
