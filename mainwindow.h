#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QtCore>
#include <QDebug>

#include <string.h>
#include <stdio.h>
#include "cripter.h"
#include "base64.h"
#include "parser.h"
#include "cryptfiledevice.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void createTempFile(void);
private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QByteArray password;
    cripter crypt;
    base64 base;
    parser pars;
    CryptFileDevice crypto;
    list * securityData;
};

#endif // MAINWINDOW_H
