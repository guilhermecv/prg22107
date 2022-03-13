#include "controlador.h"
#include <QDebug>


Controlador::Controlador(QObject *parent)
    : QObject{parent}
{

}

void Controlador::setUpdateFrequency(int freq)
{
    updateFrequency = freq;
}

void Controlador::setChannel(int channel, char value)
{
    qDebug() << "Channel " << channel << " changed to " << value;
}
