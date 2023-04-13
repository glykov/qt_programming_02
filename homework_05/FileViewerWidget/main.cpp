#include "fileviewerwidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FileViewerWidget w;
    w.show();
    return a.exec();
}
