#include "customscreen.h"
#include "ui_customscreen.h"

CustomScreen::CustomScreen(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::CustomScreen)
{
    ui->setupUi(this);
    connect(ui->BTN_ReserveNext, &QPushButton::clicked, this, [&]()
            { ui->SWT_House->setCurrentIndex(1); });
    connect(ui->BTN_ReservePre, &QPushButton::clicked, this, [&]()
            { ui->SWT_House->setCurrentIndex(0); });
    connect(ui->BTN_SellEnsure, &QPushButton::clicked, this,
            &CustomScreen::AddHouseInfo);
    connect(ui->BTN_BuyEnsure, &QPushButton::clicked, this,
            &CustomScreen::BuyHouse);
    connect(ui->BTN_ReserveEnsure, &QPushButton::clicked, this,
            &CustomScreen::EnsureReserver);
}

CustomScreen::~CustomScreen()
{
    delete ui;
}

void CustomScreen::InitializeHouseInfo()
{
    houseModel = new QStandardItemModel();
    houseModel->setColumnCount(3);
    houseModel->setHeaderData(0, Qt::Horizontal, "房源ID");
    houseModel->setHeaderData(1, Qt::Horizontal, "位置");
    houseModel->setHeaderData(2, Qt::Horizontal, "价格");
    ui->TBW_HouseInfo->setModel(houseModel);
    ui->TBW_HouseInfo->horizontalHeader()->resizeSection(0, 150);
    ui->TBW_HouseInfo->horizontalHeader()->resizeSection(1, 300);
    ui->TBW_HouseInfo->horizontalHeader()->resizeSection(2, 150);

    HouseResource* house = HouseResource::Instance();
    QVector<QStringList> houseInfo = house->GetUploadHouseInfo();
    for (auto elem : houseInfo)
    {
        int count = houseModel->rowCount();
        houseModel->setItem(count, 0, new QStandardItem(elem[0]));
        houseModel->setItem(count, 1, new QStandardItem(elem[1]));
        houseModel->setItem(count, 2, new QStandardItem(elem[3]));
    }
}

void CustomScreen::InitializeThisUser()
{
    Users* users = Users::Instance();
    QStringList thisUser = users->GetThisUserInfo();
    ui->LBL_ID->setText("ID:" + thisUser[0]);
    ui->LBL_Name->setText("名字:" + thisUser[1]);
}

void CustomScreen::ShowScreen()
{
    InitializeThisUser();
    InitializeHouseInfo();
    this->show();
}

void CustomScreen::AddHouseInfo()
{
    QString id = ui->LET_SetID->text();
    QString pos = ui->LET_HousePos->text();
    QString price = ui->LET_HousePrice->text();
    bool isCan = true;

    HouseResource* house = HouseResource::Instance();
    QVector<QStringList> allHouseInfo = house->GetAllHouseInfo();

    for (auto elem : allHouseInfo)
    {
        if (elem[0] == id)
        {
            isCan = false;
            QMessageBox msgBox;
            msgBox.setWindowTitle("错误提示");
            msgBox.setText("ID已经存在");
            msgBox.exec();
        }
        if (elem[1] == pos)
        {
            isCan = false;
            QMessageBox msgBox;
            msgBox.setWindowTitle("错误提示");
            msgBox.setText("位置已经存在");
            msgBox.exec();
        }
    }
    if (isCan == true)
    {
        HouseResource* houseInfo = HouseResource::Instance();
        houseInfo->AddHouseResource(id, pos, price.toInt());
        QMessageBox msgBox;
        msgBox.setWindowTitle("提示");
        msgBox.setText("等待销售检查");
        msgBox.exec();
    }
}

void CustomScreen::BuyHouse()
{
    QString id = ui->LET_BuyHouse->text();
    HouseResource* house = HouseResource::Instance();
    QVector<QStringList> allHouseInfo = house->GetUploadHouseInfo();
    bool isCan = false;
    for (auto elem : allHouseInfo)
    {
        if (elem[0] == id)
        {
            isCan = true;
            break;
        }
    }
    if (isCan == true)
    {
        house->SetBuyHouseInfo(id);
        QMessageBox mgeBox;
        mgeBox.setWindowTitle("提示");
        mgeBox.setText("购买成功，请线下付款");
        mgeBox.exec();
    }
    else
    {
        QMessageBox mgeBox;
        mgeBox.setWindowTitle("提示");
        mgeBox.setText("房源ID不存在");
        mgeBox.exec();
    }
}

void CustomScreen::EnsureReserver()
{
    QString resID = ui->LET_ResID->text();
    QString houseID = ui->LET_SelectHouse->text();
    QString time = ui->DET_SelectTime->dateTime().toString("yyyy-MM-dd hh");

    bool isIdExist = false, isHouExist = false, isResExist = false;

    Reservation* resInfo = Reservation::Instance();
    isIdExist = resInfo->ExistID(resID);
    if (isIdExist == true)
    {
        QMessageBox mgeBox;
        mgeBox.setWindowTitle("提示");
        mgeBox.setText("预约ID已存在");
        mgeBox.exec();
    }

    HouseResource* houseInfo = HouseResource::Instance();
    isHouExist = houseInfo->ExistPending(houseID);
    if (isHouExist == false)
    {
        QMessageBox mgeBox;
        mgeBox.setWindowTitle("提示");
        mgeBox.setText("房源ID不存在");
        mgeBox.exec();
    }

    isResExist = resInfo->ExistPending(houseID, time);
    if (isResExist == true)
    {
        QMessageBox mgeBox;
        mgeBox.setWindowTitle("提示");
        mgeBox.setText("该时间已被预约");
        mgeBox.exec();
    }

    if (isIdExist == false && isHouExist == true && isResExist == false)
    {
        resInfo->AddReservation(resID, houseID, time);
        QMessageBox mgeBox;
        mgeBox.setWindowTitle("提示");
        mgeBox.setText("等待销售接受预约");
        mgeBox.exec();
    }
}
