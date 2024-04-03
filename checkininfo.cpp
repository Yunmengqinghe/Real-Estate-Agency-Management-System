#include "checkininfo.h"
CheckInInfo* CheckInInfo::instance = nullptr;
CheckInInfo::CheckInInfo()
{
    lateTime.setHMS(9, 0, 0, 0);
}

bool CheckInInfo::LatePending(QTime time)
{
    if (time > lateTime)
        return true;
    return false;
}

void CheckInInfo::CheckIn(QString time, bool isLate)
{
    Users* user = Users::Instance();
    QStringList thisUser = user->GetThisUserInfo();
    sqlmar = new SQLManager();
    if (isLate == true)
        sqlmar->AddCheckIn(thisUser, time, 1);
    else
        sqlmar->AddCheckIn(thisUser, time, 0);
}
