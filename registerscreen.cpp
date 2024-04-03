#include "registerscreen.h"
#include "ui_registerscreen.h"

RegisterScreen::RegisterScreen(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::RegisterScreen)
{
    ui->setupUi(this);
    connect(ui->BTN_Ensure, &QPushButton::clicked, this, [&]()
            {
                Users* users = Users::Instance();
                QStringList userInfo;
                QString type= QString::number(ui->CBX_Type->currentIndex() + 1);
                userInfo.append(type + ui->LET_ID->text());
                userInfo.append(ui->LET_Name->text());
                userInfo.append(ui->LET_Phone->text());
                userInfo.append(ui->LET_Password->text());
                qDebug() << users->Register(userInfo);
                emit logined();
                this->close(); });
}

RegisterScreen::~RegisterScreen()
{
    delete ui;
}

void RegisterScreen::ShowScreen()
{
    this->show();
}
