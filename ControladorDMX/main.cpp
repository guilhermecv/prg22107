#include "mainwindow.h"
#include <QApplication>
#include <QSplashScreen>
#include <QTimer>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  QApplication::setWindowIcon(QIcon(":/img/spotlight.png"));

  QSplashScreen * splashScreen = new QSplashScreen;
  splashScreen->setPixmap( QPixmap(":/img/spotlight2.png"));
  splashScreen->show();
  MainWindow w;
  
  QTimer::singleShot(3000, splashScreen, SLOT(close()));
  QTimer::singleShot(1000, &w, SLOT(show()));

  return a.exec();
}
