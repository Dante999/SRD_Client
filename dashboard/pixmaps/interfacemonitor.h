#ifndef INTERFACEMONITOR_H
#define INTERFACEMONITOR_H


class InterfaceMonitor
{

private:
    virtual void drawLabels() = 0;
    virtual void drawValues() = 0;

public:
    virtual void refresh() = 0;

};

#endif // INTERFACEMONITOR_H
