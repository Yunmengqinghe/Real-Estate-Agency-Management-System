#include "sellerscreen.h"
#include "ui_sellerscreen.h"

#include <QMessageBox>

SellerScreen::SellerScreen(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::SellerScreen)
{
    ui->setupUi(this);

    connect(ui->BTN_HouseNext, &QPushButton::clicked, this, [&]()
            { ui->SWT_MgeHouse->setCurrentIndex(1); });
    connect(ui->BTN_HousePre, &QPushButton::clicked, this, [&]()
            { ui->SWT_MgeHouse->setCurrentIndex(0); });
    connect(ui->BTN_ResNext, &QPushButton::clicked, this, [&]()
            { ui->SWT_ResMgr->setCurrentIndex(1); });
    connect(ui->BTN_ResPre, &QPushButton::clicked, this, [&]()
            { ui->SWT_ResMgr->setCurrentIndex(0); });
    connect(ui->BTN_TranNext, &QPushButton::clicked, this, [&]()
            { ui->SWT_TranInfo->setCurrentIndex(1); });
    connect(ui->BTN_TranPre, &QPushButton::clicked, this, [&]()
            { ui->SWT_TranInfo->setCurrentIndex(0); });
    connect(ui->BTN_CheckIn, &QPushButton::clicked, this, &SellerScreen::CheckIn);
    connect(ui->BTN_PendSure, &QPushButton::clicked, this, &SellerScreen::PendHouseInfo);
    connect(ui->BTN_ResEnsure, &QPushButton::clicked, this, &SellerScreen::EnSureResInfo);
    connect(ui->BTN_TranEnsure, &QPushButton::clicked, this, &SellerScreen::ChangeTransInfo);
}

SellerScreen::~SellerScreen()
{
    delete ui;
}

void SellerScreen::InitializeReportInfo()
{
    reportModel = new QStandardItemModel(this);
    reportModel->setColumnCount(4);
    reportModel->setHeaderData(0, Qt::Horizontal, "ID");
    reportModel->setHeaderData(1, Qt::Horizontal, "CUSTOM_ID");
    reportModel->setHeaderData(2, Qt::Horizontal, "PRICE");
    reportModel->setHeaderData(3, Qt::Horizontal, "STAGE");
    ui->TBW_ReportInfo->setModel(reportModel);
    ui->TBW_ReportInfo->horizontalHeader()->resizeSection(0, 100);
    ui->TBW_ReportInfo->horizontalHeader()->resizeSection(0, 100);
    ui->TBW_ReportInfo->horizontalHeader()->resizeSection(0, 100);
    ui->TBW_ReportInfo->horizontalHeader()->resizeSection(0, 100);

    Transaction* trans = Transaction::Instance();
    QVector<QStringList> endTransInfo = trans->GetEndTransInfo();
    for (auto elem : endTransInfo)
    {
        int count = reportModel->rowCount();
        reportModel->setItem(count, 0, new QStandardItem(elem[0]));
        reportModel->setItem(count, 1, new QStandardItem(elem[1]));
        reportModel->setItem(count, 2, new QStandardItem(elem[3]));
        reportModel->setItem(count, 3, new QStandardItem(elem[4]));
    }
}

void SellerScreen::InitializeTransInfo()
{
    unTransModel = new QStandardItemModel(this);
    unTransModel->setColumnCount(5);
    unTransModel->setHeaderData(0, Qt::Horizontal, "ID");
    unTransModel->setHeaderData(1, Qt::Horizontal, "客户ID");
    unTransModel->setHeaderData(2, Qt::Horizontal, "房屋ID");
    unTransModel->setHeaderData(3, Qt::Horizontal, "价格");
    unTransModel->setHeaderData(4, Qt::Horizontal, "阶段");
    ui->TBW_TranInfo->setModel(unTransModel);
    ui->TBW_TranInfo->horizontalHeader()->resizeSection(0, 100);
    ui->TBW_TranInfo->horizontalHeader()->resizeSection(1, 100);
    ui->TBW_TranInfo->horizontalHeader()->resizeSection(2, 100);
    ui->TBW_TranInfo->horizontalHeader()->resizeSection(3, 150);
    ui->TBW_TranInfo->horizontalHeader()->resizeSection(4, 150);

    Transaction* trans = Transaction::Instance();
    QVector<QStringList> unTransInfo = trans->GetUnTransInfo();
    Users* user = Users::Instance();
    QStringList thisUser = user->GetThisUserInfo();
    for (auto elem : unTransInfo)
    {
        if (elem[2] == thisUser[0])
        {
            int count = unTransModel->rowCount();
            unTransModel->setItem(count, 0, new QStandardItem(elem[0]));
            unTransModel->setItem(count, 1, new QStandardItem(elem[1]));
            unTransModel->setItem(count, 2, new QStandardItem(elem[3]));
            unTransModel->setItem(count, 3, new QStandardItem(elem[4]));
            unTransModel->setItem(count, 4, new QStandardItem(elem[5]));
        }
    }
}

