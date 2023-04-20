#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QApplication>
#include <QDebug>
#include <QStyleFactory>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    filter = trUtf8("Text file (*.txt)");

    //fv = new FileViewer(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_openButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open", QDir::current().path(), filter);

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
    QString fileName = QFileDialog::getSaveFileName(this, "Save", QDir::current().path(), filter);

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
        QMessageBox::information(this, "Help", str);
    }
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    if (ui->checkBox->isChecked()) {
        ui->plainTextEdit->setReadOnly(true);
    } else {
        ui->plainTextEdit->setReadOnly(false);
    }
}

/*
 * 1. Добавить в текстовый редактор выбор из нескольких таблиц стилей.
 * Сделать темную и светлую тему.
*/

void MainWindow::on_styleButton_clicked()
{
    if (isLightTheme) {
        //QApplication::setStyle("Fusion");
        QFile style(":/styles/darkTheme.qss");
        style.open(QFile::ReadOnly);
        qApp->setStyleSheet(style.readAll());
        style.close();
        isLightTheme = false;
    } else {
        //QApplication::setStyle("windowsvista");
        QFile style(":/styles/aquaTheme.qss");
        style.open(QFile::ReadOnly);
        qApp->setStyleSheet(style.readAll());
        style.close();
        isLightTheme = true;
    }
    // qDebug() << QStyleFactory::keys() << " " << isLightTheme;
}

/*
 * 2. Перевести текстовый редактор на английский язык (названия кнопок из предыдущих заданий).
 * Добавить возможность динамически переключать языки во время работы приложения.
*/
void MainWindow::on_switchLangButton_clicked()
{
    QApplication::removeTranslator(translator);
    translator = new QTranslator(this);
    if (isRussian) {
        translator->load(":/tr/QtLanguage_en.qm");
        isRussian = false;
    } else {
        translator->load("ru");
        isRussian = true;
    }
    QApplication::installTranslator(translator);
}

void MainWindow::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange) {
        setWindowTitle(tr("Text Editor"));
        ui->openButton->setText(tr("Open"));
        ui->saveButton->setText(tr("Save"));
        ui->refButton->setText(tr("Help"));
        ui->styleButton->setText(tr("Change Style"));
        ui->switchLangButton->setText(tr("Change Language"));
        ui->checkBox->setText(tr("Read Only"));
    } else {
        QMainWindow::changeEvent(event);
    }
}

/*
 * 3. Добавить в текстовый редактор возможность пользоваться сочетаниями клавиш:
 * ctrl+o - открыть новый документ,
 * ctrl+s - сохранить как,
 * ctrl+n - создать новый документ,
 * ctrl+q - выход из программы.
*/

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->modifiers() & Qt::ControlModifier) {
        switch(event->key()) {
        case Qt::Key_O:
            on_openButton_clicked();
            break;
        case Qt::Key_S:
            on_saveButton_clicked();
            break;
        case Qt::Key_Q:
            QApplication::quit();
            break;
        case Qt::Key_N:
            on_saveButton_clicked();
            ui->plainTextEdit->clear();
            break;
        default:
            QWidget::keyReleaseEvent(event);
        }
    }
}


