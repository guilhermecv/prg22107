#ifndef CONTROLADOR_H
#define CONTROLADOR_H

#include <QObject>
#include <QTimer>
#include <interfaceUSB.h>

#define DMX_MAX_SIZE                200
#define DMX_MAX_OUTPUT_FREQUENCY    30
#define DMX_START_CODE              0x00


class Controlador : public QObject
{
    Q_OBJECT
public:
    explicit Controlador(QObject *parent = nullptr);

    void setUpdateFrequency(int freq);
    int getUpdateFrequency(void) {return updateFrequency;};
    int getBufferUsage(void);

    void setChannel(int channel, char value);
    InterfaceUSB *getUSBPort() {return usb;};

signals:
    void stateChanged();

public slots:

private:
    InterfaceUSB *usb;
    QTimer *timer;

    int updateFrequency;
};

#endif // CONTROLADOR_H
