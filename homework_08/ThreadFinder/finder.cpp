#include <QDir>
#include "finder.h"

Finder::Finder(QString dir, QString file, QObject *parent) : QThread(parent)
{
    this->dir = dir;
    this->file = file;
    working = true;
}

void Finder::run()
{
    QStringList dirs = {dir};
    for (int i = 0; dirs.count() && working; ) {
        QDir search(dirs.at(i));
        emit writeFoundPath(dirs.at(i));

        search.setFilter(QDir::Hidden | QDir::Dirs | QDir::NoSymLinks);
        QStringList foundDirs = search.entryList();
        int amount = foundDirs.count();
        for (int j = 0; j < amount && working; ++j) {
            QString newPath = dirs.at(i) + foundDirs[j] + "/";
            if (newPath.indexOf("/.") == -1)
                dirs << newPath;
        }

        search.setFilter(QDir::Hidden | QDir::Files | QDir::NoSymLinks);
        QStringList foundFiles = search.entryList();
        amount = foundFiles.count();
        for (int j = 0; j < amount && working; ++j) {
            QString fileName = foundFiles.at(j);
            if (fileName.indexOf(file) != -1)
                emit nextFound(fileName);
        }
        dirs.removeAt(i);
    }
    emit threadStopped();
}


