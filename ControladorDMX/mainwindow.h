#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "InterfaceUSB.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  void aboutQt(void);   // exibe as informações sobre o Qt
  void openWiki(void);  // abre o github do projeto no navegador padrão


private:
  Ui::MainWindow *ui;

  InterfaceUSB *interfaceUSB;
};
#endif // MAINWINDOW_H
