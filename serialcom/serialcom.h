#ifndef SERIALCOM_H
#define SERIALCOM_H

#include <QtSerialPort/QSerialPort>
#include "stdint.h"



#define SYNC_BYTE       0x00



typedef struct
{
    uint8_t cmd;
    uint8_t length;
    char data[256];
} serialPackage;

enum serialCommands
{
    CMD_REQUEST = 1,
    CMD_ACK,
    CMD_GAMEDATA,
};



class SerialCom : public QSerialPort
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

    void stateMachine();

public:

    SerialCom(QString portName, qint32 baudRate = QSerialPort::Baud19200);

    void writeData(serialCommands cmd, uint8_t dataLength, const char *data);
    void writeCommand(serialCommands cmd);
    void open();
    void close();

signals:
    void dataReceived(serialPackage dataPackage);

private slots:
    void readData();
};

#endif // SERIALCOM_H
