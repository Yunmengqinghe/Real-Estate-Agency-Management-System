#ifndef USERS_H
#define USERS_H

#include "sqlmanager.h"

class Users
{
  public:
    static Users* instance;

  private:
    SQLManager* sqlmar;
    QVector<QStringList> users;
    QVector<QStringList> sellerUsers;
    QStringList thisUser;

  public:
    Users();
    static Users* Instance()
    {
        if (nullptr == instance)
        {
            instance = new Users();
        }
        return instance;
    }

    bool Login(QString userID, QString userPassword);
    bool Register(QStringList user);
    void InitializeUserInfo();
    QStringList GetThisUserInfo();
    QVector<QStringList> GetSellerInfo();
    QVector<QStringList> GetAllUserInfo();
};

#endif // USERS_H
