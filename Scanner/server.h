#ifndef SERVER_H
#define SERVER_H

#include <QObject>

#include "scanner.h"

class QTcpServer;
class QTextEdit;
class QTcpSocket;


class Server : QObject
{
    Q_OBJECT
private:
    QTcpServer* m_ptcpServer;
    quint16 m_nNextBlockSize;
    Scanner scanner;

private:
    void sendToClient(QTcpSocket* pSocket, const QString& str);

public:
    Server(int);

public slots:
     void slotNewConnection();
     void slotReadClient ();
};

#endif // SERVER_H
