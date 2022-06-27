#include "settingwindow.h"
#include "ui_settingwindow.h"

SettingWindow::SettingWindow(const QString& fileName, QWidget *parent)
      : QDialog(parent)
      , ui(new Ui::SettingWindow)
      , hostPort{ fileName }
{
    ui->setupUi(this);
    this->setWindowTitle("Настройщик сети");

    if (!hostPort.size())
    {
        fillFile("localhost", "8080");
    }
    fillLines();

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &SettingWindow::fillFileByLines);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &SettingWindow::fillLines);
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &SettingWindow::close);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &SettingWindow::close);
}
SettingWindow::~SettingWindow()
{
    delete ui;
}

bool SettingWindow::fillLines()
{
    if (!hostPort.open(QIODevice::ReadOnly))
    {
        qInfo() << "Something went wrong: Can't open the file" << hostPort.fileName();
        return false;
    }
    QTextStream fromFile{ &hostPort };
    QString host;
    QString port;
    fromFile >> host;
    fromFile >> port;
    ui->hostLine->setText(host);
    ui->portLine->setText(port);
    hostPort.close();
    return true;
}

bool SettingWindow::fillFileByLines()
{
    if (!hostPort.open(QIODevice::WriteOnly))
    {
        qInfo() << "Something went wrong: Can't open the file" << hostPort.fileName();
        return false;
    }
    QTextStream toFile{ &hostPort };
    toFile << ui->hostLine->text() + '\n'
           << ui->portLine->text();
    hostPort.close();
    return true;
}
bool SettingWindow::fillFile(const QString& host, const QString& port)
{
    if (!hostPort.open(QIODevice::WriteOnly))
    {
        qInfo() << "Something went wrong: Can't open the file" << hostPort.fileName();
        return false;
    }
    QTextStream toFile{ &hostPort };
    toFile << host + '\n'
           << port;
    hostPort.close();
    return true;
}
