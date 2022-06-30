#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "settingwindow.h"

MainWindow::MainWindow(const QString &fileName,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , manager{ new QNetworkAccessManager(this) }
    , settingsWindow{ new SettingWindow(fileName, this) }
    , errorMessage{ new QMessageBox(this) }
    , hostPort{ fileName }
{
    ui->setupUi(this);

    // просто наименования для окон
    errorMessage->setWindowTitle("Произошла Ошибочка :(");
    this->setWindowTitle("Request Manager");

    // связывание Сигналов со Слотами
    // клик на кнопку 'Настройки сервера' открывает окно настроек
    connect(ui->settingsBtn, &QPushButton::clicked, settingsWindow, &SettingWindow::show);
    // клик на кнопку 'Отправить' вызывает функцию SendRequest, отправляющую запрос
    connect(ui->sendBtn, &QPushButton::clicked, this, &MainWindow::sendRequest);
    // получение запроса вызывает функцию handleReply, обрабатывающую ответ
    connect(manager, &QNetworkAccessManager::finished, this, &MainWindow::handleReply);
}

MainWindow::~MainWindow()
{
    delete errorMessage;
    delete settingsWindow;
    delete manager;
    delete ui;
}

void MainWindow::sendRequest()
{
    if(!hostPort.open(QIODevice::ReadOnly))
    {
        errorMessage->setText("Невозможно открыть файл с данными сервера.");
        errorMessage->show();
        return;
    }
    // формирование аргументов для создания url
    QString host{ hostPort.readLine().trimmed() };
    QString port{ hostPort.readLine().trimmed() };
    hostPort.close();
    if (host.isEmpty() || port.isEmpty() || port.toInt() < 0)
    {
        errorMessage->setText(
                    "Имя хоста или порт не верны:"
                    "\nХост: " + host +
                    "\nПорт: " + port);
        errorMessage->show();
        return;
    }
    QString msg{ ui->inputCmd->text().trimmed() };
    if (msg.isEmpty())
    {
        errorMessage->setText("Вы пытаетесь отправить пустую команду.");
        errorMessage->show();
        return;
    }
    // формирование url
    setUrl("http", host, port, "msg", msg);

    // отправка запроса
    QNetworkRequest request{ url };
    manager->get(request);

}

void MainWindow::handleReply(QNetworkReply *reply)
{
    ui->displayCmd->setText(reply->readAll().trimmed());
}

void MainWindow::setUrl(const QString &scheme, const QString &host, const QString &port, const QString &key, const QString &value)
{
    url.setScheme(scheme);
    url.setHost(host);
    url.setPort(port.toInt());
    QUrlQuery query;
    query.addQueryItem(key, value);
    url.setQuery(query);
}
