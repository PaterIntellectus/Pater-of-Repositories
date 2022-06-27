#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "settingwindow.h"

MainWindow::MainWindow(const QString& fileName,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , hostPort{ fileName }
    , manager{ new QNetworkAccessManager(this) }
    , settingsWindow{ new SettingWindow(fileName, this) }
{
    ui->setupUi(this);
    this->setWindowTitle("Отправка и получение HTTP запросов");
    connect(ui->settingsBtn, &QPushButton::clicked, settingsWindow, &SettingWindow::show);
    connect(manager, &QNetworkAccessManager::finished, this, &MainWindow::handleReply);
}
MainWindow::~MainWindow()
{
    delete manager;
    delete settingsWindow;
    delete ui;
}

void MainWindow::on_sendBtn_clicked()
{
    if(!hostPort.open(QIODevice::ReadOnly))
    {
        qInfo() << "Can't open a file";
        return;
    }
    QTextStream fromFile(&hostPort);
    QString host;
    qint16 port;
    fromFile >> host;
    fromFile >> port;
    hostPort.close();
    if (host.isEmpty() || port < 0)
    {
        QString message{ "Имя хоста или порт не верны:" "\nХост: " + host + "\nПорт: " + port};
        QMessageBox* messageBox{ new QMessageBox(this) };
        messageBox->setText(message);
        messageBox->show();
        return;
    }
    QString msg{ ui->inputCmd->text().trimmed() };
    if (msg.isEmpty())
    {
        qInfo() << "Nothing to send";
        return;
    }

    QUrl url;
    url.setScheme("http");
    url.setHost(host);
    url.setPort(port);
    QUrlQuery query;
    query.addQueryItem("msg", msg);
    url.setQuery(query);
    QNetworkRequest request{ url };
    manager->get(request);
}
void MainWindow::handleReply(QNetworkReply *reply)
{
    ui->displayCmd->setText(reply->readAll());
}
