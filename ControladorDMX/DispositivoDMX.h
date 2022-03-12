#ifndef DISPOSITIVODMX_H
#define DISPOSITIVODMX_H

#include <QDialog>
#include "ControladorDMX.h"

namespace Ui {
class DispositivoDMX;
}

class DispositivoDMX : public QDialog
{
    Q_OBJECT

public:
    explicit DispositivoDMX(QWidget *parent = nullptr, ControladorDMX *dmxControl = nullptr);
    ~DispositivoDMX();

    QString getDeviceName() {return DeviceName;};

    void editDevice();
    bool isDeviceValid();
    
private slots:
    void on_name_edit_editingFinished();

private:
    Ui::DispositivoDMX *ui;

    QString DeviceName;         // nome do dispositivo
    quint32 DeviceAddress;      // endereço do dispositivo no barramento

};

#endif // DISPOSITIVODMX_H
