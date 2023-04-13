#ifndef FILEVIEWERWIDGET_H
#define FILEVIEWERWIDGET_H

#include <QWidget>
#include <QFileSystemModel>
#include <QDir>

QT_BEGIN_NAMESPACE
namespace Ui { class FileViewerWidget; }
QT_END_NAMESPACE

class FileViewerWidget : public QWidget
{
    Q_OBJECT

public:
    FileViewerWidget(QWidget *parent = nullptr);
    ~FileViewerWidget();

private slots:
    void on_listView_doubleClicked(const QModelIndex &index);

private:
    Ui::FileViewerWidget *ui;
    QFileSystemModel *model;
};
#endif // FILEVIEWERWIDGET_H
