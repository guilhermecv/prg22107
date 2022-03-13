#ifndef DISPOSITIVODMX_H
#define DISPOSITIVODMX_H

#include <QDialog>
#include <QWidget>
#include <QBoxLayout>
#include <QSlider>
#include <QSignalMapper>

namespace Ui
{
    class DispositivoDMX;
}

class DispositivoDMX : public QDialog
{
    Q_OBJECT

public:
    explicit DispositivoDMX(QWidget *parent = nullptr, QHBoxLayout *layout = nullptr);
    ~DispositivoDMX();

    bool DeviceValid;

    QString getDeviceName() { return DeviceName; };

private slots:
    void on_nameInput_textChanged(const QString &arg1);
    void on_comboBoxMode_highlighted(int index);
    void on_addressInput_valueChanged(int arg1);

    void on_buttonBox_accepted();

    void sliderValueChanged();
    void channelUpdate(int ch);

private:
    Ui::DispositivoDMX *ui;
    QWidget *deviceWidget;
    QHBoxLayout *deviceLayout;

    QString DeviceName;
    QSlider *slider[8];
    QSignalMapper *signalMapper;

    int channels;
    int address;
    int mode;

    int selectedChannel;

    void checkConfig();
    void addDevice();
};

#endif // DISPOSITIVODMX_H
