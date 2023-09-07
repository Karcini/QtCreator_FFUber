#ifndef DRIVER_H
#define DRIVER_H

#include <QString>
//#include <QSqlDatabase>

class Driver
{
public:
    Driver();

    void setName(QString);
    QString getname();

    void setFerryFee(int);
    void setShipName(QString);
    void setShipCapacity(int);
    int getFerryFee();
    QString getShipName();
    int getShipCapacity();

    void resetDriver();

private:
    QString name;

    QString shipName;
    int shipCapacity;
    int ferryFee;
};

#endif // DRIVER_H
