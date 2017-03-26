#ifndef SERIALCOM_H
#define SERIALCOM_H


#include <QtSerialPort/QSerialPort>
#include "stdint.h"

#define SYNC_BYTE       0x00
#define CMD_REQUEST             10
#define CMD_ACKNOWLEDGE         11
#define CMD_GAMEDATA            20
#define CMD_SETTINGS            30
#define CMD_ERR_GAMEDATA_SIZE   40

typedef struct
{
    uint8_t cmd;
    uint8_t length;
    char data[256];
} serialPackage;


class SerialCom : public QSerialPort
{
    Q_OBJECT

private:

    enum parseState
    {
        WAITFOR_SYNC,
        WAITFOR_CMD,
        WAITFOR_LENGTH,
        WAITFOR_DATA
    };

    parseState m_state;
    serialPackage m_received;

    void parseSingleByte(char byte);

public:

    SerialCom(QString portName, qint32 baudRate = QSerialPort::Baud19200);
    void writeData(uint8_t cmd, uint8_t dataLength, const char *data);

signals:
    void parsingComplete(serialPackage dataPackage);

private slots:
    void parseAllReceivedBytes();

};

#endif // SERIALCOM_H
