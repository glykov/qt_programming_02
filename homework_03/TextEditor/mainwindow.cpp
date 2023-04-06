#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    filter = trUtf8("Текстовый файл (*.txt)");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_openButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Открыть", QDir::current().path(), filter);

    if (fileName.length() > 0) {
        int index = fileName.indexOf(".txt");

        if (index != -1 && fileName.length() - 4 == index) {
            QFile fin(fileName);
            if (fin.open(QFile::ReadOnly | QFile::ExistingOnly)) {
                QTextStream stream(&fin);
                stream.setCodec("UTF-8");
                ui->plainTextEdit->setPlainText(stream.readAll());
                fin.close();
            }
        }
    }
}


void MainWindow::on_saveButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Сохранить", QDir::current().path(), filter);

    if (fileName.length() > 0) {
        QString ext = QString(&(fileName.data()[fileName.length() - 4]));
        if (ext == ".txt") {
            QFile fout(fileName);
            if (fout.open(QFile::WriteOnly | QFile::NewOnly)) {
                QTextStream stream(&fout);
                stream.setCodec("UTF-8");
                stream << ui->plainTextEdit->toPlainText();
                fout.close();
            }
        }
    }
}


void MainWindow::on_refButton_clicked()
{
    QFile helpFile(":/help/help.txt");
    if (helpFile.open(QIODevice::ReadOnly)) {
        QTextStream stream(&helpFile);
        stream.setCodec("UTF-8");
        QString str = stream.readAll();
        QMessageBox::information(this, "Справка", str);
    }
}

