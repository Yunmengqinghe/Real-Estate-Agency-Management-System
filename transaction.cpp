#include "transaction.h"

Transaction* Transaction::instance = nullptr;
Transaction::Transaction()
{
    InitializeInfo();
}

void Transaction::InitializeInfo()
{
    SQLManager* sqlMgr = new SQLManager();
    QVector<QStringList> allTransInfo = sqlMgr->GetTransaction();
    for (auto elem : allTransInfo)
    {
        if (elem[5] == '3')
            endTransInfo.push_back(elem);
        else
        {
            unTransInfo.push_back(elem);
        }
    }
    delete sqlMgr;
}

QVector<QStringList> Transaction::GetEndTransInfo()
{
    return endTransInfo;
}

QVector<QStringList> Transaction::GetUnTransInfo()
{
    return unTransInfo;
}

bool Transaction::SetTransInfo(QString id, int stage)
{
    bool isCan = false;
    for (auto elem : unTransInfo)
    {
        if (elem[0] == id)
        {
            isCan = true;
            break;
        }
    }
    if (isCan == true)
    {
        SQLManager* sqlMgr = new SQLManager();
        sqlMgr->UpdateTransaction(id, stage);
        delete sqlMgr;
        return true;
    }
    else
        return false;
}

void Transaction::AddTransaction(QString id, QString customID,
                                 QString sellerID, QString houseID,
                                 int price, int stage)
{
    SQLManager* sqlMgr = new SQLManager();
    sqlMgr->AddTransaction(id, customID, sellerID, houseID, price, stage);
    delete sqlMgr;
}
