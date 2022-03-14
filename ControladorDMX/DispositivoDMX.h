#ifndef DISPOSITIVODMX_H
#define DISPOSITIVODMX_H

#include <QDialog>
#include <QWidget>
#include <QBoxLayout>
#include <QSlider>
#include <QSignalMapper>
#include <controlador.h>

#include <QGroupBox>


namespace Ui
{
    class DispositivoDMX;
}

class DispositivoDMX : public QDialog
{
    Q_OBJECT

public:
    explicit DispositivoDMX(QWidget *parent = nullptr, QHBoxLayout *layout = nullptr, Controlador *control = nullptr);
    ~DispositivoDMX();

    bool DeviceValid;

    QString getDeviceName() { return DeviceName; };

    void deleteDevices();

private slots:
    void on_nameInput_textChanged(const QString &arg1);

    void on_buttonBox_accepted();

    void sliderValueChanged();
    void channelUpdate(int ch);

    void on_comboBoxMode_currentIndexChanged(int index);

private:
    Ui::DispositivoDMX *ui;
    QWidget *deviceWidget;
    QHBoxLayout *deviceLayout;
    QGroupBox *groupBox;

    QString DeviceName;
    QSlider *slider[8];
    QSignalMapper *signalMapper;
    Controlador *dmxControl;

    int channels;
    int address;
    int mode;

    int selectedChannel;

    void checkConfig();
    void addDevice();
};

#endif // DISPOSITIVODMX_H
