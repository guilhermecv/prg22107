#ifndef CONTROLADORDMX_H
#define CONTROLADORDMX_H

#include <QObject>
#include <QTimer>
#include "InterfaceUSB.h"

#define DMX_MAX_SIZE 200
#define DMX_OUT_FREQ 30
#define DMX_MAX_FREQ 60
#define FTDI_VID 1027
#define FTDI_PID 24577
#define FTDI_BAUDRATE 250000

#define DMX_START_CODE 0x00

typedef enum
{
    noError,
    em_espera,
  executando,
    Falha_envio_buffer,
    Erro_de_interface_usb,
    Timer_nao_configurado
}error_t;


class ControladorDMX : public QObject
{
  Q_OBJECT

public:
    ControladorDMX();
    ~ControladorDMX();

    error_t getState(void);
    void setState(error_t state);

    void setUpdateFrequency(int value);
    int getUpdateFrequency(void);
    int getBufferUsage(void);

    InterfaceUSB *getSerialPort() { return usb; }

    void setChannel(int channel, char value);

    void sendFrame(unsigned char *data);

    QByteArray dmxBuffer;

public Q_SLOTS:
    void togleState(void);
    void updateControlState(bool state);
    void sendFrame() {updateValues();};
    /***** Exemplo *******/
Q_SIGNALS:
    void updateGui(bool state);
    void stateChanged();
    /*********************/

private:
    void updateValues();

    error_t _state;
    bool USBConnected;
    int _updateFrequency;

    static void handleSerialError(QSerialPort::SerialPortError error);

    unsigned char m_dmx[DMX_MAX_SIZE]; // buffer para envio dos frames

    QTimer *timer;
    InterfaceUSB *usb;
};

#endif // CONTROLADORDMX_H
