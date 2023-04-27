#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QSharedPointer>
#include "finder.h"

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = nullptr);
    ~Controller();
    void startSearch(QString dir, QString file);

signals:
    void changeSearchPath(QString);
    void genPathOfFile(QString);
    void newSearch();

public slots:
    void deleteThread();
    void printCurrentPath(QString);
    void genStringPathFile(QString);
    void finishThread();

private:
    QSharedPointer<Finder> finder;
    QString currentPath;
};

#endif // CONTROLLER_H