void SellerScreen::InitialzeResInfo()
{
    resInfoModel = new QStandardItemModel(this);
    resInfoModel->setColumnCount(4);
    resInfoModel->setHeaderData(0, Qt::Horizontal, "ID");
    resInfoModel->setHeaderData(1, Qt::Horizontal, "客户ID");
    resInfoModel->setHeaderData(2, Qt::Horizontal, "房屋ID");
    resInfoModel->setHeaderData(3, Qt::Horizontal, "时间");
    ui->TBW_Reserve->setModel(resInfoModel);
    ui->TBW_Reserve->horizontalHeader()->resizeSection(0, 100);
    ui->TBW_Reserve->horizontalHeader()->resizeSection(1, 150);
    ui->TBW_Reserve->horizontalHeader()->resizeSection(2, 150);
    ui->TBW_Reserve->horizontalHeader()->resizeSection(3, 200);

    Reservation* res = Reservation::Instance();
    QVector<QStringList> resInfo = res->GetUnCheckResInfo();
    for (auto elem : resInfo)
    {
        int count = resInfoModel->rowCount();
        resInfoModel->setItem(count, 0, new QStandardItem(elem[0]));
        resInfoModel->setItem(count, 1, new QStandardItem(elem[1]));
        resInfoModel->setItem(count, 2, new QStandardItem(elem[3]));
        resInfoModel->setItem(count, 3, new QStandardItem(elem[4]));
    }
}

void SellerScreen::InitialzeHouseInfo()
{
    houseInfoModel = new QStandardItemModel(this);
    houseInfoModel->setColumnCount(4);
    houseInfoModel->setHeaderData(0, Qt::Horizontal, "房源ID");
    houseInfoModel->setHeaderData(1, Qt::Horizontal, "位置");
    houseInfoModel->setHeaderData(2, Qt::Horizontal, "客户ID");
    houseInfoModel->setHeaderData(3, Qt::Horizontal, "价格");
    ui->TBW_HouseInfo->setModel(houseInfoModel);
    ui->TBW_HouseInfo->horizontalHeader()->resizeSection(0, 100);
    ui->TBW_HouseInfo->horizontalHeader()->resizeSection(1, 250);
    ui->TBW_HouseInfo->horizontalHeader()->resizeSection(2, 100);
    ui->TBW_HouseInfo->horizontalHeader()->resizeSection(3, 150);

    HouseResource* house = HouseResource::Instance();
    QVector<QStringList> houseInfo = house->GetCheckHouseInfo();
    for (auto elem : houseInfo)
    {
        int count = houseInfoModel->rowCount();
        houseInfoModel->setItem(count, 0, new QStandardItem(elem[0]));
        houseInfoModel->setItem(count, 1, new QStandardItem(elem[1]));
        houseInfoModel->setItem(count, 2, new QStandardItem(elem[2]));
        houseInfoModel->setItem(count, 3, new QStandardItem(elem[3]));
    }
}

