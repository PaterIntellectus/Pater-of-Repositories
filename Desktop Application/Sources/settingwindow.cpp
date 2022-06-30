#include "settingwindow.h"
#include "ui_settingwindow.h"

SettingWindow::SettingWindow(const QString &fileName, QWidget *parent)
      : QDialog(parent)
      , ui(new Ui::SettingWindow)
      , hostPort{ fileName }
{
    // формирование GUI из файлов .ui
    ui->setupUi(this);

    // именование окна
    this->setWindowTitle("Настройщик сети");

    // если файл не существует, то будет создан
    if (!hostPort.size())
    {
        fillFile("localhost", "8080");
    }
    // взятие строк из файла для заполнения строкинтерфейса
    fillLines();

    // связывание Сигналов со Слотами
    // кнопка Принятия заполняет файл новыми значениями, и закрывает окно настроек
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &SettingWindow::fillFileByLines);
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &SettingWindow::close);
    // кнопка Отмены заполняет поля старыми значениями из файла, и закрывает окно настроек
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &SettingWindow::fillLines);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &SettingWindow::close);
    // окно продолжает существовать после закрытия,
    // ведь на него есть указатель в MainWindow,
    // поэтому перезапись значений в полях имеет значение
}

SettingWindow::~SettingWindow()
{
    delete ui;
}

bool SettingWindow::fillLines()
{
    if (!hostPort.open(QIODevice::ReadOnly))
    {
        fileError();
        return false;
    }
    // перезапись осуществляется только если строки были изменены
    QString host{ hostPort.readLine().trimmed() };
    if(host != ui->hostLine->text().trimmed())
    {
        ui->hostLine->setText(host);
    }
    QString port{ hostPort.readLine().trimmed() };
    if(port != ui->portLine->text().trimmed())
    {
        ui->portLine->setText(port);
    }
    hostPort.close();
    return true;
}

bool SettingWindow::fillFileByLines() // СУЩЕСТВУЕТ ТОЛЬКО ЛИШЬ ДЛЯ ПРИВЯЗКИ К СИГНАЛУ
{
    return fillFile(ui->hostLine->text(), ui->portLine->text());
}

bool SettingWindow::fillFile(const QString& host, const QString& port)
{
    if (!hostPort.open(QIODevice::WriteOnly))
    {
        fileError();
        return false;
    }
    // поток необходим для записи В файл
    QTextStream toFile{ &hostPort };
    toFile << host.trimmed() + '\n'
           << port.trimmed();
    hostPort.close();
    return true;
}

void SettingWindow::fileError()
{
    QMessageBox *error{ new QMessageBox(this) };
    error->setWindowTitle("Что-то с файлом");
    error->setText("Файл " + hostPort.fileName() + " не может быть открыт или прочтён,\n"
                   "проверьте его наличие в папке с приложением");
    error->show();
}
