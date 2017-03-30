#include "srdclient.h"
#include <QDebug>
#include <QMessageBox>

SrdClient::SrdClient()
{
   memset(&m_gameData, 0, sizeof(m_gameData));
   m_config = Config::getInstance();
}



void SrdClient::start()
{
   m_serialCom = new SerialCom(m_config->getValue(CFG_SERIALPORT), 19200);   

   if(m_serialCom->open(QIODevice::ReadWrite))
   {
      connect(m_serialCom, SIGNAL(parsingComplete(serialPackage)), this, SLOT(executeCommand(serialPackage)));
      m_dashboard = new Dashboard(&m_gameData);

      if(m_config->getValue(CFG_FULLSCREEN) == "1")
      {
          m_dashboard->showFullScreen();
          qDebug() << "open in fullscreen";
      }
      else
      {
          m_dashboard->resize(1024,600);
          m_dashboard->show();
          qDebug() << "open in 1024x600";
      }
   }
   else
   {
      QMessageBox msgBox;
      msgBox.setIcon(QMessageBox::Critical);
      msgBox.setText("Can't open SerialPort!");

      QString infoText = "";
      infoText += tr("the port '%1' is maybe busy.\n\n").arg(m_serialCom->portName());
      infoText += tr("The programm will close now!");

      msgBox.setInformativeText(infoText);
      msgBox.exec();

      exit(EXIT_FAILURE);
   }



}

void SrdClient::executeCommand(serialPackage serialData)
{
   static int counter = 0;

   counter ++;
   counter %= 1000;

   qDebug() << "data" << counter;


   switch(serialData.cmd)
   {
      case CMD_REQUEST:
         m_serialCom->writeData(CMD_ACKNOWLEDGE, 1, "A");
         break;

      case CMD_GAMEDATA:
         if(serialData.length == sizeof(m_gameData))
         {
            memcpy(&m_gameData, &serialData.data, sizeof(m_gameData));
            //m_serialCom->writeData(CMD_ACKNOWLEDGE, 1, "A");
         }
         else
         {
            qDebug() << "Error datalength!!";
            m_serialCom->writeData(CMD_ERR_GAMEDATA_SIZE, 1, "E");
         }

         break;

      default:
         // nothing to do
         break;

   }

   m_dashboard->update();
}
