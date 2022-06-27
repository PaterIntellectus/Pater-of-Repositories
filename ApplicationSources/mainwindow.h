#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "settingwindow.h"
#include <QFile>
#include <QMessageBox>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(const QString& fileName = "HostPort", QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_sendBtn_clicked();

private:
    Ui::MainWindow *ui;
    QFile hostPort;
    QNetworkAccessManager* manager;
    SettingWindow *settingsWindow;
};
#endif // MAINWINDOW_H
