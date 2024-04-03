#ifndef SELLERSCREEN_H
#define SELLERSCREEN_H

#include "checkininfo.h"
#include "houseresource.h"
#include "reservation.h"
#include "sqlmanager.h"
#include "wage.h"
#include <QMainWindow>
#include <QStandardItemModel>

namespace Ui
{
    class SellerScreen;
}

class SellerScreen : public QMainWindow
{
    Q_OBJECT

  public:
    explicit SellerScreen(QWidget* parent = nullptr);
    ~SellerScreen();
    void InitializeReportInfo();
    void InitializeTransInfo();
    void InitialzeResInfo();
    void InitialzeHouseInfo();
    void InitializeWageInfo();
    void InitializeThisUser();

  private:
    Ui::SellerScreen* ui;
    QStandardItemModel* wageInfoModel;
    QStandardItemModel* houseInfoModel;
    QStandardItemModel* resInfoModel;
    QStandardItemModel* unTransModel;
    QStandardItemModel* reportModel;

  public slots:
    void ShowScreen();
    void CheckIn();
    void PendHouseInfo();
    void EnSureResInfo();
    void ChangeTransInfo();
};

#endif // SELLERSCREEN_H
