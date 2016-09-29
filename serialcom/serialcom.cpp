#include "serialcom.h"
#include <QDebug>



#define HEADER "serialPort - "


SerialCom::SerialCom(QString portName, qint32 baudRate)
{
    qDebug() << HEADER << "creating: " << portName;
    qDebug() << HEADER << "baudrate: " << baudRate;

    QSerialPort::setPortName(portName);
    QSerialPort::setBaudRate(baudRate);
    QSerialPort::setDataBits(QSerialPort::Data8);
    QSerialPort::setParity(QSerialPort::NoParity);
    QSerialPort::setStopBits(QSerialPort::OneStop);
    QSerialPort::setFlowControl(QSerialPort::NoFlowControl);

    state = WAITFOR_SYNC;

    connect(this, SIGNAL(readyRead()), this, SLOT(readData()));
}



void SerialCom::writeData(serialCommands cmd, uint8_t dataLength, const char *data)
{
    QByteArray syncByte(1, SYNC_BYTE);
    QByteArray cmdByte(1, cmd);
    QByteArray lengthByte(1, dataLength);    

    QSerialPort::write(syncByte);
    QSerialPort::write(cmdByte);
    QSerialPort::write(lengthByte);
    QSerialPort::write(data, dataLength);
}

void SerialCom::writeCommand(serialCommands cmd)
{
    this->writeData(cmd, 0, "");
}

void SerialCom::open()
{

    qDebug() << HEADER << "trying to open...";


    try
    {        
        if(QSerialPort::isOpen())    throw (QString)"Port is already open";

        if(QSerialPort::open(QIODevice::ReadWrite) == true)
        {
            qDebug() << HEADER << "opening succesfull";
        }
        else
        {
            throw (QString)"unable to open";
        }
    }

    catch(QString msg)
    {
        qDebug() << "[E] " << msg;
    }


}

void SerialCom::close()
{
    qDebug() << HEADER << "trying to close...";


    try
    {
        if(this->isOpen() == false)
        {
            throw (QString)"Port is already closed";
        }
        else
        {
            QSerialPort::close();

            qDebug() << HEADER << "closing succesfull";
        }
    }
    catch(QString msg)
    {
        qDebug() << "[E] " << HEADER << msg;
    }
}





void SerialCom::readData()
{

    qDebug() << "reading serialPort...";

    while(QSerialPort::bytesAvailable() > 0)
    {
        stateMachine();
    }

    qDebug() << "finished";
}



void SerialCom::stateMachine()
{
    static uint8_t iterator = 0;

    switch(state)
    {
        case WAITFOR_SYNC:
                    uint8_t byte;
                    QSerialPort::read((char*)&byte, 1);

                    if( byte == SYNC_BYTE )
                    {
                        iterator = 0;
                        state = WAITFOR_CMD;
                    }
                    else
                    {
                        qDebug() << "Missing sync byte";
                    }

            break;

        case WAITFOR_CMD:
                QSerialPort::read((char*)&received.cmd, 1);
                state = WAITFOR_LENGTH;
            break;

        case WAITFOR_LENGTH:
                QSerialPort::read((char*)&received.length, 1);
                state = WAITFOR_DATA;
            break;

        case WAITFOR_DATA:

                if(iterator < received.length)
                {
                    QSerialPort::read((char*)&received.data[iterator], 1);
                    iterator++;
                }

                if(iterator >= received.length)
                {
                    state = WAITFOR_SYNC;
                    iterator = 0;

                    qDebug() << HEADER << "incoming data complete";

                    emit dataReceived(received);                    
                }

            break;
    }
}





