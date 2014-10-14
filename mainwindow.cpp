#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "list.h"
#include "cripter.h"
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit->setEchoMode(QLineEdit::Password);
    ui->lineEdit->setInputMethodHints(Qt::ImhHiddenText| Qt::ImhNoPredictiveText|Qt::ImhNoAutoUppercase);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::createTempFile() {
    QFile t1(qApp->applicationDirPath() + "/test.txt");
    QFile encryptedFile(qApp->applicationDirPath() + "/save.enc");

    CryptFileDevice cryptFileDevice(&encryptedFile,
                                    "01234567890123456789012345678901",
                                    "0123456789012345");
    if (!cryptFileDevice.open(QIODevice::WriteOnly | QIODevice::Truncate)){
        qDebug() << "File can't open";
        return;
    }
    if (!t1.open(QIODevice::ReadOnly | QIODevice::Truncate)){
        qDebug() << "File can't open";
        return;
    }
    QByteArray d = t1.readAll();
    qDebug() << d;
    cryptFileDevice.write(d);
    t1.close();
    cryptFileDevice.close();
}

//01234567890123456789012345678901
void MainWindow::on_pushButton_clicked()
{
    QFile encryptedFile(qApp->applicationDirPath() + "/save.enc");
    password.append(ui->lineEdit->text());
    CryptFileDevice cryptFileDevice(&encryptedFile, password, "0123456789012345");

    if(cryptFileDevice.isOpen()) cryptFileDevice.close();
    if (!cryptFileDevice.open(QIODevice::ReadWrite)) {
        qDebug() << "File can't open";
        return;
    }

    QByteArray decryptData = cryptFileDevice.readAll();
//    qDebug() << decryptData;
    if(decryptData.size()) {
        securityData = pars.parse_data(decryptData);
        qDebug() << securityData->getSite(1);
        delete securityData;
    }
    cryptFileDevice.close();
//    createTempFile();
}
