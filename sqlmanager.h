#ifndef SQLMANAGER_H
#define SQLMANAGER_H

#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QString>
#include <QStringList>
#include <QVector>

class SQLManager
{
  public:
    QSqlDatabase db;

  public:
    SQLManager();
    QVector<QStringList> GetUsers();
    void AddUser(QStringList user);
    void AddWage(QVector<QStringList> sellerInfo, int BaseWage,
                 int bonus, int mounth);
    QVector<QStringList> GetWages();
    void AddCheckIn(QStringList user, QString checkInTime,
                    int isLate);
    void AddHouseSource(QString houseID, QString pos, QString userID, int price);
    QVector<QStringList> GetHouseSource();
    void UpdateHouseSource(QString id, int check, int upload);
    QVector<QStringList> GetReservation();
    void AddReservation(QString id, QString customID, QString sellerID,
                        QString houseID, QString time);
    void UpdateReservation(QString resId, QString id);
    void AddTransaction(QString id, QString customID, QString sellerID,
                        QString houseID, int price, int stage);
    QVector<QStringList> GetTransaction();
    void UpdateTransaction(QString id, int stage);
};

#endif // SQLMANAGER_H
