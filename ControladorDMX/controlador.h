#ifndef CONTROLADOR_H
#define CONTROLADOR_H

#include <QObject>
#include <QTimer>
#include "interfaceUSB.h"

#define DMX_MAX_SIZE                15
#define DMX_MAX_OUTPUT_FREQUENCY    30
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
    int getBufferUsage(void);

    void setChannel(int channel, int value);
    InterfaceUSB *getSerialPort() { return usb; }

signals:
    void stateChanged(bool state);

public slots:
    void clearBuffer(void);
    void printBuffer(void);
    void setUpdateFrequency(int freq);
    void toggleRunningState();

private:
    InterfaceUSB *usb;
    QTimer *timer;

    int updateFrequency;
    bool usbConnected;

    bool controlState;

    int dmxBuffer[DMX_MAX_SIZE];    // buffer para os frames DMX
    QByteArray m_dmxBuffer;         // buffer para os frames DMX utilizando QByteArray
};

#endif // CONTROLADOR_H
