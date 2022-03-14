#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <controlador.h>
#include <dispositivoDMX.h>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void openConfig();
    void openWiki();
    void aboutQt();
    void addDevice();

    DispositivoDMX* deviceAtIndex(int index);
    void deleteDevice(int index);


private slots:
    void on_bRemover_clicked();
    void updateControlState(bool state);


signals:

private:
    Ui::MainWindow *ui;
    Controlador *dmxControl;

    QList<DispositivoDMX*> dispositivos;

    int indexSelected;
};
#endif // MAINWINDOW_H
