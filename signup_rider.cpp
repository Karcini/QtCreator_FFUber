#include "signup_rider.h"
#include "ui_signup_rider.h"

SignUp_Rider::SignUp_Rider(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SignUp_Rider)
{
    ui->setupUi(this);

    connect(ui->button_signup, SIGNAL(clicked()), this, SLOT(confirmSignup()));
}

SignUp_Rider::~SignUp_Rider()
{
    delete ui;
}

void SignUp_Rider::getUserInput()
{
    bool isValid = true;

    if(!ui->lineEdit_name->isModified())
        isValid = false;
    else if(!ui->lineEdit_userName->isModified())
        isValid = false;
    else if(!ui->lineEdit_pass->isModified())
        isValid = false;

    if(isValid)
    {
        name = ui->lineEdit_name->text();
        un = ui->lineEdit_userName->text();
        p = ui->lineEdit_pass->text();
        //save form and close
        emit signupSignal();
        this->close();
    }
    else
    {
        ui->label_status->setText("Please fill out entire form");
    }
}
void SignUp_Rider::confirmSignup()
{
    getUserInput();
}
void SignUp_Rider::clearInfo()
{
    name = ""; un= ""; p="";
}
QString SignUp_Rider::getName() {return name;}
QString SignUp_Rider::getUN() {return un;}
QString SignUp_Rider::getP() {return p;}
