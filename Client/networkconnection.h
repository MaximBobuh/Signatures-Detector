#ifndef NETWORKCONNECTION_H
#define NETWORKCONNECTION_H

#include <QObject>
#include <QTcpSocket>

class NetworkConnection : public QObject
{
    Q_OBJECT
public:
    NetworkConnection(const QString& strHost, int nPort);

    void SendToServer(const QString&);

private slots:
    void slotReadyRead ( );

signals:
    void signalReply(const QString&);

private:
    QTcpSocket* m_pTcpSocket;
    quint16 m_nNextBlockSize;
};

#endif // NETWORKCONNECTION_H
