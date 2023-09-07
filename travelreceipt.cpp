#include "travelreceipt.h"

TravelReceipt::TravelReceipt()
{

}
QString TravelReceipt::displayTripInfo()
{
    //Date of transaction
    QDate d;
    d = QDate::currentDate();
    today = d.toString("yyyy.MM.dd");

    //populate strings
    QString receipt = "Date:"+today+"\n";
    receipt += rider + "\n";
    receipt += "Driver: " + driver.getname()
            +"\nShip: "+ driver.getShipName() +"\tcapacity:"+ QString::number(driver.getShipCapacity())+"\n\n";

    int totalPrice = 0, counter = 0;
    for(int x=0; x<trips.size(); x++)
    {
        counter ++;

        //Add receipt string for trip at index
        QString t = trips[x].startDestination + "-->" + trips[x].endDestination
                + "\tPrice: " + QString::number(trips[x].price)
                + "\n";

        receipt += t;

        //running total
        totalPrice += trips[x].price;
    }
    //ferry fee
    int fee = driver.getFerryFee() * counter;
    receipt += "Driver Ship and Labor Fee\t"
            + QString::number(driver.getFerryFee()) + "g  x" +QString::number(counter) +"\n";

    //total price
    totalPrice += fee;

    //finish receipt
    receipt += "\t\tTrip Total = " + QString::number(totalPrice) + "g";
    return receipt;
}
void TravelReceipt::addTrip(Trip t)
{
    trips.append(t);
}
void TravelReceipt::printReceipt()
{
    //append receipt onto existing text file travelReceipts.txt
    QFile file("../CIS17B_Final/travelReceipts.txt");   //Original path
    //QFile file("travelReceipts.txt");                     //Absolute path

    if(!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
    {
        qDebug() << "Could not open file";
    }
    else
    {
        //Save to File
        QTextStream out(&file);
        out << displayTripInfo() << "\n------------------------------" << endl;

        //Also save transactions to database for convinience
        setTransactions();
    }
    file.close();
}
void TravelReceipt::setTransactions()
{
    for(int x=0; x<trips.size(); x++)
    {
        int tp = trips[x].price + driver.getFerryFee();
        saveTransaction(today, rider, driver.getname(), trips[x].startDestination, trips[x].endDestination,tp);
    }
    mydb.close();
}
void TravelReceipt::saveTransaction(QString date, QString riderName, QString driverName
                                    , QString startDest, QString endDest, int price)
{
    //insert data into table_transaction
    mydb = QSqlDatabase::addDatabase("QSQLITE", "transaction");
    mydb.setDatabaseName("../CIS17B_Final/mydb.db");    //Original path
    //mydb.setDatabaseName("mydb.db");                      //Absolute path

    if(!mydb.open())
    {
        qDebug() << ("Failed to open Transactions");
    }
    else
    {
        QSqlQuery qry;
        //Note: table_transaction(_date varchar(25), _riderName varchar(25),
            //_driverName varchar(25), _start varchar(25), _end varchar(25), _price integer)
        qry.prepare("INSERT INTO table_transaction(_date, _riderName, _driverName, _start, _end, _price) "
                    "VALUES (?,?,?,?,?,?) ");
        qry.bindValue(0, date);
        qry.bindValue(1, riderName);
        qry.bindValue(2, driverName);
        qry.bindValue(3, startDest);
        qry.bindValue(4, endDest);
        qry.bindValue(5, price);
        qry.exec();
    }
}

void TravelReceipt::setDriver(Driver d){driver = d;}

void TravelReceipt::resetReceipt()
{
    driver.resetDriver();
    trips.clear();
    today = "";
    //rider stays "logged in" until changed
}
