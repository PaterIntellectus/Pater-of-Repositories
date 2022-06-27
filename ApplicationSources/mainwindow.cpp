#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "settingwindow.h"

MainWindow::MainWindow(const QString& fileName,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , hostPort{ fileName }
    , settingsWindow{ new SettingWindow(fileName) }
    , manager{ new QNetworkAccessManager(this) }
{
    ui->setupUi(this);
    this->setWindowTitle("Отправка и получение HTTP запросов");
    connect(ui->settingsBtn, &QPushButton::clicked, settingsWindow, &SettingWindow::show);

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
    int port;
    fromFile >> host;
    fromFile >> port;
    hostPort.close();
    manager->connectToHost(host, port);
    QNetworkRequest request{ QUrl("http://" + host + "/index.php?msg=" + ui->inputCmd->text()) };
    manager->get(request);
}
