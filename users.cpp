#include "users.h"

Users* Users::instance = nullptr;
Users::Users()
{
    InitializeUserInfo();
}

bool Users::Login(QString userID, QString userPassword)
{

    for (auto elem : users)
    {
        if (elem[0] == userID)
            if (elem[3] == userPassword)
            {
                thisUser = elem;
                return true;
            }
    }
    return false;
}

bool Users::Register(QStringList userInfo)
{
    if (userInfo.count() == 0)
    {
        return false;
    }
    sqlmar = new SQLManager();
    sqlmar->AddUser(userInfo);
    users = sqlmar->GetUsers();
    delete sqlmar;
    return true;
}

void Users::InitializeUserInfo()
{
    sqlmar = new SQLManager();
    users = sqlmar->GetUsers();
    for (auto elem : users)
    {
        if (elem[0][0] == '2')
            sellerUsers.append(elem);
    }
    delete sqlmar;
}

QVector<QStringList> Users::GetAllUserInfo()
{
    return users;
}

QStringList Users::GetThisUserInfo()
{
    return thisUser;
}

QVector<QStringList> Users::GetSellerInfo()
{
    return sellerUsers;
}
