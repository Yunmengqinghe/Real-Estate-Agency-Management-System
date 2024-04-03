#include "screenmanager.h"

#include <QApplication>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    ScreenManager w;
    return a.exec();
}
