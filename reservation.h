#ifndef RESERVATION_H
#define RESERVATION_H

#include "houseresource.h"
#include "sqlmanager.h"
#include "transaction.h"
#include "users.h"
class Reservation
{
  public:
    static Reservation* instance;

  private:
    QVector<QStringList> resInfo;

  public:
    static Reservation* Instance()
    {
        if (instance == nullptr)
            instance = new Reservation();
        return instance;
    }
    Reservation();
    void InitializeInfo();
    bool ExistID(QString id);
    bool ExistPending(QString id, QString time);
    void AddReservation(QString id, QString houseID, QString time);
    QVector<QStringList> GetUnCheckResInfo();
    void UpdateResInfo(QString id);
};

#endif // RESERVATION_H
