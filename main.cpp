#include "AppWindows.h"  //bundle of includes to reduce clutter
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //LoginWindow w;
    MainWindowRider w;
    //MainWindowDriver w;
    w.show();

    return a.exec();
}
