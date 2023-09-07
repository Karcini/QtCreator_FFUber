#include "mainwindowdriver.h"
#include "ui_mainwindowdriver.h"

MainWindowDriver::MainWindowDriver(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowDriver)
{
    ui->setupUi(this);
}

MainWindowDriver::~MainWindowDriver()
{
    delete ui;
}

void MainWindowDriver::on_button_logout_clicked()
{

}

