#ifndef MESSAGEWINDOW_H
#define MESSAGEWINDOW_H

#include <QWidget>
#include <QGridLayout>
#include <QTextBrowser>
#include <QLineEdit>
#include <QPushButton>
#include <QTime>
#include <QDate>
#include <QDataStream>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSql>
#include <QSqlRecord>
#include <QSqlError>
#include <QDebug>
#include <QTcpSocket>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonObject>


class MessageWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MessageWindow(QWidget *parent = nullptr);

public slots:
    void upLoadInfo(QString);
    void registId();

private slots:
    void recieveMessage();
    void sendClicked();

private:
    QTextBrowser* chat;
    QLineEdit*  sendTo;
    QLineEdit*    text;
    QPushButton*  send;

    QString clientName;
    QString   userName;

    QSqlDatabase    db;

    QTcpSocket* socket;

};

#endif // MESSAGEWINDOW_H
