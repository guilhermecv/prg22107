#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>
#include "Configuracoes.h"
#include "DispositivoDMX.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    qDebug() << "MainWindow construtor";
    ui->setupUi(this);

    this->setWindowTitle("Controlador DMX");
    dmx = new ControladorDMX();
    dmx->setState(em_espera);

    updateState();

    connect(ui->aboutQt, &QAction::triggered, this, &MainWindow::aboutQt);
    connect(ui->help, &QAction::triggered, this, &MainWindow::openWiki);
    connect(ui->actionConfig, &QAction::triggered, this, &MainWindow::openConfig);

    connect(dmx, SIGNAL(stateChanged()), this, SLOT(updateState()));
    connect(ui->bDMX, SIGNAL(clicked()), dmx, SLOT(togleState()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete dmx;
}

void MainWindow::aboutQt(void)
{
    QMessageBox::aboutQt(this, tr("Sobre o Qt"));
}

/**
 * @brief Abre o repositório do projeto no navegador padrão
 */
void MainWindow::openWiki(void)
{
    QDesktopServices::openUrl(QUrl("https://github.com/guilhermecv/prg22107"));
}

/**
 * @brief abre as configurações
 */
void MainWindow::openConfig()
{
    Configuracoes config(this, dmx);
    config.exec();
}

void MainWindow::on_bAdicionar_clicked()
{
    //DispositivoDMX dmxDevice(this, dmx);
    //dmxDevice.exec();

    DispositivoDMX *_dmx = new DispositivoDMX(this, dmx);
    qDebug() << "Novo dispositivo DMX";
    _dmx->editDevice();
    qDebug() << _dmx->exec();
    qDebug() << "finish";

    ui->listWidget->addItem(_dmx->getDeviceName());
    delete _dmx;
}

void MainWindow::updateState()
{
  error_t state = dmx->getState();

  switch(state)
    {
    case executando:
      ui->bDMX->setText("Parar");
      break;

    case Erro_de_interface_usb:
      ui->bDMX->setText("Iniciar");
      ui->bDMX->setEnabled(false);
      ui->infoLabel->setText("Falha na interface USB!");
      break;

    case em_espera:
      ui->bDMX->setText("Iniciar");
      ui->bDMX->setEnabled(true);
      ui->infoLabel->setText("Controlador em espera!");
      break;

    case Falha_envio_buffer:
      ui->bDMX->setText("Iniciar");
      ui->infoLabel->setText("Falha no envio do buffer DMX!");
      break;

    default:
      break;
    }
}



