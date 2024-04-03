#ifndef LOGINSCREEN_H
#define LOGINSCREEN_H

#include "users.h"
#include <QMainWindow>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class LoginScreen;
}
QT_END_NAMESPACE

class LoginScreen : public QMainWindow
{
    Q_OBJECT

  public:
    LoginScreen(QWidget* parent = nullptr);
    ~LoginScreen();

  private:
    Ui::LoginScreen* ui;

  public slots:
    void ShowScreen();

  signals:
    emit void registered();
    emit void adminChecked();
    emit void customChecked();
    emit void sellerChecked();
};
#endif // LOGINSCREEN_H
