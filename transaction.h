#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QString>

class Transaction
{
public:
    Transaction();

    QString date;
    QString riderName;
    QString driverName;
    QString startLocation;
    QString endLocation;
    int price;

    QString printTransaction();
};

#endif // TRANSACTION_H
