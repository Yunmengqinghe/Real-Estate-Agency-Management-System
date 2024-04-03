#include "wage.h"

Wage* Wage::instance = nullptr;
Wage::Wage()
{
    InitializeWageInfo();
}

void Wage::SetWageInfo(int baseWage, int bonus, int month)
{
    Users* user = Users::Instance();
    QVector<QStringList> sellerInfo = user->GetSellerInfo();
    sqlmar = new SQLManager();
    sqlmar->AddWage(sellerInfo, baseWage, bonus, month);
    delete sqlmar;
}

QVector<QStringList> Wage::GetWageInfo()
{
    return thisUserWage;
}

void Wage::InitializeWageInfo()
{
    sqlmar = new SQLManager();
    Users* user = Users::Instance();
    QStringList thisUser = user->GetThisUserInfo();

    QVector<QStringList> allUserWage;
    allUserWage = sqlmar->GetWages();

    for (auto elem : allUserWage)
    {
        if (elem[0] == thisUser[0])
            thisUserWage.push_back(elem);
    }
    delete sqlmar;
}
