#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "settingwindow.h"
#include <QFile>
#include <QMessageBox>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QUrlQuery>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(const QString &fileName = "HostPort", QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_sendBtn_clicked();

    void handleReply(QNetworkReply *reply);

    void setUrl(const QString &scheme,
                const QString &host, const QString &port,
                const QString &key,  const QString &value);

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *manager;
    SettingWindow *settingsWindow;
    QMessageBox *errorMessage;

    QFile hostPort;
    QUrl url{};
};
#endif // MAINWINDOW_H
