#include "transactionhistory.h"
#include "ui_transactionhistory.h"

TransactionHistory::TransactionHistory(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TransactionHistory)
{
    ui->setupUi(this);
    textEdit_history = ui->textEdit_history;
    activeLogin = "Guest";//for simplicity


}

TransactionHistory::~TransactionHistory()
{
    delete ui;
}
void TransactionHistory::refreshHistory(){startDatabase();}
void TransactionHistory::startDatabase()
{
    mydb = QSqlDatabase::addDatabase("QSQLITE", "history");
    mydb.setDatabaseName("../CIS17B_Final/mydb.db");  //Original path
    //mydb.setDatabaseName("mydb.db");    //Absolute path

    if(!mydb.open())
    {
        qDebug() << ("Failed to open history database");
    }
    else
    {
        //qDebug() << "Connected to history db";
        saveTransactions();
    }
}
void TransactionHistory::saveTransactions()
{
    //Empty List (perhaps better at the end)
    transactions.clear();

    //How do we get the active login? pass info from mainwindowrider.cpp
    //QString activeLogin = "driver name";

    //Iterate through database
    QSqlQuery qry;
    int counter = 0;

    Transaction t;
    //Note: table_transaction(_date varchar(25), _riderName varchar(25),
        //_driverName varchar(25), _start varchar(25), _end varchar(25), _price integer)
    if(qry.exec("select * from table_transaction where _riderName='"+ activeLogin +"' "))
    {
        //info exists...
        while(qry.next())
        {
            t.date = qry.value(0).toString();
            t.riderName = qry.value(1).toString();
            t.driverName = qry.value(2).toString();
            t.startLocation = qry.value(3).toString();
            t.endLocation = qry.value(4).toString();
            t.price = qry.value(5).toInt();

            transactions.append(t);
            counter ++;
        }
    }
    mydb.close();

    displayTransactions(counter);
}
void TransactionHistory::displayTransactions(int size)
{
    //if info resulted empty
    if(size == 0)
    {
        QString noHistory = "No History for " + activeLogin;
        textEdit_history->setText(noHistory);
    }
    else
    {
        QString history = "History for " + activeLogin + "\n";
        history += printAllTransactions();
        textEdit_history->setText(history);
    }
}
QString TransactionHistory::printAllTransactions()
{
    QString s = "";
    for(int x=0; x<transactions.size(); x++)
    {
        s += transactions[x].printTransaction() + "\n";
    }
    return s;
}

void TransactionHistory::setActiveLogin(QString name) {activeLogin = name;}
