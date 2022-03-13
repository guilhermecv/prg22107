#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QWidget>
#include <QSlider>
#include <QLabel>
#include "dispositivoDMX.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_bAdicionar_clicked()
{
    DispositivoDMX *_dispositivoDMX = new DispositivoDMX;

    _dispositivoDMX->exec();
    /*
    if(ui->tabControl->layout() == nullptr)
    {
        qDebug() << "nullptr";
    }
    QHBoxLayout* layout = qobject_cast<QHBoxLayout*>(ui->tabControl->layout());

    qDebug() << "object cast";

    QSlider* slider = new QSlider(ui->tabControl);
    qDebug() << "Slider created " << layout->count();

    slider->setRange(0, 255);
    slider->setOrientation(Qt::Vertical);
    slider->setTickInterval(50);
    slider->setTickPosition(QSlider::TicksBothSides);
    qDebug() << "Slider configured";

    layout->insertWidget(0, slider);

    qDebug() << "Widget inserted";
    */
}


void MainWindow::on_bRemover_clicked()
{
    // Quando usado com connect, sender() passa o endereço do slider a ser removido

    // QSlider* slider = qobject_cast<QSlider*>(sender());
    // delete slider;
}