void SellerScreen::InitializeWageInfo()
{
    wageInfoModel = new QStandardItemModel(this);
    wageInfoModel->setColumnCount(4);
    wageInfoModel->setHeaderData(0, Qt::Horizontal, "ID");
    wageInfoModel->setHeaderData(1, Qt::Horizontal, "月份");
    wageInfoModel->setHeaderData(2, Qt::Horizontal, "基本工资");
    wageInfoModel->setHeaderData(3, Qt::Horizontal, "奖金");
    ui->TBW_WageInfo->setModel(wageInfoModel);
    ui->TBW_WageInfo->horizontalHeader()->resizeSection(0, 100);
    ui->TBW_WageInfo->horizontalHeader()->resizeSection(1, 100);
    ui->TBW_WageInfo->horizontalHeader()->resizeSection(2, 100);
    ui->TBW_WageInfo->horizontalHeader()->resizeSection(2, 100);

    Wage* userWage = Wage::Instance();
    QVector<QStringList> wageInfo = userWage->GetWageInfo();
    for (auto elem : wageInfo)
    {
        int count = wageInfoModel->rowCount();
        wageInfoModel->setItem(count, 0, new QStandardItem(elem[0]));
        wageInfoModel->setItem(count, 1, new QStandardItem(elem[1]));
        wageInfoModel->setItem(count, 2, new QStandardItem(elem[2]));
        wageInfoModel->setItem(count, 3, new QStandardItem(elem[3]));
    }
}

void SellerScreen::InitializeThisUser()
{
    Users* users = Users::Instance();
    QStringList thisUser = users->GetThisUserInfo();
    ui->LBL_ID->setText("ID:" + thisUser[0]);
    ui->LBL_Name->setText("名字:" + thisUser[1]);
}

void SellerScreen::ShowScreen()
{
    InitializeThisUser();
    InitializeReportInfo();
    InitializeTransInfo();
    InitialzeResInfo();
    InitializeWageInfo();
    InitialzeHouseInfo();
    this->show();
}

void SellerScreen::CheckIn()
{
    CheckInInfo* info = CheckInInfo::Instance();
    QDateTime checkInTime = QDateTime::currentDateTime();
    QString time = checkInTime.toString("yyyy-MM-dd hh:mm");
    QTime timeHMS = checkInTime.time();
    bool isLate = info->LatePending(timeHMS);
    info->CheckIn(time, isLate);
    QMessageBox mgeBox;
    mgeBox.setWindowTitle("提示");
    mgeBox.setText("签到成功");
    mgeBox.exec();
}

void SellerScreen::PendHouseInfo()
{
    QString id = ui->LET_SelectHouID->text();
    bool isPend = ui->CBX_Pend->isChecked();
    HouseResource* houseinfo = HouseResource::Instance();
    if (isPend == true)
        houseinfo->SetCheckHouseInfo(id, 1);
    else
        houseinfo->SetCheckHouseInfo(id, -1);
    QMessageBox mgeBox;
    mgeBox.setWindowTitle("提示");
    mgeBox.setText("信息将在重新登录后刷新");
    mgeBox.exec();
}

void SellerScreen::EnSureResInfo()
{
    QString id = ui->LET_ResID->text();
    Reservation* res = Reservation::Instance();
    QVector<QStringList> resInfo = res->GetUnCheckResInfo();
    bool isCan = false;
    for (auto elem : resInfo)
    {
        if (id == elem[0])
        {
            isCan = true;
            break;
        }
    }
    if (isCan == false)
    {
        QMessageBox mgeBox;
        mgeBox.setWindowTitle("提示");
        mgeBox.setText("ID不存在");
        mgeBox.exec();
    }
    else
    {
        res->UpdateResInfo(id);
        QMessageBox mgeBox;
        mgeBox.setWindowTitle("提示");
        mgeBox.setText("确认成功");
        mgeBox.exec();
    }
}

void SellerScreen::ChangeTransInfo()
{
    QString id = ui->LET_TranID->text();
    int stage = ui->SBX_TranSection->value();
    Transaction* trans = Transaction::Instance();
    bool isCan = trans->SetTransInfo(id, stage);
    if (isCan == false)
    {
        QMessageBox mgeBox;
        mgeBox.setWindowTitle("提示");
        mgeBox.setText("ID不存在");
        mgeBox.exec();
    }
    else
    {
        QMessageBox mgeBox;
        mgeBox.setWindowTitle("提示");
        mgeBox.setText("更改成功");
        mgeBox.exec();
    }
}
