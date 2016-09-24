#ifndef CONFIG_H
#define CONFIG_H

#include <QFile>

class Config
{

private:
    QFile fConfig;

public:
    Config();
    void init();
};

#endif // CONFIG_H
