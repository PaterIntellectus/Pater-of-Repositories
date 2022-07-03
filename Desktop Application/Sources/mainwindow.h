#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUrl>
#include <QUrlQuery>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include "settingwindow.h"
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void sendRequest();
    // отправляет запрос

    void handleReply(QNetworkReply *reply);
    // обрабатывает ответ

    void updateQuery();
    // обновляет запрос

signals:
    void queryChanged();

private:
    Ui::MainWindow *ui;
    // объект GUI

    QSharedPointer<QUrl> url;
    // объект веб-адреса

    QNetworkAccessManager *manager;
    // менеджер запросов, отправляет и принимает

    SettingWindow *settingsWindow;
    // окно настроек

    QMessageBox *errorMessage;
    // окно для вывода ошибок
};

#endif // MAINWINDOW_H
