#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>
#include "Configuracoes.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
  qDebug() << "MainWindow construtor";
  ui->setupUi(this);

  this->setWindowTitle("Controlador DMX");

  connect(ui->aboutQt, &QAction::triggered, this, &MainWindow::aboutQt);
  connect(ui->help, &QAction::triggered, this, &MainWindow::openWiki);
  connect(ui->actionConfig, &QAction::triggered, this, &MainWindow::openConfig);

  _interfaceUSB = new InterfaceUSB();
  dmx = new ControladorDMX();

  QString portName = _interfaceUSB->findPort(FTDI_VID, FTDI_PID);
  ui->info->append(portName);
  ui->info->append(_interfaceUSB->getDeviceInfo(portName));
  if(_interfaceUSB->connect(portName))
    {
      ui->info->append("Dispositivo iniciado corretamente");
    }
  else
    {
      ui->info->append("Falha na conexao com o dispositivo USB");
    }
}

MainWindow::~MainWindow()
{
  qDebug() << "MainWindow destrutor";
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

void MainWindow::openConfig()
{
  Configuracoes config(this, dmx);
  config.exec();
}
