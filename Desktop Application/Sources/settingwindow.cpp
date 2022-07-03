#include "settingwindow.h"
#include "ui_settingwindow.h"

SettingWindow::SettingWindow(QSharedPointer<QUrl> _url, QWidget *parent)
      : QDialog(parent)
      , ui(new Ui::SettingWindow)
      , urlDataFile{ "UrlData" }
      , url{ _url }
      , errorMessage{ new QMessageBox(this) }
{
    ui->setupUi(this);
    this->setWindowTitle("Настройщик сети");

    // связывание Сигналов со Слотами (Фактически одна функция, вызывающая другую)
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &SettingWindow::urlChanged);
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &SettingWindow::close);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &SettingWindow::updateLines);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &SettingWindow::close);
    connect(this, &SettingWindow::urlChanged, &SettingWindow::updateUrl);
    connect(this, &SettingWindow::urlChanged, &SettingWindow::updateFile);

    if (!urlDataFile.size())
    {
        urlDataFile.open(QIODevice::WriteOnly);
        QTextStream toFile{ &urlDataFile };
        toFile << "localhost\n" << 8080;
        urlDataFile.close();
    }
    updateLines();
    updateUrl();
}

SettingWindow::~SettingWindow()
{
    delete ui;
}

void SettingWindow::updateLines()
{
    if (!urlDataFile.open(QIODevice::ReadOnly))
    {
        showError("Неверные данные",
                  "Файл не может быть открыт для Чтения");
        return;
    }

    ui->hostLine->setText(urlDataFile.readLine().trimmed());
    ui->portLine->setText(urlDataFile.readLine().trimmed());

    urlDataFile.close();
}

void SettingWindow::updateFile()
{
    if (!urlDataFile.open(QIODevice::WriteOnly))
    {
        showError("Проблемы с файлом",
                  "Файл не может быть открыт для Записи");
        return;
    }
    QTextStream toFile{ &urlDataFile };
    toFile << ui->hostLine->text().trimmed() + '\n'
           << ui->portLine->text().trimmed();
    urlDataFile.close();
}

void SettingWindow::updateUrl()
{
    QString host{ ui->hostLine->text().trimmed() };
    QString port{ ui->portLine->text().trimmed() };
    int i_port{ port.toInt() };
    if (host.isEmpty())
    {
        showError("Неверные данные",
                  "Хост не может быть пустым значеним");
        return;
    }
    if (port.isEmpty())
    {
        showError("Неверные данные",
                  "Порт не может пустым\n");
        return;
    }
    if (i_port < 0 || i_port > 65535)
    {
        showError("Неверные данные",
                  "Порт не может быть отрицательным\n"
                  "или превышать значение 65535\n"
                  "Порт: " + port);
        return;
    }
    url->setScheme("http");
    url->setHost(host);
    url->setPort(i_port);
}

void SettingWindow::showError(const QString &title, const QString &text)
{
    errorMessage->setWindowTitle(title);
    errorMessage->setText(text);
    errorMessage->show();
}
