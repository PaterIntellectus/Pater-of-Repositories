#ifndef SETTINGWINDOW_H
#define SETTINGWINDOW_H

#include <QDialog>
#include <QFile>
#include <QMessageBox>

namespace Ui {
class SettingWindow;
}

class SettingWindow : public QDialog
{
    Q_OBJECT

public:
    SettingWindow(const QString &fileName, QWidget *parent = nullptr);
    ~SettingWindow();

private:
    // выводит сообщение о проблемах с файлом
    void fileError();

private slots:
    // запоняет строки интерфейса из файла
    bool fillLines();
    // наполняет файл строками из интерфейса
    // (я бы просто выставил дефолтные аргументы
    // но аргументы типа ui->hostLine->text() нельзя использовать до создания оюъекта GUI)
    bool fillFileByLines();
    // делает то же, что и предыдущая функция, но с аргументами
    bool fillFile(const QString &host, const QString &port);

private:
    // объект GUI
    Ui::SettingWindow *ui;
    // объект файла
    QFile hostPort;

};

#endif // SETTINGWINDOW_H
