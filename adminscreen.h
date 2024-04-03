#ifndef ADMINSCREEN_H
#define ADMINSCREEN_H

#include "transaction.h"
#include "users.h"
#include "wage.h"
#include <QMainWindow>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QString>
#include <QStringList>
#include <QVector>
#include <algorithm>
#include <map>

namespace Ui
{
    class AdminScreen;
}

class AdminScreen : public QMainWindow
{
    Q_OBJECT

  public:
    explicit AdminScreen(QWidget* parent = nullptr);
    ~AdminScreen();
    void InitializeInfo();
    void InitializePerformance();
    void InitializeThisUser();

  private:
    Ui::AdminScreen* ui;
    QStandardItemModel *infoModel, *performanceModel;

  public slots:
    void ShowScreen();
    void SetWage();
    void InitializeTransInfo();
};
#endif // ADMINSCREEN_H
