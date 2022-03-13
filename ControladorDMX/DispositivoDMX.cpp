#include "dispositivoDMX.h"
#include "ui_dispositivodmx.h"

#include <QMessageBox>



DispositivoDMX::DispositivoDMX(QWidget *parent, QHBoxLayout *layout) : QDialog(parent),
    ui(new Ui::DispositivoDMX)
{
    ui->setupUi(this);

    channels = 0;
    address = 0;
    mode = 0;
    selectedChannel = 0;

    DeviceValid = false;
    deviceLayout = layout;
    deviceWidget = parent;

    if(deviceLayout == nullptr)
    {
        qDebug() << "Ponteiro nulo para layout";
        return;
    }

    signalMapper = new QSignalMapper(this);
}

DispositivoDMX::~DispositivoDMX()
{
    delete ui;
}

void DispositivoDMX::checkConfig()
{
    address = ui->addressInput->value();

    if (DeviceName != "" && channels != 0 && address != 0 && mode != 0)
    {
        qDebug() << "Configuração válida";
        DeviceValid = true;
    }
    else
    {
        qDebug() << "Configuração Inválida";
        DeviceValid = false;
    }
}

void DispositivoDMX::addDevice()
{
    QGroupBox *groupBox = new QGroupBox(deviceWidget);
    groupBox->setTitle(DeviceName);

    qDebug() << "GroupBox created ";

    auto *groupBoxLayout = new QHBoxLayout(groupBox);

    for(int i = 0; i < channels; i++)
    {
        slider[i] = new QSlider(deviceWidget);
        qDebug() << "Slider created " << deviceLayout->count();
        slider[i]->setRange(0, 255);
        slider[i]->setOrientation(Qt::Vertical);
        slider[i]->setTickInterval(50);
        slider[i]->setTickPosition(QSlider::TicksBothSides);
        qDebug() << "Slider configured";
        groupBoxLayout->addWidget(slider[i]);

        connect(slider[i], SIGNAL(valueChanged(int)), this, SLOT(sliderValueChanged()));
        connect(slider[i], &QSlider::valueChanged, signalMapper, static_cast<void(QSignalMapper::*)()>(&QSignalMapper::map));

        signalMapper->setMapping(slider[i], i);     // Alterando o valor, enviamos o ID do slider
        connect(signalMapper, SIGNAL(mappedInt(int)), this, SLOT(channelUpdate(int)));
    }
    dumpObjectInfo();

    groupBox->setLayout(groupBoxLayout);
    deviceLayout->addWidget(groupBox);
    qDebug() << "Widget inserted";
}

void DispositivoDMX::on_nameInput_textChanged(const QString &arg1)
{
    if (arg1 != "")
    {
        ui->addressInput->setEnabled(true);
        DeviceName = arg1;
    }
    else
    {
        ui->addressInput->setEnabled(false);
    }
}

void DispositivoDMX::on_comboBoxMode_highlighted(int index)
{
    ui->deviceInfo->clear();

    mode = index;

    switch (index)
    {
    case 0:
        ui->deviceInfo->clear();
        break;
    case 1:
        channels = 1;
        ui->deviceInfo->append("Canal 1: Intensidade");
        break;
    case 2:
        channels = 3;
        ui->deviceInfo->append("Canal 1: Vermelho");
        ui->deviceInfo->append("Canal 2: Verde");
        ui->deviceInfo->append("Canal 3: Azul");
        break;

    case 3:
        channels = 4;
        ui->deviceInfo->append("Canal 1: Vermelho");
        ui->deviceInfo->append("Canal 2: Verde");
        ui->deviceInfo->append("Canal 3: Azul");
        ui->deviceInfo->append("Canal 4: Branco");
        break;

    case 4:
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

void DispositivoDMX::on_buttonBox_accepted()
{
    checkConfig();

    if(DeviceValid)
    {
        addDevice();
        close();
    }
    else
    {
        QString message = "As informações abaixo não são válidas\n\n";
        QMessageBox msgBox;

        if(DeviceName == "") message += "Nome do dispositivo\n";
        if(address == 0)    message += "Endereço\n";
        if(mode == 0)   message += "Modo de operação \n";
        if(deviceLayout == nullptr) message += "Ponteiro nulo para layout";
        msgBox.warning(this, "Erro ao incluir novo dispositivo", message);
    }
}

void DispositivoDMX::sliderValueChanged()
{
    QSlider *m_slider = (QSlider*)sender();
    int value = m_slider->value();

    qDebug() << "Buffer [ " << selectedChannel << "] = [ " << value << "]";
}

void DispositivoDMX::channelUpdate(int ch)
{
    qDebug() << "Chanel " << ch;

    selectedChannel = address + ch;
}

