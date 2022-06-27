#ifndef SETTINGWINDOW_H
#define SETTINGWINDOW_H

#include <QDialog>
#include <QFile>


namespace Ui {
class SettingWindow;
}

class SettingWindow : public QDialog
{
    Q_OBJECT

public:
    SettingWindow(const QString& fileName, QWidget *parent = nullptr);
    ~SettingWindow();

private slots:
    bool fillLines();
    bool fillFileByLines();
    bool fillFile(const QString& host, const QString& port);

signals:


private:
    Ui::SettingWindow *ui;
    QFile hostPort;

};

#endif // SETTINGWINDOW_H
