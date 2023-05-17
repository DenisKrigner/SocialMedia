#ifndef USERPAGE_H
#define USERPAGE_H

#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QPushButton>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFont>
#include <QFileDialog>
#include <QSqlRecord>
#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSql>

#include "messagewindow.h"
#include "browseuser.h"

class UserPage : public QWidget
{
    Q_OBJECT
public:
    UserPage(QWidget *parent = nullptr);
    ~UserPage();

signals:
    void sendInfo(QString);
    void findUserUploadInfo(QString, QString, QString, QString);

public slots:
    void upLoad(QString,int,int);

private slots:
    void changeAvatar();
    void sendMessage();
    void findUser();

private:

    QLabel*         userName;
    QLabel*           avatar;
    QPushButton*  chngAvatar;
    QPushButton*        send;
    QPlainTextEdit* userInfo;
    QTextBrowser*  aboutUser;
    QLineEdit*    findUserLe;
    QPushButton* findUserBut;

    QString usrName;

    int m_age;
    int m_port;

    MessageWindow mw;
    BrowseUser    bu;
    QSqlDatabase  db;
};

#endif // USERPAGE_H
