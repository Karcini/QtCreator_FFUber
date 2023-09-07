#ifndef MAINWINDOWDRIVER_H
#define MAINWINDOWDRIVER_H

#include <QMainWindow>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui {  class MainWindowDriver;}
QT_END_NAMESPACE

class MainWindowDriver : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindowDriver(QWidget *parent = nullptr);
    ~MainWindowDriver();

private slots:
    void on_button_logout_clicked();

private:
    Ui::MainWindowDriver *ui;
};

#endif // MAINWINDOWDRIVER_H
