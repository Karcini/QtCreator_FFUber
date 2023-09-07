#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include <QDebug>
#include <QLineEdit>
#include <QComboBox>
#include <QLabel>
#include <QSqlDatabase> //for logging in
#include <QSqlQuery>
#include "signup_rider.h"
#include "signup_driver.h"

QT_BEGIN_NAMESPACE
namespace Ui {  class LoginWindow;}
QT_END_NAMESPACE

class LoginWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();
    QString currentLogin; //QString Class since our rider info is just a name

signals:
    void loginSignal();

private slots:
    void login();
    void signup();
    void userTypeChange();
    void createNewRider();
    void createNewDriver();

private:
    Ui::LoginWindow *ui;
    QLineEdit * usernameBox;
    QLineEdit * passwordBox;
    int userType;
    QLabel * statusLabel;
    SignUp_Driver * driverSignup;
    SignUp_Rider * riderSignup;
    QSqlDatabase mydb;

    void startDatabase();
};

#endif // LOGINWINDOW_H
