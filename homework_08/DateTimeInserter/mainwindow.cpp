#include <QTextCursor>
#include <QDateTime>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QDateTime dateTime = QDateTime::currentDateTime();
    QString str = dateTime.toString("dd.MM.yyyy hh:mm");
    QTextCursor cursor(ui->plainTextEdit->textCursor());
    cursor.insertText(str);
}

