#ifndef REGISTERSCREEN_H
#define REGISTERSCREEN_H

#include "users.h"
#include <QMainWindow>

namespace Ui
{
    class RegisterScreen;
}

class RegisterScreen : public QMainWindow
{
    Q_OBJECT

  public:
    explicit RegisterScreen(QWidget* parent = nullptr);
    ~RegisterScreen();

  private:
    Ui::RegisterScreen* ui;

  public slots:
    void ShowScreen();

  signals:
    emit void logined();
};

#endif // REGISTERSCREEN_H
