#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include "controller.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void browseDirs();
    void findFile();
    void printFoundFile(QString);

private:
    Controller *controller;
    QLineEdit *startingDir;
    QLineEdit *fileToFind;
    QTextEdit *resultText;

};
#endif // MAINWINDOW_H
