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


void MainWindow::on_bAdicionar_clicked()
{
    auto layout = qobject_cast<QHBoxLayout*>(ui->tabControl->layout());
    DispositivoDMX *_dispositivoDMX = new DispositivoDMX(ui->tabControl, layout, dmxControl);
    _dispositivoDMX->show();
}


void MainWindow::on_bRemover_clicked()
{
    // Quando usado com connect, sender() passa o endereço do slider a ser removido

    // QSlider* slider = qobject_cast<QSlider*>(sender());
    // delete slider;
}

void MainWindow::updateControlState(bool state)
{
    if(state == true)
    {
        ui->statusbar->showMessage("Executando", 0);
        ui->bControle->setText("Parar");
    }
    else
    {
        ui->statusbar->showMessage("Em espera", 0);
        ui->bControle->setText("Iniciar");
    }
}
