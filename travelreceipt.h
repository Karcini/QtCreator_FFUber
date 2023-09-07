#ifndef TRAVELRECEIPT_H
#define TRAVELRECEIPT_H

#include <QList>
#include <QFile>
#include <QTextStream>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QDate>
#include "trip.h"
#include "driver.h"

class TravelReceipt
{
public:
    TravelReceipt();
    QString displayTripInfo();
    void addTrip(Trip);
    void printReceipt();

    void setDriver(Driver);
    void resetReceipt();

    //public for simplicity
    QString today;
    QString rider;
    Driver driver;
    QList<Trip> trips;

private:
    QSqlDatabase mydb;
    void setTransactions();
    void saveTransaction(QString, QString, QString, QString, QString, int);
};

#endif // TRAVELRECEIPT_H
