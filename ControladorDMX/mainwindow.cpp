#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QWidget>
#include <QSlider>
#include <QLabel>
#include <QListWidgetItem>

#include "dispositivoDMX.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->statusbar->showMessage("Iniciando...", 2000);

    dmxControl = new Controlador;
}

MainWindow::~MainWindow()
{
    delete ui;
    delete dmxControl;
}

void MainWindow::on_bAdicionar_clicked()
{
    auto layout = qobject_cast<QHBoxLayout*>(ui->tabControl->layout());
    DispositivoDMX *_dispositivoDMX = new DispositivoDMX(ui->tabControl, layout);
    _dispositivoDMX->exec();
}


void MainWindow::on_bRemover_clicked()
{
    // Quando usado com connect, sender() passa o endereço do slider a ser removido

    // QSlider* slider = qobject_cast<QSlider*>(sender());
    // delete slider;
}

