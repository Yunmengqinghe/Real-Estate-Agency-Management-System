#include "reservation.h"

Reservation* Reservation::instance = nullptr;
Reservation::Reservation()
{
    InitializeInfo();
}

void Reservation::InitializeInfo()
{
    SQLManager* sqlmgr = new SQLManager();
    resInfo = sqlmgr->GetReservation();
    delete sqlmgr;
}

bool Reservation::ExistID(QString id)
{
    for (auto elem : resInfo)
    {
        if (elem[0] == id)
            return true;
    }
    return false;
}

bool Reservation::ExistPending(QString id, QString time)
{
    for (auto elem : resInfo)
    {
        if (elem[2] == id)
            if (elem[3] == time)
                return true;
    }
    return false;
}

void Reservation::AddReservation(QString id, QString houseID, QString time)
{
    Users* user = Users::Instance();
    QStringList userInfo = user->GetThisUserInfo();
    SQLManager* sqlmgr = new SQLManager();
    sqlmgr->AddReservation(id, userInfo[0], "None", houseID, time);
    delete sqlmgr;
}

QVector<QStringList> Reservation::GetUnCheckResInfo()
{
    QVector<QStringList> info;
    for (auto elem : resInfo)
    {
        if (elem[2] == "None")
        {
            QStringList infoList;
            infoList.push_back(elem[0]);
            infoList.push_back(elem[1]);
            infoList.push_back(elem[2]);
            infoList.push_back(elem[3]);
            infoList.push_back(elem[4]);
            info.push_back(infoList);
        }
    }
    return info;
}

void Reservation::UpdateResInfo(QString id)
{

    Users* user = Users::Instance();
    QStringList thisUser = user->GetThisUserInfo();

    SQLManager* sqlmgr = new SQLManager();
    sqlmgr->UpdateReservation(id, thisUser[0]);
    delete sqlmgr;
    QStringList thisRes;
    for (auto elem : resInfo)
    {
        if (elem[0] == id)
            thisRes = elem;
    }

    int price;
    HouseResource* house = HouseResource::Instance();
    QVector<QStringList> houseInfo;
    houseInfo = house->GetUploadHouseInfo();
    for (auto elem : houseInfo)
    {
        if (elem[0] == id)
        {
            price = elem[3].toInt();
            break;
        }
    }
    Transaction* trans = Transaction::Instance();
    trans->AddTransaction(thisRes[0], thisRes[1], thisUser[0], thisRes[3], price, 1);
}
