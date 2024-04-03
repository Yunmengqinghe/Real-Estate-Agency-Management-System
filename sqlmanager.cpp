#include "sqlmanager.h"

SQLManager::SQLManager()
{
    db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("SEsql");
    db.setHostName("127.0.0.1");
    db.setDatabaseName("SEsql");
    db.setPort(1433);

    if (!db.open())
    {
        qDebug() << "失败原因：" << db.lastError().text();
    }
    else
    {
        qDebug() << "连接成功";
    }
    db.close();
}

QVector<QStringList> SQLManager::GetUsers()
{
    db.open();
    QSqlQuery query("SELECT * FROM USER_INFORMATION");
    QVector<QStringList> allusers;
    while (query.next())
    {
        QStringList user;
        user.push_back(query.value("ID").toString());
        user.push_back(query.value("NAME").toString());
        user.push_back(query.value("PHONE_NUMBER").toString());
        user.push_back(query.value("PASSWORD").toString());
        allusers.push_back(user);
    }
    db.close();
    return allusers;
}

void SQLManager::AddUser(QStringList user)
{
    db.open();
    QSqlQuery query;
    query.prepare("INSERT INTO USER_INFORMATION (ID, NAME, PHONE_NUMBER, PASSWORD) "
                  "VALUES (?, ?, ?, ?)");
    query.bindValue(0, user[0]);
    query.bindValue(1, user[1]);
    query.bindValue(2, user[2]);
    query.bindValue(3, user[3]);
    query.exec();
    db.close();
}

void SQLManager::AddWage(QVector<QStringList> sellerInfo, int baseWage,
                         int bonus, int mounth)
{
    db.open();
    QSqlQuery query;
    query.prepare("INSERT INTO WAGES (SELLER_ID, TIME, WAGES, BONUS) "
                  "VALUES (?, ?, ?, ?)");
    for (auto elem : sellerInfo)
    {
        query.bindValue(0, elem[0]);
        query.bindValue(1, mounth);
        query.bindValue(2, baseWage);
        query.bindValue(3, bonus);
        query.exec();
    }
    db.close();
}

QVector<QStringList> SQLManager::GetWages()
{
    db.open();
    QSqlQuery query("SELECT * FROM WAGES");
    QVector<QStringList> wageInfo;
    while (query.next())
    {
        QStringList info;
        info.push_back(query.value("SELLER_ID").toString());
        info.push_back(query.value("TIME").toString());
        info.push_back(query.value("WAGES").toString());
        info.push_back(query.value("BONUS").toString());
        wageInfo.push_back(info);
    }
    db.close();
    return wageInfo;
}

void SQLManager::AddCheckIn(QStringList user, QString checkInTime,
                            int isLate)
{
    db.open();
    QSqlQuery query;
    query.prepare("INSERT INTO CHECKIN (SELLER_ID, TIME, IS_LATE) "
                  "VALUES (?, ?, ?)");
    query.bindValue(0, user[0]);
    query.bindValue(1, checkInTime);
    query.bindValue(2, isLate);
    query.exec();
    db.close();
}

void SQLManager::AddHouseSource(QString houseID, QString pos, QString userID,
                                int price)
{
    db.open();
    QSqlQuery query;
    query.prepare("INSERT INTO HOUSE_RESOURCES (ID, POSITION, CUSTOM_ID, PRICE, IS_CHECK, IS_UPLOAD) "
                  "VALUES (?, ?, ?, ?, ?, ?)");
    query.bindValue(0, houseID);
    query.bindValue(1, pos);
    query.bindValue(2, userID);
    query.bindValue(3, price);
    query.bindValue(4, 0);
    query.bindValue(5, 0);
    query.exec();
    db.close();
}

