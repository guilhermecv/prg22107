#ifndef CONTROLADOR_H
#define CONTROLADOR_H

#include <QObject>
#include <QTimer>
#include "interfaceUSB.h"

#define DMX_MAX_SIZE                512
#define DMX_MAX_OUTPUT_FREQUENCY    50
#define DMX_START_CODE              0x00

#define FTDI_VID                    1027
#define FTDI_PID                    24577
#define FTDI_BAUDRATE               250000

class Controlador : public QObject
{
    Q_OBJECT
public:
    explicit Controlador(QObject *parent = nullptr);

    bool getState(void);
    void setState(bool state);

    int getUpdateFrequency(void) {return updateFrequency;};
    int getBufferSize(void);

    void setChannel(int channel, int value);
    InterfaceUSB *getSerialPort() { return usb; }

signals:
    void stateChanged(bool state);
    void interfaceError();

public slots:
    void clearBuffer(void);
    void printBuffer(void);
    void setUpdateFrequency(int freq);
    void toggleRunningState();
    void writeFrame();

private:
    InterfaceUSB *usb;
    QTimer *timer;

    int updateFrequency;
    bool usbConnected;

    bool controlState;

    void timerAction();
    void handleInterfaceError();

    unsigned char dmxBuffer[DMX_MAX_SIZE];
};

#endif // CONTROLADOR_H
