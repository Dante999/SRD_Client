#ifndef SERIALCOM_H
#define SERIALCOM_H

#include <QtSerialPort/QSerialPort>
#include "stdint.h"




class SerialCom : public QObject
{
    Q_OBJECT

private:

    enum receiveState
    {
        WAITFOR_SYNC,
        WAITFOR_CMD,
        WAITFOR_LENGTH,
        WAITFOR_DATA
    } state;

    struct receivePackage
    {
        uint8_t cmd;
        uint8_t length;
        char data[256];
    } received;



    QSerialPort *sPort;



    void stateMachine();

public:
    SerialCom(QString portName, qint32 baudRate = QSerialPort::Baud19200);

    void writeData(uint8_t cmd, uint8_t dataLength, const char *data);
    void open();
    void close();

signals:
    void dataReceived(serialPackage dataPackage);




private slots:
    void readData();
};

#endif // SERIALCOM_H
