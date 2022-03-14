#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QWidget>
#include <QSlider>
#include <QLabel>
#include <QListWidgetItem>

#include <QDebug>
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>

#include <QPixmap>

#include "dispositivoDMX.h"
#include "configuracoes.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->statusbar->showMessage("Iniciando...", 2000);

    dmxControl = new Controlador();

    updateControlState(dmxControl->getState());

    connect(ui->actionConfig, &QAction::triggered, this, &MainWindow::openConfig);
    connect(ui->actionAboutQt, &QAction::triggered, this, &MainWindow::aboutQt);
    connect(ui->actionDoc, &QAction::triggered, this, &MainWindow::openWiki);
    connect(ui->actionAddDevice, &QAction::triggered, this, &MainWindow::addDevice);
    connect(ui->bAdd, &QPushButton::clicked, this, &MainWindow::addDevice);
    connect(dmxControl, SIGNAL(stateChanged(bool)), this, SLOT(updateControlState(bool)));
    connect(ui->bControle, SIGNAL(clicked()), dmxControl, SLOT(toggleRunningState()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete dmxControl;
}

void MainWindow::openConfig()
{
    Configuracoes *config = new Configuracoes(this, dmxControl);
    config->show();
}

void MainWindow::openWiki()
{
    QDesktopServices::openUrl(QUrl("https://github.com/guilhermecv/prg22107"));
}

void MainWindow::aboutQt()
{
    QMessageBox::aboutQt(this, tr("Sobre o Qt"));
}

void MainWindow::addDevice()
{
    auto layout = qobject_cast<QHBoxLayout*>(ui->tabControl->layout());
    DispositivoDMX *_dispositivoDMX = new DispositivoDMX(ui->tabControl, layout, dmxControl);
    _dispositivoDMX->exec();
    if(_dispositivoDMX->DeviceValid == true)
    {
        qDebug() << "append device";
        dispositivos.append(_dispositivoDMX);
        ui->listWidget->addItem(_dispositivoDMX->getDeviceName());
    }

    qDebug() << "device count " << dispositivos.length();
}

void MainWindow::on_bRemover_clicked()
{
    // Quando usado com connect, sender() passa o endereço do slider a ser removido

    // QSlider* slider = qobject_cast<QSlider*>(sender());
    // delete slider;

    ui->listWidget->selectedItems();

    deleteDevice(0);
}

void MainWindow::updateControlState(bool state)
{
    if(state == true)
    {
        ui->statusbar->showMessage("Executando", 0);
        ui->bControle->setText("Parar");
        ui->bControle->setIcon(QIcon(":/pause.png"));
    }
    else
    {
        ui->statusbar->showMessage("Em espera", 0);
        ui->bControle->setText("Iniciar");
        ui->bControle->setIcon(QIcon(":/play.png"));
    }
}


DispositivoDMX *MainWindow::deviceAtIndex(int index)
{
    return dispositivos[index];
}

void MainWindow::deleteDevice(int index)
{
    if(index > dispositivos.length() || index == 0)
        return;

    qDebug() << "delete device";
    DispositivoDMX *device = dispositivos[index];
    device->deleteDevices();
    delete device;
}