QVector<QStringList> SQLManager::GetHouseSource()
{
    db.open();
    QSqlQuery query("SELECT * FROM HOUSE_RESOURCES");
    QVector<QStringList> hourseSource;
    while (query.next())
    {
        QStringList info;
        info.push_back(query.value("ID").toString());
        info.push_back(query.value("POSITION").toString());
        info.push_back(query.value("CUSTOM_ID").toString());
        info.push_back(query.value("PRICE").toString());
        info.push_back(query.value("IS_CHECK").toString());
        info.push_back(query.value("IS_UPLOAD").toString());
        hourseSource.push_back(info);
    }
    db.close();
    return hourseSource;
}

void SQLManager::UpdateHouseSource(QString id, int check, int upload)
{
    db.open();
    QSqlQuery query;
    query.prepare("UPDATE HOUSE_RESOURCES SET IS_CHECK = ? , IS_UPLOAD = ? WHERE ID = ?");
    query.bindValue(0, check);
    query.bindValue(1, upload);
    query.bindValue(2, id);
    query.exec();
    db.close();
}

QVector<QStringList> SQLManager::GetReservation()
{
    db.open();
    QSqlQuery query("SELECT * FROM RESERVATION");
    QVector<QStringList> resInfo;
    while (query.next())
    {
        QStringList info;
        info.push_back(query.value("ID").toString());
        info.push_back(query.value("CUSTOM_ID").toString());
        info.push_back(query.value("SELLER_ID").toString());
        info.push_back(query.value("HOUSE_ID").toString());
        info.push_back(query.value("TIME").toString());
        resInfo.push_back(info);
    }
    db.close();
    return resInfo;
}

void SQLManager::AddReservation(QString id, QString customID, QString sellerID,
                                QString houseID, QString time)
{
    db.open();
    QSqlQuery query;
    query.prepare("INSERT INTO RESERVATION (ID, CUSTOM_ID, SELLER_ID, HOUSE_ID, TIME) "
                  "VALUES (?, ?, ?, ?, ?)");
    query.bindValue(0, id);
    query.bindValue(1, customID);
    query.bindValue(2, sellerID);
    query.bindValue(3, houseID);
    query.bindValue(4, time);
    query.exec();
    db.close();
}

void SQLManager::UpdateReservation(QString resId, QString id)
{
    db.open();
    QSqlQuery query;
    query.prepare("UPDATE RESERVATION SET SELLER_ID = ? WHERE ID = ?");
    query.bindValue(0, id);
    query.bindValue(1, resId);
    query.exec();
    db.close();
}

void SQLManager::AddTransaction(QString id, QString customID,
                                QString sellerID, QString houseID,
                                int price, int stage)
{
    db.open();
    QSqlQuery query;
    query.prepare("INSERT INTO [TRANSACTION] (ID, CUSTOM_ID, SELLER_ID, HOUSE_ID, PRICE, STAGE) "
                  "VALUES (?, ?, ?, ?, ?, ?)");
    query.bindValue(0, id);
    query.bindValue(1, customID);
    query.bindValue(2, sellerID);
    query.bindValue(3, houseID);
    query.bindValue(4, price);
    query.bindValue(5, stage);
    query.exec();
    db.close();
}

QVector<QStringList> SQLManager::GetTransaction()
{
    db.open();
    QSqlQuery query("SELECT * FROM [TRANSACTION]");
    QVector<QStringList> transInfo;
    while (query.next())
    {
        QStringList info;
        info.push_back(query.value("ID").toString());
        info.push_back(query.value("CUSTOM_ID").toString());
        info.push_back(query.value("SELLER_ID").toString());
        info.push_back(query.value("HOUSE_ID").toString());
        info.push_back(query.value("PRICE").toString());
        info.push_back(query.value("STAGE").toString());
        transInfo.push_back(info);
    }
    db.close();
    return transInfo;
}

void SQLManager::UpdateTransaction(QString id, int stage)
{
    db.open();
    QSqlQuery query;
    query.prepare("UPDATE [TRANSACTION] SET STAGE = ? WHERE ID = ?");
    query.bindValue(0, stage);
    query.bindValue(1, id);
    query.exec();
    db.close();
}
