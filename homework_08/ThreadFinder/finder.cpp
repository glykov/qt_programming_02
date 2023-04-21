#include <QDir>
#include "finder.h"

Finder::Finder(QObject *parent) : QObject(parent)
{

}

void Finder::find(QString path, QString fileToFind)
{
    QDir dir(path);
    QStringList listFiles = dir.entryList(QDir::Files);

    foreach(QString fileName, listFiles) {
        if (fileName.contains(fileToFind)) emit nextFound(fileName);
    }

    QStringList listDirs = dir.entryList(QDir::Dirs);
    foreach(QString subdir, listDirs) {
        if (subdir == "." || subdir == "..") {
            continue;
        }
        find(dir.absoluteFilePath(subdir), fileToFind);
    }

}
