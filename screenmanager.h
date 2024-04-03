#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H

#include "adminscreen.h"
#include "customscreen.h"
#include "loginscreen.h"
#include "registerscreen.h"
#include "sellerscreen.h"
#include <QObject>

class ScreenManager : public QObject
{
    Q_OBJECT
  public:
    ScreenManager();
};

#endif // SCREENMANAGER_H
