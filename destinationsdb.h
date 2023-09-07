#ifndef DESTINATIONSDB_H
#define DESTINATIONSDB_H

#include <QList>
//#include <QtSql> //why did I insert this?
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtDebug>
#include "Location.h"
#include "driver.h"

//This class got repurposed for copying memory from database
//I did not rename it because I always encounter issues when renaming a class with multiple uses in code
class DestinationsDB
{
public:
    DestinationsDB();
    QList<Location> destinations;
    QList<Driver> drivers;
    void fillDrivers();
    int getTripPrice(QString, QString);
    Driver getDriver(QString);

private:
    QSqlDatabase mydb;
    void startDatabase();
    void fillLocations();
    //void fillDrivers();

    //unused test functions
    void showDestinations();
    void showDrivers();

};

#endif // DESTINATIONSDB_H
