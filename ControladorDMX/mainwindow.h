#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <controlador.h>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_bAdicionar_clicked();

    void on_bRemover_clicked();

private:
    Ui::MainWindow *ui;

    Controlador *dmxControl;
};
#endif // MAINWINDOW_H
