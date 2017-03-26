#include "serialcom.h"


/*******************************************************************************
 * @brief   constructor
 *
 * configures the ComPort with settings like the portName, baudRate and parity.
 *
 * @param   portName    name of the ComPort (e.g., "COM1")
 * @param   baudRate    Baudrate of the ComPort (e.g., 9600)
 *
 * @return  none
 *
*******************************************************************************/
SerialCom::SerialCom(QString portName, qint32 baudRate)
{
    m_state = WAITFOR_SYNC;

    QSerialPort::setPortName(portName);
    QSerialPort::setBaudRate(baudRate);
    QSerialPort::setDataBits(QSerialPort::Data8);
    QSerialPort::setParity(QSerialPort::NoParity);
    QSerialPort::setStopBits(QSerialPort::OneStop);
    QSerialPort::setFlowControl(QSerialPort::NoFlowControl);

    connect(this, SIGNAL(readyRead()), this, SLOT(parseAllReceivedBytes()));
}


/*******************************************************************************
 * @brief   writes formatted data to the ComPort
 *
 * @param   cmd         command-byte
 * @param   dataLength  length-byte (number of bytes of the payload)
 * @param   *data       payload
 *
 * @return  none
 *
*******************************************************************************/
void SerialCom::writeData(uint8_t cmd, uint8_t dataLength, const char *data)
{
    QByteArray syncByte(1, SYNC_BYTE);
    QByteArray cmdByte(1, cmd);
    QByteArray lengthByte(1, dataLength);    

    QSerialPort::write(syncByte);
    QSerialPort::write(cmdByte);
    QSerialPort::write(lengthByte);
    QSerialPort::write(data, dataLength);
}


/*******************************************************************************
 * @brief   parses all received bytes from the input buffer
 *
 * @param   none
 *
 * @return  none
 *
*******************************************************************************/
void SerialCom::parseAllReceivedBytes()
{
    char byte = 0;

    while(QSerialPort::bytesAvailable() > 0)
    {
        QSerialPort::read((char*)&byte, 1);
        parseSingleByte(byte);
    }
}


void SerialCom::parseSingleByte(char byte)
{
    static uint8_t iterator = 0;

    switch(m_state)
    {
        case WAITFOR_SYNC:

            if( byte == SYNC_BYTE )
            {
                iterator = 0;
                m_state = WAITFOR_CMD;
            }
            break;

        case WAITFOR_CMD:
            m_received.cmd = byte;
            m_state = WAITFOR_LENGTH;
            break;

        case WAITFOR_LENGTH:
                m_received.length = byte;
                m_state = WAITFOR_DATA;
            break;

        case WAITFOR_DATA:

                if(iterator < m_received.length)
                {
                    m_received.data[iterator] = byte;
                    iterator++;
                }

                if(iterator >= m_received.length)
                {
                    m_state = WAITFOR_SYNC;
                    iterator = 0;

                    emit parsingComplete(m_received);
                }

            break;
    }
}





