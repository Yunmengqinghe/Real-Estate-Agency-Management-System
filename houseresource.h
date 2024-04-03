#ifndef HOUSERESOURCE_H
#define HOUSERESOURCE_H

#include "sqlmanager.h"
#include "users.h"

class HouseResource
{
  public:
    static HouseResource* instance;

  private:
    QVector<QStringList> upHouseInfo;
    QVector<QStringList> checkHouseInfo;
    QVector<QStringList> allHouseInfo;

  public:
    static HouseResource* Instance()
    {
        if (instance == nullptr)
            instance = new HouseResource();
        return instance;
    }
    HouseResource();
    void InitializeHouseInfo();
    QVector<QStringList> GetCheckHouseInfo();
    QVector<QStringList> GetUploadHouseInfo();
    QVector<QStringList> GetAllHouseInfo();
    void SetCheckHouseInfo(QString id, int check);
    void AddHouseResource(QString id, QString pos, int price);
    void SetBuyHouseInfo(QString id);
    bool ExistPending(QString id);
};

#endif // HOUSERESOURCE_H
