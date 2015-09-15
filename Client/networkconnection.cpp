#include "networkconnection.h"


NetworkConnection::NetworkConnection(const QString& strHost, int nPort) : m_nNextBlockSize(0)
{
    m_pTcpSocket = new QTcpSocket(this);
    m_pTcpSocket->connectToHost(strHost, nPort);

    connect(m_pTcpSocket, SIGNAL(readyRead()), SLOT(slotReadyRead()));
}

void NetworkConnection::slotReadyRead()
{
    QDataStream in(m_pTcpSocket);
    in.setVersion(QDataStream::Qt_5_4);

    for (;;)
    {
        if (!m_nNextBlockSize)
        {
            if (m_pTcpSocket->bytesAvailable() < sizeof(quint16))
                break;
            in >> m_nNextBlockSize;
        }
        if (m_pTcpSocket->bytesAvailable() < m_nNextBlockSize)
            break;

        QString str = "";
        in >> str;
        emit signalReply(str);

        m_nNextBlockSize = 0;
    }

}

void NetworkConnection::SendToServer(const QString& str)
{
    QByteArray arr;
    QDataStream data(&arr, QIODevice::WriteOnly);
    data.setVersion(QDataStream::Qt_5_1);

    data << qint16(0) << str;

    data.device()->seek(0);

    data << qint16(arr.size() - sizeof(qint16));

    m_pTcpSocket->write(arr);
    m_pTcpSocket->flush();
}


