#include "signup_driver.h"
#include "ui_signup_driver.h"

SignUp_Driver::SignUp_Driver(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SignUp_Driver)
{
    ui->setupUi(this);
    shipC = 0;
    fee = 0;
    scBox = ui->lineEdit_shipCap;
    fBox = ui->lineEdit_shipFee;

    scBox->setValidator( new QIntValidator(1,100,this) );
    fBox->setValidator( new QIntValidator(0,2500,this) );

    connect(ui->button_signup, SIGNAL(clicked()), this, SLOT(confirmSignup()));
}

SignUp_Driver::~SignUp_Driver()
{
    delete ui;
}

void SignUp_Driver::getUserInput()
{
    bool isValid = true;

    if(!ui->lineEdit_name->isModified())
        isValid = false;
    else if(!ui->lineEdit_userName->isModified())
        isValid = false;
    else if(!ui->lineEdit_pass->isModified())
        isValid = false;
    else if(!ui->lineEdit_shipName->isModified())
        isValid = false;
    else if(!scBox->isModified())
        isValid = false;
    else if(!fBox->isModified())
        isValid = false;

    if(isValid)
    {
        name = ui->lineEdit_name->text();
        un = ui->lineEdit_userName->text();
        p = ui->lineEdit_pass->text();
        shipN = ui->lineEdit_shipName->text();
        shipC = scBox->text().toInt();
        fee = fBox->text().toInt();
        //save form and close
        emit signupSignal();
        this->close();
    }
    else
    {
        ui->label_status->setText("Please fill out entire form");
    }
}
void SignUp_Driver::confirmSignup()
{
    getUserInput();
}
void SignUp_Driver::clearInfo()
{
    name = ""; un= ""; p="";
    shipN = ""; shipC = 0; fee = 0;
}
QString SignUp_Driver::getName() {return name;}
QString SignUp_Driver::getUN() {return un;}
QString SignUp_Driver::getP() {return p;}
QString SignUp_Driver::getShipN() {return shipN;}
int SignUp_Driver::getShipC() {return shipC;}
int SignUp_Driver::getFee() {return fee;}
