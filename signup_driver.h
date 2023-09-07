#ifndef SIGNUP_DRIVER_H
#define SIGNUP_DRIVER_H

#include <QWidget>
#include <QString>
#include <QLineEdit>
#include <QIntValidator>

namespace Ui {
class SignUp_Driver;
}

class SignUp_Driver : public QWidget
{
    Q_OBJECT

public:
    explicit SignUp_Driver(QWidget *parent = nullptr);
    ~SignUp_Driver();

    void clearInfo();
    QString getName();
    QString getUN();
    QString getP();
    QString getShipN();
    int getShipC();
    int getFee();

signals:
    void signupSignal();

private slots:
    void confirmSignup();

private:
    Ui::SignUp_Driver *ui;
    QLineEdit * scBox;
    QLineEdit * fBox;

    QString name;
    QString un;
    QString p;
    QString shipN;
    int shipC;
    int fee;

    void getUserInput();
};

#endif // SIGNUP_DRIVER_H
