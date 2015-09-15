#ifndef CLIENT_H
#define CLIENT_H

#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QProgressBar>
#include <QPushButton>

#include "networkconnection.h"


class QDir;

class Client : public QWidget
{
    Q_OBJECT
public:
    Client(QWidget* par = 0);

private:
    void start(const QDir&);

public slots:
    void slotBrowse();
    void slotScan();
    void slotProgress(){}
    void slotReply(const QString&);

signals:
    void sin(const QString&);

private:
    NetworkConnection connection;
    int count;

    QLineEdit dir;
    QTextEdit fileStatus;
    QProgressBar progress;
    QPushButton butScan;
};

#endif // CLIENT_H
