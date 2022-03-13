#ifndef DISPOSITIVODMX_H
#define DISPOSITIVODMX_H

#include <QDialog>

namespace Ui {
class DispositivoDMX;
}

class DispositivoDMX : public QDialog
{
    Q_OBJECT

public:
    explicit DispositivoDMX(QWidget *parent = nullptr);
    ~DispositivoDMX();

    bool DeviceValid;

    QString getDeviceName() {return DeviceName;};

private slots:
    void on_nameInput_textChanged(const QString &arg1);
    void on_comboBoxMode_highlighted(int index);
    void on_addressInput_valueChanged(int arg1);

private:
    Ui::DispositivoDMX *ui;

    QString DeviceName;
    int channels;
    int address;
};

#endif // DISPOSITIVODMX_H
