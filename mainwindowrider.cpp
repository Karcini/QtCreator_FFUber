#include "mainwindowrider.h"
#include "ui_mainwindowrider.h"

#include <QAction>
#include <QString>
#include <QImage>
#include <QAbstractItemView>

MainWindowRider::MainWindowRider(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowRider)
{
    //initializations
    ui->setupUi(this);
    buttonAddDestination = ui->button_add;
    buttonFinalizeTrip = ui->button_complete;
    buttonCancelTrip = ui->button_cancel;
    statusLabel = ui->label_status;
    zoomInAct = ui->act_zoomIn;
    zoomOutAct = ui->act_zoomOut;
    normalizeAct = ui->act_normalize;
    fitToWindowAct = ui->act_fitToWindow;
    historyAct = ui->act_history;
    mapLabel = ui->label_map;
    mapArea = ui->scrollArea_map;
    scaleFactor = 1.0;
    tripStarted = false;

    user = new LoginWindow();
    userHistory = new TransactionHistory();

    //map image
    QString imageFilePath = "../CIS17B_Final/map_ffxiv_eorzea_lowres.jpg";  //Original path
    //QString imageFilePath = "map_ffxiv_eorzea_lowres.jpg";                    //Absolute path
    QImage imageMap(imageFilePath);
    mapLabel->setPixmap(QPixmap::fromImage(imageMap));
    mapLabel->setScaledContents(true);
    mapArea->setBackgroundRole(QPalette::Dark);

    //access database
    //destinationList = new DestinationsDB(); //un needed??

    //fill tables and gui
    populateDrivers();
    populateDestinations();
    resetRiderGUI();
    onUserLogin();

    //connections
    connect(buttonCancelTrip, SIGNAL(clicked()), this, SLOT(cancelTrip()));
    connect(buttonFinalizeTrip, SIGNAL(clicked()), this, SLOT(completeTrip()));
    connect(buttonAddDestination, SIGNAL(clicked()), this, SLOT(addDestination()));
    connect(ui->actionLogin, SIGNAL(triggered()), this, SLOT(loginDialog()));
    connect(zoomInAct, SIGNAL(triggered()), this, SLOT(zoomIn()));
    connect(zoomOutAct, SIGNAL(triggered()), this, SLOT(zoomOut()));
    connect(normalizeAct, SIGNAL(triggered()), this, SLOT(normalSize()));
    connect(fitToWindowAct, SIGNAL(triggered()), this, SLOT(fitToWindow()));
    connect(historyAct, SIGNAL(triggered()), this, SLOT(historyDialog()));
    connect(ui->list_drivers, SIGNAL(pressed(QModelIndex)), this, SLOT(tripDetailsSelected()));
    connect(ui->list_destFrom, SIGNAL(pressed(QModelIndex)), this, SLOT(tripDetailsSelected()));
    connect(ui->list_destTo, SIGNAL(pressed(QModelIndex)), this, SLOT(tripDetailsSelected()));
    connect(user, SIGNAL(loginSignal()), this, SLOT(onLoginWindowClose()));

    //temporary connections for testing
    //connect(ui->button_testAdd, SIGNAL(clicked()), this, SLOT(addDriver()));
}

