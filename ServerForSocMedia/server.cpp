#include "server.h"
#include <QDebug>

Server::Server()
{
    m_server = new QTcpServer;

    if(m_server->listen(QHostAddress::Any, 9001))
        std::cout << "Server has started. port 9001"<< std::endl;
    else
        std::cout << "Server failed to start error: "
                  << m_server->errorString().toStdString() << std::endl;

    connect(m_server, SIGNAL(newConnection()), this, SLOT(incomingConnection()));
}

void Server::sendMessegaToClient(QString msg, int toID)
{
   if(m_clients_id.size() <= 0 || !m_clients_id.contains(toID)){
       std::cout << "invailed client ID" << std::endl;
       return;
   }

   auto *client = m_clients_id[toID];
   client->write(msg.toUtf8());
}

void Server::incomingConnection()
{
    QTcpSocket *client = m_server->nextPendingConnection();
    QString ipAdrr = client->peerAddress().toString();
    int port = client->peerPort();

    connect(client, &QTcpSocket::disconnected, this, &Server::socketDisconnected);
    connect(client, &QTcpSocket::readyRead   , this, &Server::ReadyRead);
    connect(client, &QTcpSocket::stateChanged, this, &Server::socketStateChanged);

    m_clients.push_back(client);

    std::cout << "Client was connected IP: "<< ipAdrr.toStdString() << "port: "
              << port << std::endl;
}

void Server::ReadyRead()
{
    QTcpSocket *client = qobject_cast<QTcpSocket*>(QObject::sender());
    QString ipAdrr     = client->peerAddress().toString();
    QString msg;
    int port           = client->peerPort();
    int toID;

    QByteArray data    = client->readAll();
    QJsonDocument jDoc = QJsonDocument::fromJson(data);
    QJsonObject   jObj = jDoc.object();

    if(jObj.contains("ID") && jObj["ID"].isDouble())
    {
        int id = jObj["ID"].toInt();
        m_clients_id[id] = client;
        std::cout << "new client registed id: " << id << std::endl;
    }else if(jObj.contains("msg") && jObj.contains("to")){
        msg  = jObj["msg"].toString();
        toID = jObj["to"].toInt();
        std::cout << "Client IP: " << ipAdrr.toStdString() << " port: " << port << " send message - " <<
                     msg.toStdString() << " to:" << toID << std::endl;

    sendMessegaToClient(msg, toID);
    }
}

void Server::socketDisconnected()
{
    QTcpSocket *client = qobject_cast<QTcpSocket*>(QObject::sender());
    QString ipAdrr     = client->peerAddress().toString();
    int port           = client->peerPort();

    std::cout << "Clent disconnected IP: " << ipAdrr.toStdString() << " port: " << port << std::endl;;
}

void Server::socketStateChanged(QAbstractSocket::SocketState state)
{
    QTcpSocket *client = qobject_cast<QTcpSocket*>(QObject::sender());
    QString ipAdrr     = client->peerAddress().toString();
    int port           = client->peerPort();
    QString desc;

    switch (state) {
    case QAbstractSocket::UnconnectedState:
        desc = "The socket is not connected.";
        break;
    case QAbstractSocket::HostLookupState:
        desc = "The socket is performing a host name lookup.";
        break;
    case QAbstractSocket::ConnectingState:
        desc = "The socket has started establishing a connection.";
        break;
    case QAbstractSocket::ConnectedState:
         desc = "A connection is established.";
        break;
    case QAbstractSocket::BoundState:
        desc = "The socket is bound to an address and port.";
        break;
    case QAbstractSocket::ClosingState:
        desc = "The socket is about to close (data may still be waiting to be written).";
        break;
    case QAbstractSocket::ListeningState:
        desc = "For internal use only.";
        break;
    }
    std::cout << "Client state changed (" << "IP: "<< ipAdrr.toStdString() <<" port: "<< port << " state: " <<desc.toStdString() << std::endl;
}



