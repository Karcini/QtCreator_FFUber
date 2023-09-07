#include "transaction.h"

Transaction::Transaction()
{

}

QString Transaction::printTransaction()
{
    QString s = date + ": Driver-" + driverName
            + "\t" + startLocation +"-->"+ endLocation
            + "  " + QString::number(price) + "gil";
    return s;
}
