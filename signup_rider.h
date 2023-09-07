#ifndef SIGNUP_RIDER_H
#define SIGNUP_RIDER_H

#include <QWidget>
#include <QString>

namespace Ui {
class SignUp_Rider;
}

class SignUp_Rider : public QWidget
{
    Q_OBJECT

public:
    explicit SignUp_Rider(QWidget *parent = nullptr);
    ~SignUp_Rider();

    void clearInfo();
    QString getName();
    QString getUN();
    QString getP();

signals:
    void signupSignal();

private slots:
    void confirmSignup();

private:
    Ui::SignUp_Rider *ui;
    QString name;
    QString un;
    QString p;

    void getUserInput();
};

#endif // SIGNUP_RIDER_H
