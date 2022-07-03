#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "settingwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , url{ new QUrl }
    , manager{ new QNetworkAccessManager(this) }
    , settingsWindow{ new SettingWindow(url, this) }
    , errorMessage{ new QMessageBox(this) }
{
    ui->setupUi(this);
    errorMessage->setWindowTitle("Произошла Ошибочка :(");
    this->setWindowTitle("Request Manager");

    // связывание Сигналов со Слотами (Фактически одна функция, вызывающая другую)
    connect(ui->sendBtn, &QPushButton::clicked, this, &MainWindow::queryChanged);
    connect(ui->sendBtn, &QPushButton::clicked, this, &MainWindow::sendRequest);
    connect(ui->settingsBtn, &QPushButton::clicked, settingsWindow, &SettingWindow::show);
    connect(manager, &QNetworkAccessManager::finished, this, &MainWindow::handleReply);
    connect(this, &MainWindow::queryChanged, &MainWindow::updateQuery);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sendRequest()
{
    if (ui->inputCmd->text().trimmed().isEmpty())
    {
        errorMessage->setWindowTitle("Проблема с запросом");
        errorMessage->setText("Нельзя отправить пустой запрос");
        errorMessage->show();
        return;
    }
    QNetworkRequest request{ *url };
    manager->get(request);
}

void MainWindow::handleReply(QNetworkReply *reply)
{
    ui->displayCmd->setText(reply->readAll().trimmed());
}

void MainWindow::updateQuery()
{
    QUrlQuery query;
    query.addQueryItem("msg", ui->inputCmd->text().trimmed());
    url->setQuery(query);
}
