#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDir>
#include <QTextStream>
#include <QDebug>

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
    QString contents;
    QString fileName = QFileDialog::getOpenFileName(this, "Открыть",
                                                    QDir::current().path(),
                                                    "Веб-страницы (*.html)");
    if (fileName.length() > 0) {
        QFile fin(fileName);
        if (fin.open(QFile::ReadOnly | QFile::ExistingOnly)) {
            QTextStream stream(&fin);
            stream.setCodec("UTF-8");
            contents = stream.readAll();
            ui->plainTextEdit->setPlainText(contents);
            fin.close();
        }
    }

    QStringList data = getData(contents);

    ui->weatherLineEdit->setText(data[0]);
    ui->usdLineEdit->setText(data[1]);
    ui->euroLineEdit->setText(data[2]);
}

QStringList MainWindow::getData(const QString &html)
{
    QStringList data;
    QRegExp weatherRegexp("(<span class=\"temp bckelgg__fxeidd\" data-testid=\"weather-temp\">)([+-]?([1-9]\\d*|0)\\W*)(</span>)");
    int pos = weatherRegexp.indexIn(html, 0);
    data.append(weatherRegexp.cap(2));
    QRegExp currencyRegexp("(<div class=\"rate__currency bckelgg__dz16t5\">)(\\d{1,3},\\d{0,2})(</div>)");
    while ((pos = currencyRegexp.indexIn(html, pos)) != -1) {
        pos += currencyRegexp.matchedLength();
        data.append(currencyRegexp.cap(2));
    }
    return data;
}

