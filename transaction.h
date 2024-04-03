#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "sqlmanager.h"
#include "users.h"

class Transaction
{
  public:
    static Transaction* instance;

  private:
    QVector<QStringList> endTransInfo;
    QVector<QStringList> unTransInfo;

  public:
    static Transaction* Instance()
    {
        if (instance == nullptr)
            instance = new Transaction();
        return instance;
    }
    Transaction();
    void InitializeInfo();
    QVector<QStringList> GetEndTransInfo();
    QVector<QStringList> GetUnTransInfo();
    bool SetTransInfo(QString id, int stage);
    void AddTransaction(QString id, QString customID, QString sellerID,
                        QString houseID, int price, int stage);
};

#endif // TRANSACTION_H
