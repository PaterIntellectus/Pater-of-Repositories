#include "settingwindow.h"
#include "ui_settingwindow.h"

SettingWindow::SettingWindow(const QString &fileName, QWidget *parent)
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
        fileError(hostPort.fileName());
        return false;
    }
    ui->hostLine->setText(hostPort.readLine().trimmed());
    ui->portLine->setText(hostPort.readLine().trimmed());
    hostPort.close();
    return true;
}

bool SettingWindow::fillFileByLines() // СУЩЕСТВУЕТ ТОЛЬКО ЛИШЬ ДЛЯ ПРИВЯЗКИ К СИГНАЛУ
{
    if (!hostPort.open(QIODevice::WriteOnly))
    {
        fileError(hostPort.fileName());
        return false;
    }
    QTextStream toFile{ &hostPort };
    toFile << ui->hostLine->text().trimmed() + '\n'
           << ui->portLine->text().trimmed();
    hostPort.close();
    return true;
}

bool SettingWindow::fillFile(const QString& host, const QString& port)
{
    if (!hostPort.open(QIODevice::WriteOnly))
    {
        fileError(hostPort.fileName());
        return false;
    }
    QTextStream toFile{ &hostPort };
    toFile << host.trimmed() + '\n'
           << port.trimmed();
    hostPort.close();
    return true;
}

void SettingWindow::fileError(const QString &fileName)
{
    QMessageBox *error{ new QMessageBox(this) };
    error->setWindowTitle("Что-то с файлом");
    error->setText("Файл " + fileName + " не может быть открыт или прочтён, проверьте его наличие в файле с приложением");
    error->show();
}
