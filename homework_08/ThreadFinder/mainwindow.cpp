#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QFileDialog>
#include <QThread>
#include "mainwindow.h"
#include "finder.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    startingDir = new QLineEdit(qApp->applicationDirPath());
    fileToFind = new QLineEdit("");
    resultText = new QTextEdit;

    QLabel *dirLabel = new QLabel("Начальная папка для поиска");
    dirLabel->setBuddy(startingDir);
    QLabel *fileLabel = new QLabel("Введите имя файла");
    fileLabel->setBuddy(fileToFind);

    QPushButton *dirButton = new QPushButton("Выбрать папку");
    QPushButton *findButton = new QPushButton("Начать поиск");

    connect(dirButton, SIGNAL(clicked()), this, SLOT(browseDirs()));
    connect(findButton, SIGNAL(clicked()), this, SLOT(findFile()));

    QGridLayout *layout = new QGridLayout;
    layout->setContentsMargins(5, 5, 5, 5);
    layout->setSpacing(15);
    // filling row 0
    layout->addWidget(dirLabel, 0, 0);
    layout->addWidget(startingDir, 0, 1);
    layout->addWidget(dirButton, 0, 2);
    // filling row 1
    layout->addWidget(fileLabel, 1, 0);
    layout->addWidget(fileToFind, 1, 1);
    layout->addWidget(findButton, 1, 2);
    // filling row 2
    layout->addWidget(resultText, 2, 0, 1, 3);
    setLayout(layout);

    controller = new Controller();
    connect(controller, SIGNAL(genPathOfFile(QString)),
            this, SLOT(printFoundFile(QString)));
    connect(controller, SIGNAL(newSearch()), resultText, SLOT(clear()));

}

MainWindow::~MainWindow()
{
}

void MainWindow::browseDirs()
{
    QString path = QFileDialog::getExistingDirectory(0,
                                                     "Выберите папку для поиска",
                                                     startingDir->text());
    if (!path.isEmpty()) {
        startingDir->setText(path);
    }
}

void MainWindow::findFile()
{
    QString file = fileToFind->text();
    QString dir = startingDir->text();
    if (file.length() == 0 || dir.length() == 0) {
        return;
    }
    controller->startSearch(dir, file);
}

void MainWindow::printFoundFile(QString str)
{
    resultText->append(str);
}


