#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  this->setWindowTitle("Controlador DMX");

  connect(ui->aboutQt, &QAction::triggered, this, &MainWindow::aboutQt);
  connect(ui->help, &QAction::triggered, this, &MainWindow::openWiki);
  
  interfaceUSB = new InterfaceUSB();


  ui->info->append(interfaceUSB->getDeviceInfo());
}

MainWindow::~MainWindow()
{
  delete ui;
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
