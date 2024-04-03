#include "loginscreen.h"
#include "ui_loginscreen.h"

LoginScreen::LoginScreen(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::LoginScreen)
{
    ui->setupUi(this);

    connect(ui->BTN_Ensure, &QPushButton::clicked, this, [&]()
            {
                QString id = ui->LET_ID->text();
                QString password = ui->LET_Password->text();
                Users *users = Users::Instance();
                bool isLogin = users->Login(id, password);
                if(isLogin)
                {
                    if(id[0]=='1')
                        emit LoginScreen::adminChecked();
                    else if(id[0]=='2')
                        emit LoginScreen::sellerChecked();
                    else if(id[0]=='3')
                        emit LoginScreen::customChecked();
                    this->close();
                }
                else
                {
                    QMessageBox msgBox;
                    msgBox.setWindowTitle("错误提示");
                    msgBox.setText("账号或密码错误");
                    msgBox.exec();
                } });

    connect(ui->BTN_Register, &QPushButton::clicked, this, [&]()
            {
                emit LoginScreen::registered();
                this->close(); });
}

LoginScreen::~LoginScreen()
{
    delete ui;
}

void LoginScreen::ShowScreen()
{
    this->show();
}
