#include "screenmanager.h"

ScreenManager::ScreenManager()
{
    LoginScreen* loginScreen = new LoginScreen();
    RegisterScreen* registerScreen = new RegisterScreen();
    AdminScreen* adminScreen = new AdminScreen();
    SellerScreen* sellerScreen = new SellerScreen();
    CustomScreen* customScreen = new CustomScreen();

    connect(loginScreen, &LoginScreen::registered,
            registerScreen, &RegisterScreen::ShowScreen);
    connect(loginScreen, &LoginScreen::adminChecked,
            adminScreen, &AdminScreen::ShowScreen);
    connect(loginScreen, &LoginScreen::sellerChecked,
            sellerScreen, &SellerScreen::ShowScreen);
    connect(loginScreen, &LoginScreen::customChecked,
            customScreen, &CustomScreen::ShowScreen);
    connect(registerScreen, &RegisterScreen::logined,
            loginScreen, &LoginScreen::ShowScreen);

    loginScreen->show();
}
