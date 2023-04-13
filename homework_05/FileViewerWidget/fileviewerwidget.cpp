#include "fileviewerwidget.h"
#include "ui_fileviewerwidget.h"

FileViewerWidget::FileViewerWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::FileViewerWidget)
{
    ui->setupUi(this);

    model = new QFileSystemModel(this);
    model->setFilter(QDir::AllEntries);
    model->setRootPath("");

    ui->listView->setModel(model);
}

FileViewerWidget::~FileViewerWidget()
{
    delete ui;
}


void FileViewerWidget::on_listView_doubleClicked(const QModelIndex &index)
{
    QString path;
    QFileInfo fileInfo = model->fileInfo(index);
    if (fileInfo.fileName() == "..") {
        QDir dir = fileInfo.dir();
        dir.cdUp();
        path = dir.absolutePath();
        ui->listView->setRootIndex(model->index(path));
        ui->lineEdit->setText(path);
    } else if (fileInfo.fileName() == ".") {
        path = "";
        ui->listView->setRootIndex(model->index(path));
        ui->lineEdit->setText(path);
    } else if (fileInfo.isDir()) {
        path = fileInfo.absolutePath();
        ui->listView->setRootIndex(index);
        ui->lineEdit->setText(path);
    }
}

