#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "InterfaceUSB.h"
#include "ControladorDMX.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class InterfaceUSB;

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  void aboutQt(void);       // exibe as informações sobre o Qt
  void openWiki(void);      // abre o github do projeto no navegador padrão
  void openConfig(void);    // abre a interface de configurações
void ReceiveFromControl(){};

public Q_SLOTS:
  void on_bAdicionar_clicked();
  void updateState();

signals:
  void transmit_to_control();


private:
  Ui::MainWindow *ui;

  InterfaceUSB *_interfaceUSB;
  ControladorDMX *dmx;
};
#endif // MAINWINDOW_H
