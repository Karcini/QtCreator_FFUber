#ifndef TRANSACTIONHISTORY_H
#define TRANSACTIONHISTORY_H

#include <QWidget>
#include <QTextEdit>
#include <QList>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include "transaction.h"

namespace Ui {
class TransactionHistory;
}

class TransactionHistory : public QWidget
{
    Q_OBJECT

public:
    explicit TransactionHistory(QWidget *parent = nullptr);
    ~TransactionHistory();

    void setActiveLogin(QString); //our login is just a QString class
    void refreshHistory();

private:
    Ui::TransactionHistory *ui;
    QString activeLogin; //in our case, string of name

    QTextEdit * textEdit_history;
    QList<Transaction> transactions;
    void startDatabase();
    void saveTransactions();
    void displayTransactions(int);
    QString printAllTransactions();

    QSqlDatabase mydb;
};

#endif // TRANSACTIONHISTORY_H
