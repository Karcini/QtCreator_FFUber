#include "driver.h"

Driver::Driver()
{

}
void Driver::setName(QString n)         {name = n;}
QString Driver::getname()               {return name;}

void Driver::setShipName(QString value) {shipName = value;}
void Driver::setShipCapacity(int value) {shipCapacity = value;}
void Driver::setFerryFee(int value)     {ferryFee = value;}
QString Driver::getShipName()           {return shipName;}
int Driver::getShipCapacity()           {return shipCapacity;}
int Driver::getFerryFee()               {return ferryFee;}

void Driver::resetDriver()
{
    name.clear();
    ferryFee = 0;
    shipName.clear();
    shipCapacity = 0;
}
