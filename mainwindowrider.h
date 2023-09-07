#ifndef MAINWINDOWRIDER_H
#define MAINWINDOWRIDER_H

#include <QMainWindow>
#include <QDebug>
#include <QAction>
#include <QLabel>
#include <QScrollBar>
#include <QScrollArea>
#include <QStringListModel>
#include <QStringList>
#include <QPushButton>
#include <QListView>

#include "destinationsdb.h"
#include "travelreceipt.h"
#include "loginwindow.h"
#include "transactionhistory.h"

QT_BEGIN_NAMESPACE
namespace Ui {  class MainWindowRider;}
QT_END_NAMESPACE

class MainWindowRider : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindowRider(QWidget *parent = nullptr);
    ~MainWindowRider();

private slots:
    //MAP SLOTS
    void zoomIn();
    void zoomOut();
    void normalSize();
    void fitToWindow();

    //FULL GUI SLOTS
    void addDriver();   //unused button for testing purposes

    //TRIP SLOTS
    void tripDetailsSelected();
    void addDestination();
    void completeTrip();
    void cancelTrip();

    //LOGIN SLOTS
    void loginDialog();
    void onLoginWindowClose();

    //HISTORY SLOTS
    void historyDialog();

private:
    //Class Variables
    Ui::MainWindowRider *ui;
    QPushButton * buttonFinalizeTrip;
    QPushButton * buttonCancelTrip;
    QPushButton * buttonAddDestination;
    QLabel * statusLabel;
    QLabel * mapLabel;
    QScrollArea * mapArea;
    QAction * zoomInAct;
    QAction * zoomOutAct;
    QAction * normalizeAct;
    QAction * fitToWindowAct;
    QAction * historyAct;
    double scaleFactor;
    QStringListModel * driverModel;
    QStringListModel * destModel;
    bool tripStarted;
    QString currentDriver;
    TravelReceipt currentTR;
    //QString currentRider;

    //database objects
    DestinationsDB database;
    LoginWindow * user;
    TransactionHistory * userHistory;

    //MAP FUNCTIONS
    void updateActions();
    void scaleImage(double);
    void adjustScrollBar(QScrollBar *, double);

    //FILL GUI FUNCTIONS
    void populateDestinations();
    void populateDrivers();

    //TRIP FUNCTIONS
    bool checkListSelected(QListView *);
    bool checkListValid(QListView *, QListView *);
    void resetRiderGUI();

    //LOGIN FUNCTIONS
    void onUserLogin();

    //HISTORY FUNCTIONS
};

#endif // MAINWINDOWRIDER_H
