#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    username = ui->lineEdit_user;
    password = ui->lineEdit_pass;

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(login()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(cancel()));

}

Login::~Login()
{
    delete ui;
}

void Login::login()
{
    qDebug() << "login attempted";

    //to call this dialog use..
    //Login loginDialog;          //create dialog
    //loginDialog.setModal(true); //modal approach to ui
    //loginDialog.exec();         //execute dialog
}

void Login::cancel()
{
    qDebug() << "login window closed";
}
