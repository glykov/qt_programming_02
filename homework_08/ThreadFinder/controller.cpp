#include "controller.h"

Controller::Controller(QObject *parent) : QObject(parent)
{

}

Controller::~Controller()
{
    if (finder != nullptr) {
        if (finder->isRunning()) {
            finder->stopSearch();
            finder->terminate();
        }
        finder.reset();
    }
}

void Controller::startSearch(QString dir, QString file)
{
    if (finder.get()) {
        finder->stopSearch();
        finder->terminate();
        finder.reset();
        return;
    }

    finder = QSharedPointer<Finder>::create(dir, file);
    finder->start();
    connect(finder.get(), SIGNAL(threadStopped()), this, SLOT(deleteThread()));
    connect(finder.get(), SIGNAL(writeFoundPath(QString)),
            this, SLOT(printCurrentPath(QString)));
    connect(finder.get(), SIGNAL(nextFound(QString)),
            this, SLOT(genStringPathFile(QString)));
    emit newSearch();
}

void Controller::deleteThread()
{
    finder.reset();
}

void Controller::printCurrentPath(QString path)
{
    currentPath = path;
    emit changeSearchPath(path);
}

void Controller::genStringPathFile(QString file)
{
    QString str = currentPath + file;
    emit genPathOfFile(str);
}

void Controller::finishThread()
{
    emit changeSearchPath("Поиск завершен");
}
