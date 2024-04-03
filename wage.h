#ifndef WAGE_H
#define WAGE_H

#include "sqlmanager.h"
#include "users.h"

class Wage
{
  public:
    static Wage* instance;

  private:
    SQLManager* sqlmar;
    QVector<QStringList> thisUserWage;

  public:
    Wage();
    static Wage* Instance()
    {
        if (instance == nullptr)
            instance = new Wage();
        return instance;
    }

    void SetWageInfo(int BaseWage, int bonus, int mounth);
    QVector<QStringList> GetWageInfo();
    void InitializeWageInfo();
};

#endif // WAGE_H
