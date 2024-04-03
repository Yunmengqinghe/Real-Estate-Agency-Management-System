#ifndef CHECKININFO_H
#define CHECKININFO_H

#include "sqlmanager.h"
#include "users.h"
#include <QDateTime>
#include <QTime>

class CheckInInfo
{
  public:
    static CheckInInfo* instance;

  public:
    static CheckInInfo* Instance()
    {
        if (instance == nullptr)
            instance = new CheckInInfo();
        return instance;
    }
    CheckInInfo();
    bool LatePending(QTime time);
    void CheckIn(QString time, bool isLate);

  private:
    QTime lateTime;
    SQLManager* sqlmar;
};

#endif // CHECKININFO_H
