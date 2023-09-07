#ifndef DESTINATION_H
#define DESTINATION_H

#include <QString>
#include <QStringList>
#include <QList>

class Location
{
public:
    Location();
    int getTravelPrice(QString);
    QString getName();

private:
    QString name;
    QStringList toDest;
    QList<int> toDestPrice;
    void createToDest(QString, int);
};

void Location::createToDest(QString destination, int priceToTravelTo)
{
    toDest.append(destination);
    toDestPrice.append(priceToTravelTo);
}
int Location::getTravelPrice(QString location)
{
    for(int x =0; x<toDest.size(); x++)
    {
        if(toDest[x] == location)
            return toDestPrice[x];
    }
    return -1;
}
QString Location::getName() {return name;}


#endif // DESTINATION_H
