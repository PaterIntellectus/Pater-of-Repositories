#ifndef SETTINGWINDOW_H
#define SETTINGWINDOW_H

#include <QDialog>
#include <QFile>
#include <QUrl>
#include <QMessageBox>

namespace Ui {
class SettingWindow;
}

class SettingWindow : public QDialog
{
    Q_OBJECT

public:
    SettingWindow(QSharedPointer<QUrl> _url, QWidget *parent = nullptr);
    ~SettingWindow();

private slots:
    void updateLines();
    // запоняет строки интерфейса строками из файла

    void updateFile();
    // запоняет строки файла строками из интерфейса

    void updateUrl();
    // обновляет параметры url

private:
    void showError(const QString& title, const QString& text);
    // показывает окно текстом

signals:
    void urlChanged();

private:
    void fileError(const QString &str);
    // выводит сообщение о проблемах с файлом

private:
    Ui::SettingWindow *ui;
    // объект GUI

    QFile urlDataFile;
    // объект файла

    QSharedPointer<QUrl> url;
    // объект веб-адреса

    QMessageBox *errorMessage;
    // окно для вывода ошибок
};

#endif // SETTINGWINDOW_H
