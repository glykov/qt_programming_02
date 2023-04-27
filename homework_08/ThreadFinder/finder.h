#ifndef FINDER_H
#define FINDER_H

#include <QObject>
#include <QThread>

class Finder : public QThread
{
    Q_OBJECT
public:
    explicit Finder(QString dir, QString file, QObject *parent = nullptr);
    void stopSearch() {
        working = false;
    }

protected:
    void run() override;

signals:
    void nextFound(QString);
    void writeFoundPath(QString);
    void threadStopped();

private:
    QString dir;
    QString file;
    bool working;

};

#endif // FINDER_H
