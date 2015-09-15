#include <QTcpServer>
#include <QTcpSocket>
#include <QCoreApplication>

#include "server.h"
#include "scanner.h"

extern QString fileName; //dictionary's path

//----------------------------------------------

Server::Server(int nPort) :  m_nNextBlockSize(0), scanner(fileName)
{
    m_ptcpServer = new QTcpServer(this);

    if (!m_ptcpServer->listen(QHostAddress::Any, nPort))
    {
        m_ptcpServer->close();
        return;
    }
    connect(m_ptcpServer, SIGNAL(newConnection()), this, SLOT(slotNewConnection()));
}

//----------------------------------------------

void Server::slotNewConnection()
{
    QTcpSocket* pClientSocket = m_ptcpServer->nextPendingConnection();
    connect(pClientSocket, SIGNAL(disconnected()), pClientSocket, SLOT(deleteLater()) );
    connect(pClientSocket, SIGNAL(readyRead()), this, SLOT(slotReadClient()));
}

//----------------------------------------------

void Server::slotReadClient()
{
    QTcpSocket* pClientSocket = (QTcpSocket*)sender();

    QDataStream data(pClientSocket);
    data.setVersion(QDataStream::Qt_5_4);

    QString buf;
    qint16 nextBlockSize = 0;

    for(;;)
    {
        if(!nextBlockSize)
        {
            if(pClientSocket->bytesAvailable() < sizeof(qint16))
                break;

            data >> nextBlockSize;
        }
        if(pClientSocket->bytesAvailable() < nextBlockSize)
            break;

        data >> buf;
        if(!buf.isEmpty())
            sendToClient(pClientSocket, scanner.scanFile(buf));

        nextBlockSize = 0;
    }
}

//---------------------------------------------------------------

void Server::sendToClient(QTcpSocket* pSocket, const QString& str)
{
    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_4);
    out << quint16(0) << str;
    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));

    pSocket->write(arrBlock);
    pSocket->flush();
}
