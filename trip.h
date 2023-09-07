#ifndef TRIP_H
#define TRIP_H

#include <QString>

class Trip
{
public:
    Trip(QString, QString, int);

    QString startDestination;
    QString endDestination;
    int price;
};

#endif // TRIP_H
