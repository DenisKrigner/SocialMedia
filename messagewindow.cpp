#include "messagewindow.h"

MessageWindow::MessageWindow(QWidget *parent) : QWidget(parent)
{
    QGridLayout* layout = new QGridLayout(this);

    chat =       new QTextBrowser(this);
    sendTo =        new QLineEdit(this);
    text =          new QLineEdit(this);
    send = new QPushButton("send",this);

    sendTo->setPlaceholderText("Send to:");
    text->setPlaceholderText("text:");

    layout->addWidget(chat,  0,0,3,5);
    layout->addWidget(sendTo,1,0,1,1);
    layout->addWidget(text,  2,0,1,1);
    layout->addWidget(send,  2,1,1,1);

    socket = new QTcpSocket;
    socket->connectToHost("127.0.0.1", 9001);

    connect(send,     SIGNAL(clicked()), this, SLOT(sendClicked()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(recieveMessage()));

}

void MessageWindow::upLoadInfo(QString name)
{
    userName = name;
}

void MessageWindow::registId()
{
    QJsonObject registedID;
    QString       tempName;
    QByteArray      byteID;

    QSqlQuery query(db);
    query.exec("SELECT login, port FROM UsersInfo");

    while(query.next())
    {
        tempName      = query.value(0).toString();
        int port         = query.value(1).toInt();

        if(userName == tempName)
        {
            registedID["ID"] = port;
            QJsonDocument jDocID(registedID);
            byteID = jDocID.toJson();
            socket->write(byteID);
        }
    }
}

void MessageWindow::recieveMessage()
{
    chat->setHtml(chat->toHtml().append("<br>").append(socket->readAll()));
}

void MessageWindow::sendClicked()
{
    QString clientName = sendTo->text();
    QString msg = text->text();
    QString tempName, senderName, recieverName;
    QJsonObject jsonMsg;
    QByteArray data;
    int tempPort;

    QDate date = QDate::currentDate();
    QTime time = QTime::currentTime();

    QString dateTime = date.toString("dd MMMM") + "." + time.toString("hh:mm") + " ";


    QSqlQuery query(db);
    query.exec("SELECT login, port FROM UsersInfo");

    while(query.next())
    {
        tempName = query.value(0).toString();
        tempPort = query.value(1).toInt();

        if(clientName == tempName)
        {
            recieverName = "<font color='%1'>%2</font>";
            recieverName = recieverName.arg("blue").arg(userName);
            chat->setHtml(chat->toHtml().append("<br>").append(recieverName + " " + dateTime)
                          .append("<br>").append(msg));

            recieverName = recieverName.arg("red").arg(userName);
            jsonMsg["msg"] = recieverName + " " + dateTime + "<br>" + msg;
            jsonMsg["to"]  = tempPort;
            QJsonDocument jDoc(jsonMsg);
            data = jDoc.toJson();
            socket->write(data);
        }
    }

    text->clear();
}
