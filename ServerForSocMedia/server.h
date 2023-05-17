#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>
#include <QDataStream>
#include <QMap>
#include <iostream>
#include <string>
#include <QJsonDocument>
#include <QJsonObject>

class Server : public QObject
{
    Q_OBJECT
public:
    Server();

    void sendMessegaToClient(QString, int);

public slots:
    void incomingConnection();
    void ReadyRead();
    void socketDisconnected();
    void socketStateChanged(QAbstractSocket::SocketState);

private:
    QVector<QTcpSocket*>      m_clients;
    QTcpServer                *m_server;
    QMap<int, QTcpSocket*> m_clients_id;
};

#endif // SERVER_H
