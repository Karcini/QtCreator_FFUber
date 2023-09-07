#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QStringList>
#include <QLineEdit>
#include <QDebug>

namespace Ui {  class Login;}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

private:
    Ui::Login * ui;
    QLineEdit * username;
    QLineEdit * password;

private slots:
    void login();
    void cancel();
};

#endif // LOGIN_H
