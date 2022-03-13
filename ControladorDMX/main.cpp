#include "mainwindow.h"
#include <QApplication>
#include <QSplashScreen>
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QSplashScreen *splashScreen = new QSplashScreen;
    MainWindow window;

    splashScreen->setPixmap( QPixmap(":/spotlight.png"));
    splashScreen->show();

    QTimer::singleShot(1000, splashScreen, SLOT(close()));
    QTimer::singleShot(1000, &window, SLOT(show()));
    return app.exec();
}
