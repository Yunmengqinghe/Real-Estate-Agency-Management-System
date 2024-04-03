#include "adminscreen.h"
#include "ui_adminscreen.h"

AdminScreen::AdminScreen(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::AdminScreen)
{
    ui->setupUi(this);
    connect(ui->BTN_Next, &QPushButton::clicked, this, [&]()
            { ui->SWT_Perfomance->setCurrentIndex(1); });
    connect(ui->BTN_ReturnPerfo, &QPushButton::clicked, this, [&]()
            { ui->SWT_Perfomance->setCurrentIndex(0); });
    connect(ui->BTN_WageEnsure, &QPushButton::clicked, this, &AdminScreen::SetWage);
    connect(ui->BTN_LineEnsure, &QPushButton::clicked, this, &AdminScreen::InitializeTransInfo);
}

AdminScreen::~AdminScreen()
{
    delete ui;
}

void AdminScreen::InitializeInfo()
{
    infoModel = new QStandardItemModel(this);
    infoModel->setColumnCount(3);
    infoModel->setHeaderData(0, Qt::Horizontal, "ID");
    infoModel->setHeaderData(1, Qt::Horizontal, "姓名");
    infoModel->setHeaderData(2, Qt::Horizontal, "电话");
    ui->TBW_Info->setModel(infoModel);
    ui->TBW_Info->horizontalHeader()->resizeSection(0, 200);
    ui->TBW_Info->horizontalHeader()->resizeSection(1, 200);
    ui->TBW_Info->horizontalHeader()->resizeSection(2, 200);

    Users* users = Users::Instance();
    QVector<QStringList> usersInfo = users->GetSellerInfo();
    for (auto elem : usersInfo)
    {
        int count = infoModel->rowCount();
        infoModel->setItem(count, 0, new QStandardItem(elem[0]));
        infoModel->setItem(count, 1, new QStandardItem(elem[1]));
        infoModel->setItem(count, 2, new QStandardItem(elem[2]));
    }
}

void AdminScreen::InitializePerformance()
{
    performanceModel = new QStandardItemModel(this);
    performanceModel->setColumnCount(2);
    performanceModel->setHeaderData(0, Qt::Horizontal, "ID");
    performanceModel->setHeaderData(1, Qt::Horizontal, "业绩");
    ui->TBW_Performance->setModel(performanceModel);
    ui->TBW_Performance->horizontalHeader()->resizeSection(0, 300);
    ui->TBW_Performance->horizontalHeader()->resizeSection(1, 300);
}

void AdminScreen::InitializeThisUser()
{
    Users* users = Users::Instance();
    QStringList thisUser = users->GetThisUserInfo();
    ui->LBL_ID->setText("ID:" + thisUser[0]);
    ui->LBL_Name->setText("名字:" + thisUser[1]);
}

void AdminScreen::ShowScreen()
{
    InitializeThisUser();
    InitializeInfo();
    InitializePerformance();
    this->show();
}

void AdminScreen::SetWage()
{
    Wage* wageMgr = Wage::Instance();
    wageMgr->SetWageInfo(ui->LET_BaseWage->text().toInt(),
                         ui->LET_Bonus->text().toInt(),
                         ui->SBX_Time->text().toInt());
    QMessageBox mgeBox;
    mgeBox.setWindowTitle("提示");
    mgeBox.setText("设置成功");
    mgeBox.exec();
}

void AdminScreen::InitializeTransInfo()
{
    int line = ui->LET_SetLine->text().toInt();

    Transaction* trans = Transaction::Instance();
    QVector<QStringList> transInfo = trans->GetEndTransInfo();
    QMap<QString, int> transRank;
    for (auto elem : transInfo)
    {
        if (transRank.contains(elem[2]) == false)
        {
            transRank.insert(elem[2], 1);
        }
        else
        {
            transRank[elem[2]]++;
        }
    }

    for (auto it1 = transRank.begin(); it1 != transRank.end(); it1++)
    {
        auto maxIt = it1;
        for (auto it2 = transRank.begin(); it2 != transRank.end(); it2++)
        {
            if (it2.value() >= maxIt.value())
            {
                maxIt = it2;
            }
        }
        if (maxIt.value() >= line)
        {
            int count = performanceModel->rowCount();
            QString val = QString::number(maxIt.value());
            performanceModel->setItem(count, 0, new QStandardItem(maxIt.key()));
            performanceModel->setItem(count, 1, new QStandardItem(val));
            transRank.remove(maxIt.key());
        }
        else
            break;
    }
}
