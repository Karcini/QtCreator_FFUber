#include "Location.h"

Location::Location()
{

}
void Location::createToDest(QString destination, int priceToTravelTo)
{
    toDest.append(destination);
    toDestPrice.append(priceToTravelTo);
}
//Search destination list for matching location, return price at location
int Location::getTravelPriceTo(QString location)
{
    for(int x =0; x<toDest.size(); x++)
    {
        if(toDest[x] == location)
            return toDestPrice[x];
    }
    return -1;
}
//return price using index from list of prices
int Location::getPriceAtIndex(int index)
{
    return toDestPrice.at(index);
}
void Location::reset()
{
    name.clear();
    toDest.clear();
    toDestPrice.clear();
}

void Location::setName(QString n) {name = n;}
QString Location::getName() {return name;}
QStringList Location::getDestList() {return toDest;}
QList<int> Location::getPriceList() {return toDestPrice;}