MainWindowRider::~MainWindowRider()
{
    //ui pointer deletes its children
    delete ui;
    //delete floating pointers?
    delete driverModel;
    delete destModel;
    delete user;
    delete userHistory;
}
//MAP FUNCTIONS   ----------------------
void MainWindowRider::updateActions()
{
    //update action clickability when "state change" is clicked
    zoomInAct->setEnabled(!fitToWindowAct->isChecked());
    zoomOutAct->setEnabled(!fitToWindowAct->isChecked());
    normalizeAct->setEnabled(!fitToWindowAct->isChecked());
}
void MainWindowRider::zoomIn()
{
    qDebug() << "zoom in";
    scaleImage(1.25);
}
void MainWindowRider::zoomOut()
{
    qDebug() << "zoom out";
    scaleImage(0.8);
}
void MainWindowRider::normalSize()
{
    qDebug() << "normalize zoom";
    mapLabel->adjustSize();
    scaleFactor = 1.0;
}
void MainWindowRider::fitToWindow()
{
    //qDebug() << "fitToWindow()";  //should work
    bool fitToWindow = fitToWindowAct->isChecked();
    mapArea->setWidgetResizable(fitToWindow);

    //reset sizes
    if(!fitToWindow)
    {
        normalSize();
    }
    updateActions();
}
void MainWindowRider::scaleImage(double factor)
{
    //increase image size by passed in factor
    Q_ASSERT(mapLabel->pixmap());
    scaleFactor *= factor;
    mapLabel->resize(scaleFactor * mapLabel->pixmap()->size());

    //change scroll bars by factor
    adjustScrollBar(mapArea->horizontalScrollBar(), factor);
    adjustScrollBar(mapArea->verticalScrollBar(), factor);

    //enable and disable zooms at a max and min
    zoomInAct->setEnabled(scaleFactor < 3.0);
    zoomOutAct->setEnabled(scaleFactor > 0.2);
}
void MainWindowRider::adjustScrollBar(QScrollBar *scrollBar, double factor)
{
    scrollBar->setValue(int(factor * scrollBar->value() + ((factor - 1) * scrollBar->pageStep()/2)));
    //scrollBar->setValue(int(factor * scrollBar->value())); //centers image on the top left corner
}


//POPULATE GUI   ----------------------
void MainWindowRider::populateDestinations()
{
    destModel = new QStringListModel(this);
    QStringList list;

    //populate list from databse
    for(int x=0; x<database.destinations.size(); x++)
    {
        list.append(database.destinations[x].getName());
    }

    destModel->setStringList(list);

    ui->list_destFrom->setModel(destModel);
    ui->list_destFrom->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->list_destTo->setModel(destModel);
    ui->list_destTo->setEditTriggers(QAbstractItemView::NoEditTriggers);
}
void MainWindowRider::populateDrivers()
{
    //get the new database information and populate drivers
    driverModel = new QStringListModel(this);
    QStringList list;

    //populate list from databse instead
    for(int x=0; x<database.drivers.size(); x++)
    {
        list.append(database.drivers[x].getname());
    }

    driverModel->setStringList(list);
    ui->list_drivers->setModel(driverModel);
    ui->list_drivers->setEditTriggers(QAbstractItemView::NoEditTriggers);
}
void MainWindowRider::addDriver()
{
    //This FUNC was used for testing purposes and is now unused


    //Currently this FUNC adds a custom Qstring to the listview for drivers
    qDebug() << "Driver added";
    int row = driverModel->rowCount();            //get position of list
    driverModel->insertRows(row,1);               //enable add one or more rows
    QModelIndex index = driverModel->index(row);  //Get row to edit

    //add to list
    ui->list_drivers->setCurrentIndex(index);
    ui->list_drivers->edit(index);
    //add to database
        //...

    //example for deleting from Model
    //driverModel->removeRows(ui->list_drivers->currentIndex().row(), 1);
}




