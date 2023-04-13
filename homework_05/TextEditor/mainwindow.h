#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTranslator>
#include <QEvent>

#include "my_fileviewer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void on_openButton_clicked();

    void on_saveButton_clicked();

    void on_refButton_clicked();

    void on_checkBox_stateChanged(int arg1);

    void on_switchLangButton_clicked();

    void on_styleButton_clicked();

private:
    Ui::MainWindow *ui;
    QString filter;
    QTranslator *translator;
    bool isRussian = true;
    bool isLightTheme = true;
    void changeEvent(QEvent *event) override;
    FileViewer *fv;
};
#endif // MAINWINDOW_H
