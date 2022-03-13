#ifndef CONFIGURACOES_H
#define CONFIGURACOES_H

#include <QDialog>
#include <controlador.h>

namespace Ui {
class Configuracoes;
}

class Configuracoes : public QDialog
{
    Q_OBJECT

public:
    explicit Configuracoes(QWidget *parent = nullptr, Controlador *control = nullptr);
    ~Configuracoes();



public slots:
    void updateControlState(bool state);

private:
    Ui::Configuracoes *ui;
    Controlador *dmxControl;
    InterfaceUSB *_interfaceUSB;

};

#endif // CONFIGURACOES_H
