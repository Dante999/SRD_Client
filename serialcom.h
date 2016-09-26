#ifndef SERIALCOM_H
#define SERIALCOM_H

#include <QtSerialPort/QSerialPort>
#include "stdint.h"



#define SYNC_BYTE       0xF0
#define CMD_REQUEST     0x01
#define CMD_ACK         0x02
#define CMD_READY       0x03
#define CMD_GAMEDATA    0x0A










typedef struct
{
    uint8_t cmd;
    uint8_t length;
    char data[256];
} serialPackage;



class SerialCom : public QObject
{
    Q_OBJECT

private:

    enum serialState
    {
        WAITFOR_SYNC,
        WAITFOR_CMD,
        WAITFOR_LENGTH,
        WAITFOR_DATA
    } state;



    serialPackage received;



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
