#ifndef CUSTOMSCREEN_H
#define CUSTOMSCREEN_H

#include "houseresource.h"
#include "reservation.h"
#include "sqlmanager.h"
#include "users.h"
#include <QMainWindow>
#include <QMessageBox>
#include <QStandardItemModel>

namespace Ui
{
    class CustomScreen;
}

class CustomScreen : public QMainWindow
{
    Q_OBJECT

  public:
    explicit CustomScreen(QWidget* parent = nullptr);
    ~CustomScreen();
    void InitializeHouseInfo();
    void InitializeThisUser();

  private:
    Ui::CustomScreen* ui;
    QStandardItemModel* houseModel;

  public slots:
    void ShowScreen();
    void AddHouseInfo();
    void BuyHouse();
    void EnsureReserver();
};

#endif // CUSTOMSCREEN_H
