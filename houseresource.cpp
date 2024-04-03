#include "houseresource.h"

HouseResource* HouseResource::instance = nullptr;
HouseResource::HouseResource()
{
    InitializeHouseInfo();
}

void HouseResource::AddHouseResource(QString id, QString pos, int price)
{
    Users* user = Users::Instance();
    QStringList thisUser = user->GetThisUserInfo();
    SQLManager* sqlmar = new SQLManager();
    sqlmar->AddHouseSource(id, pos, thisUser[0], price);
    delete sqlmar;
}

void HouseResource::SetBuyHouseInfo(QString id)
{
    SQLManager* sqlmgr = new SQLManager();
    sqlmgr->UpdateHouseSource(id, 1, 0);
    delete sqlmgr;
}

bool HouseResource::ExistPending(QString id)
{
    for (auto elem : upHouseInfo)
    {
        if (id == elem[0])
        {
            return true;
        }
    }
    return false;
}

void HouseResource::InitializeHouseInfo()
{
    SQLManager* sqlmar = new SQLManager();
    allHouseInfo = sqlmar->GetHouseSource();
    delete sqlmar;
    for (auto elem : allHouseInfo)
    {
        if (elem[4] == '0')
        {
            checkHouseInfo.push_back(elem);
        }
        if (elem[5] == '1')
        {
            upHouseInfo.push_back(elem);
        }
    }
}

QVector<QStringList> HouseResource::GetCheckHouseInfo()
{
    return checkHouseInfo;
}

QVector<QStringList> HouseResource::GetUploadHouseInfo()
{
    return upHouseInfo;
}

QVector<QStringList> HouseResource::GetAllHouseInfo()
{
    return allHouseInfo;
}

void HouseResource::SetCheckHouseInfo(QString id, int check)
{
    SQLManager* sqlmgr = new SQLManager();
    sqlmgr->UpdateHouseSource(id, check, 1);
    delete sqlmgr;
}