//TRIP FUNCTIONS ----------------------
void MainWindowRider::tripDetailsSelected()
{
    bool isEmpty = false;
    bool isValid = true;
    if(!isEmpty)
        isEmpty = checkListSelected(ui->list_drivers);
    if(!isEmpty)
        isEmpty = checkListSelected(ui->list_destFrom);
    if(!isEmpty)
        isEmpty = checkListSelected(ui->list_destTo);

    isValid = checkListValid(ui->list_destFrom, ui->list_destTo);

    //All trip details are selected and Selection is Valid...
    if(!isEmpty && isValid)
    {
        buttonAddDestination->setEnabled(true);
    }
    else
        buttonAddDestination->setEnabled(false);
}
bool MainWindowRider::checkListSelected(QListView * list)
{
    QModelIndex modelIndex = list->currentIndex();
    QString text = modelIndex.data(Qt::DisplayRole).toString();
    if(text == "")
        return true;
    return false;
}
bool MainWindowRider::checkListValid(QListView * list1, QListView * list2)
{
    QString text1, text2;
    QModelIndex modelIndex;
    modelIndex = list1->currentIndex();
    text1 = modelIndex.data(Qt::DisplayRole).toString();
    modelIndex = list2->currentIndex();
    text2 = modelIndex.data(Qt::DisplayRole).toString();
    if(text1 == text2)
        return false;
    return true;
}
void MainWindowRider::addDestination()
{
    //Create New Travel Receipt
    QModelIndex modelIndex;
    if(!tripStarted)
    {
        //Save Rider
        currentTR.rider = user->currentLogin; //.name()   if it wasn't just a QString

        //Lock in Driver
        modelIndex = ui->list_drivers->currentIndex();
        QString currentDriver = modelIndex.data(Qt::DisplayRole).toString();
        currentTR.driver = database.getDriver(currentDriver);
        qDebug() << currentTR.driver.getname() << " is ferrying you";

        //Lock GUI until trip is completed or canceled
        ui->actionLogin->setEnabled(false);
        ui->list_drivers->setEnabled(false);
        tripStarted = true;
    }


    //confirm 'from' destination
    modelIndex = ui->list_destFrom->currentIndex();
    QString start = modelIndex.data(Qt::DisplayRole).toString();
    //confirm 'to' destination
    modelIndex = ui->list_destTo->currentIndex();
    QString end = modelIndex.data(Qt::DisplayRole).toString();
    //get trip price
    int tripPrice = database.getTripPrice(start, end);

    //"Save" destination parameters for receipt
    Trip t(start, end, tripPrice);
    currentTR.addTrip(t);


    //lock 'from' destination as the 'to' destination
    ui->list_destFrom->setCurrentIndex(modelIndex); //model index currently being list_destTo's index
    ui->list_destFrom->setEnabled(false);


    //Display current receipt
    ui->textEdit_display->setText(currentTR.displayTripInfo());


    //Any follow up events
    statusLabel->setText("Select follow up destination or Confirm/Cancel");
    buttonFinalizeTrip->setEnabled(true);
    buttonCancelTrip->setEnabled(true);
    buttonAddDestination->setEnabled(false);
}
void MainWindowRider::completeTrip()
{
    qDebug() << "Trip Confirmed";
    //save information as necessary
    currentTR.printReceipt();

    //display
    ui->textEdit_display->setText("Receipt Issued");

    //reset gui
    resetRiderGUI();

    //reset info
    currentTR.resetReceipt();
}
void MainWindowRider::cancelTrip()
{
    qDebug() << "Trip was Canceled";
    //cancel any saved information as necessary
        //none to cancel

    //reset gui
    resetRiderGUI();
    ui->textEdit_display->clear();

    //reset info
    currentTR.resetReceipt();
}
void MainWindowRider::resetRiderGUI()
{
    //Reset any information that is locked on creating trips
    tripStarted = false;
    ui->list_drivers->setEnabled(true);
    ui->list_destFrom->setEnabled(true);
    ui->actionLogin->setEnabled(true);

    buttonAddDestination->setEnabled(false);
    buttonFinalizeTrip->setEnabled(false);
    buttonCancelTrip->setEnabled(false);
    QString text = "Please select trip details";
    statusLabel->setText(text);
}



//LOGINS         ----------------------
void MainWindowRider::loginDialog()
{
    qDebug() << "Login initiated";
    //loginWindow->isModal(); //QWidget asynchronous, modality is changable in designer (not usual in practice)
    user->show();

    //qDebug() << "loginDialog function finishes";
}
void MainWindowRider::onUserLogin()
{
    //Refresh information on Login Change
    QString currentRider = user->currentLogin; //appears trivial, but QString is our rider class type
    database.fillDrivers();

    //Refresh any UI
    QString intro = "Hello " + currentRider + "!";
    ui->label_hello->setText(intro);
    populateDrivers();

}
void MainWindowRider::onLoginWindowClose()
{
    //qDebug() << "login window closed";
    onUserLogin();
}



//LOGINS         ----------------------
void MainWindowRider::historyDialog()
{
    qDebug() << "History initiated";
    //log active login
    qDebug() << "current log in " << user->currentLogin;
    userHistory->setActiveLogin(user->currentLogin);

    userHistory->show();
    userHistory->refreshHistory(); //not really proper since programmed to be modal, but works
}
