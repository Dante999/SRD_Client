#ifndef SRDCLIENT_H
#define SRDCLIENT_H

#include "QObject"
#include "config.h"


class SrdClient : public QObject
{
    Q_OBJECT

private:
    Config m_config;

public:
    SrdClient();
};

#endif // SRDCLIENT_H
