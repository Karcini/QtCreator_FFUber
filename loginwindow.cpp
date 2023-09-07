#include "loginwindow.h"
#include "ui_loginwindow.h"

LoginWindow::LoginWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWindow)
{
    //Initialize
    ui->setupUi(this);
    usernameBox = ui->lineEdit_user;
    passwordBox = ui->lineEdit_pass;
    userType = ui->comboBox->currentIndex();
    statusLabel = ui->label_status;
    riderSignup = new SignUp_Rider();
    driverSignup = new SignUp_Driver();

    startDatabase();
    currentLogin = "Guest";

    connect(ui->button_login, SIGNAL(clicked()), this, SLOT(login()));
    connect(ui->button_signup, SIGNAL(clicked()), this, SLOT(signup()));
    connect(ui->comboBox, SIGNAL(activated(int)), this, SLOT(userTypeChange()));

    connect(riderSignup, SIGNAL(signupSignal()), this, SLOT(createNewRider()));
    connect(driverSignup, SIGNAL(signupSignal()), this, SLOT(createNewDriver()));
}
LoginWindow::~LoginWindow()
{
    delete ui;
    mydb.close();
}
void LoginWindow::startDatabase()
{
    //Login will have a constant connection until window is closed
    mydb = QSqlDatabase::addDatabase("QSQLITE", "login");
    mydb.setDatabaseName("../CIS17B_Final/mydb.db");      //Original path
    //mydb.setDatabaseName("mydb.db");                        //Absolute path
    if(!mydb.open())
    {
        qDebug() << ("Failed to open Logins database");
    }
    else
    {
        //qDebug() << "Connected to Logins!";
    }
}
void LoginWindow::userTypeChange()
{
    userType = ui->comboBox->currentIndex();
    //-1 unselected, 0 rider, 1 driver
}
void LoginWindow::login()
{
    if(userType <0)
        qDebug() << "Please Select Rider or Driver";
    else if(userType == 0)
    {
        QString username, password, name;
        username = ui->lineEdit_user->text();
        password = ui->lineEdit_pass->text();
        //qDebug()<<username << "   " << password;

        //check if database is still open
        if(!mydb.open())
        {
            //not open
            qDebug()<<"Failed to open database";
            return;
        }
        else
        {
            QSqlQuery qry;
            //Note: table_riders(name, login_un, login_p)
            if(qry.exec("select * from table_riders where login_un='"+username+"' and login_p='"+password+"' ") )
            {
                //info exists
                while(qry.next())
                {
                    //create rider object, populate data, return rider object
                    //but since all rider is, is a QString, we will simply get the name of rider
                    name = qry.value(0).toString();
                    currentLogin = name;

                    emit loginSignal();
                    this->close();
                }
            }
            else
            {
                qDebug() << "Login information was not found.";
            }
        }
    }
    else if(userType == 1)
    {
        qDebug() << "There is no login functionality for drivers at this time.";
    }
}
void LoginWindow::signup()
{
    if(userType <0)
        qDebug() << "Select Rider or Driver";
    else if(userType == 0)
    {
        qDebug() << "Rider Sign up";
        riderSignup->show();
    }
    else if(userType == 1)
    {
        qDebug() << "Driver Sign up";
        driverSignup->show();
    }
}
void LoginWindow::createNewRider()
{
    qDebug() << "New Rider Created";

    //insert data into table_riders
    mydb = QSqlDatabase::addDatabase("QSQLITE", "signup_rider");
    mydb.setDatabaseName("../CIS17B_Final/mydb.db");    //Original path
    //mydb.setDatabaseName("mydb.db");                    //Absolute path

    if(!mydb.open())
    {
        qDebug() << ("Failed to open signup_rider");
    }
    else
    {
        QSqlQuery qry;
        //Note: table_riders(name varchar(25), login_un varchar(25), login_p varchar(25) )
        qry.prepare("INSERT INTO table_riders(name, login_un, login_p) "
                    "VALUES (?,?,?) ");
        qry.bindValue(0, riderSignup->getName());
        qry.bindValue(1, riderSignup->getUN());
        qry.bindValue(2, riderSignup->getP());
        if(!qry.exec())
            qDebug() << "Could not successfully save Rider Information";
    }
    mydb.close();

    emit loginSignal(); //bad naming convention, sorry
    riderSignup->clearInfo(); //protect sensitive information
}
void LoginWindow::createNewDriver()
{
    qDebug() << "New Driver Created";

    //insert data into table_drivers
    mydb = QSqlDatabase::addDatabase("QSQLITE", "signup_driver");
    mydb.setDatabaseName("../CIS17B_Final/mydb.db");    //Original path
    //mydb.setDatabaseName("mydb.db");                    //Absolute path

    if(!mydb.open())
    {
        qDebug() << ("Failed to open signup_driver");
    }
    else
    {
        QSqlQuery qry;
        //Note: table_drivers(name varchar(25), login_un varchar(25), login_p varchar(25)
                //shipName varchar(25), shipCapacity integer, ferryFee integer)
        qry.prepare("INSERT INTO table_drivers(name, login_un, login_p, shipName, shipCapacity, ferryFee) "
                    "VALUES (?,?,?,?,?,?) ");
        qry.bindValue(0, driverSignup->getName());
        qry.bindValue(1, driverSignup->getUN());
        qry.bindValue(2, driverSignup->getP());
        qry.bindValue(3, driverSignup->getShipN());
        qry.bindValue(4, driverSignup->getShipC());
        qry.bindValue(5, driverSignup->getFee());
        if(!qry.exec())
            qDebug() << "Could not successfully save Driver Information";
    }
    mydb.close();

    emit loginSignal(); //bad naming convention, sorry
    driverSignup->clearInfo(); //protect sensitive information
}
