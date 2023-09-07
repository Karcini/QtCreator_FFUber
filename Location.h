#ifndef LOCATION_H
#define LOCATION_H

#include <QString>
#include <QStringList>
#include <QList>

class Location
{
public:
    Location();
    void createToDest(QString, int);
    int getTravelPriceTo(QString);
    int getPriceAtIndex(int);
    void reset();

    void setName(QString);
    QString getName();
    QStringList getDestList();
    QList<int> getPriceList();
private:
    QString name;
    QStringList toDest;
    QList<int> toDestPrice;

};

#endif // LOCATION_H
