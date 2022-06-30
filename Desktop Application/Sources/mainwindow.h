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
    Q_OBJECT // даёт возможность объекту иметь Сигналы и Слоты то есть,
             // связывать действия пользователя с внутренним функционалом

public:
    MainWindow(const QString &fileName = "HostPort", QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // отправка запроса
    void sendRequest();
    // обработка ответа
    void handleReply(QNetworkReply *reply);
    // формирование url
    void setUrl(const QString &scheme,
                const QString &host, const QString &port,
                const QString &key,  const QString &value);

private:
    // объект GUI
    Ui::MainWindow *ui;
    // менеджер запросов, отправляет и принимает
    QNetworkAccessManager *manager;
    // окно настроек
    SettingWindow *settingsWindow;
    // окно для вывода ошибок
    QMessageBox *errorMessage;

    // объект файла
    QFile hostPort;
    // объект веб-адреса
    QUrl url{};
};
#endif // MAINWINDOW_H
