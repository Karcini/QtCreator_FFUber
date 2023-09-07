#include "destinationsdb.h"

DestinationsDB::DestinationsDB()
{
    //When database is first initiated
    startDatabase();
}
void DestinationsDB::startDatabase()
{
    mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("../CIS17B_Final/mydb.db");    //Original path
    //mydb.setDatabaseName("mydb.db");                      //Absolute path
    if(!mydb.open())
    {
        qDebug() << ("Failed to open database");
    }
    else
    {
        qDebug() << "Connected!";

        //populate lists
        fillLocations();
        fillDrivers();

        //close database no longer necessary because we open different connections
        //mydb.close();
    }
}
void DestinationsDB::fillLocations()
{
    //make sure list is empty
    destinations.clear();

    //Iterate through database and fill location information onto this database Object
    //qDebug() << "Filling Locations...";
    QSqlQuery qryName, qryTravel;
    int counter = 1;

    Location location;
    //Note: table_destinations(name varchar(20), price integer, path varchar(3), parentid integer)
    if(qryName.exec("select * from table_destinations where parentid=0"))
    {
        //info exists...
        while(qryName.next())
        {
            //Location location;
            location.reset();
            location.setName(qryName.value(0).toString());
            //QString n = qryName.value(0).toString(); //name

            QString dest; int price;
            if(qryTravel.exec("select * from table_destinations where parentid='"+QString::number(counter)+"'"))
            {
                //info exits...
                while(qryTravel.next())
                {
                    dest = qryTravel.value(0).toString(); //name
                    price = qryTravel.value(1).toInt(); //price
                    location.createToDest(dest, price);
                }
            }
            counter ++;
            destinations.append(location);
        }
    }
    //showDestinations();
}
int DestinationsDB::getTripPrice(QString start, QString end)
{
    for(int x=0; x<destinations.size(); x++)
    {
        if(destinations[x].getName() == start)
        {
            int tripPrice = destinations[x].getTravelPriceTo(end);
            //qDebug() << "Trip price in destinations db = " << tripPrice;
            return tripPrice;
        }
    }
    return 0;
}
//This function runs twice on startup because of mainwindowrider.cpp onUserlogin(), but it causes no issues
void DestinationsDB::fillDrivers()
{
    //make sure list is empty
    drivers.clear();

    //Iterate through database and fill driver information onto this database Object
    //qDebug() << "Filling Drivers...";
    QSqlQuery qry;

    //Note: table_destinations(name varchar(20), price integer, path varchar(3), parentid integer)
    if(qry.exec("select * from table_drivers"))
    {
        //info exists...
        while(qry.next())
        {
            Driver d;
            d.setName(qry.value(0).toString());
            d.setShipName(qry.value(3).toString());
            d.setShipCapacity(qry.value(4).toInt());
            d.setFerryFee(qry.value(5).toInt());
            drivers.append(d);
        }
    }
    //showDrivers();
}
Driver DestinationsDB::getDriver(QString name)
{
    Driver d;
    for(int x=0; x<drivers.size(); x++)
    {
        if(drivers[x].getname() == name)
        {
            d = drivers[x];
            return d;
        }
    }
    return d;
}



//Unused Test Functions
void DestinationsDB::showDestinations()
{
    for(int x=0; x<destinations.size(); x++)
    {
        qDebug() << destinations[x].getName() << "-------------";
        qDebug() << destinations[x].getDestList();
        qDebug() << destinations[x].getPriceList();
    }
}
void DestinationsDB::showDrivers()
{
    for(int x=0; x<drivers.size(); x++)
    {
        qDebug() << drivers[x].getname() << "-------------";
        qDebug() << "Ship: " << drivers[x].getShipName()
                 << "\tCapacity: " << QString::number(drivers[x].getShipCapacity() );
        qDebug() << "Ferry Fee: " << QString::number(drivers[x].getFerryFee() );
    }
}
