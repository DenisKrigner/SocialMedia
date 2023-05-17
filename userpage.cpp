#include "userpage.h"

#include <QDebug>

UserPage::UserPage(QWidget *parent) :
     QWidget(parent)
{

    QVBoxLayout* layout     = new QVBoxLayout(this);
    QHBoxLayout* hLayout    = new QHBoxLayout(this);
    QHBoxLayout* hTopLayout = new QHBoxLayout(this);
    QPixmap defaultPix("C:/project/SocialMedia/defaultAvatar.png");

    userName    = new QLabel(this);
    avatar      = new QLabel(this);
    aboutUser   = new QTextBrowser(this);
    chngAvatar  = new QPushButton("Change Avatar", this);
    send        = new QPushButton(QIcon("C:/project/SocialMedia/img/sendMessage.png"), "", this);
    userInfo    = new QPlainTextEdit(this);
    findUserLe  = new QLineEdit(this);
    findUserBut = new QPushButton(QIcon("C:/project/SocialMedia/img/findUserBut.png"),"",this);

    userInfo->setPlaceholderText("About yourself");
    userName->setAlignment (Qt::AlignHCenter | Qt::AlignTop);
    QFont font = userName->font();
    font.setPointSize(18);
    userName->setFont(font);
    userName->resize(20,20);
    avatar->resize(250,250);
    int w = avatar->width();
    int h = avatar->height();
    avatar->setPixmap(defaultPix.scaled(w,h,Qt::KeepAspectRatio));
    chngAvatar->resize(110,40);
    send->setFixedSize(110,40);
    userInfo->resize(75,40);
    findUserLe->setPlaceholderText("Find user");

    hTopLayout->addWidget(findUserLe);
    hTopLayout->addWidget(findUserBut);

    hLayout->addWidget(avatar);
    hLayout->addWidget(aboutUser);

    layout->addLayout(hTopLayout);
    layout->addWidget(userName);
    layout->addLayout(hLayout);
    layout->addWidget(chngAvatar);
    layout->setAlignment(chngAvatar,Qt::AlignLeft);
    layout->addWidget(send);
    layout->setAlignment(send,Qt::AlignLeft);
    layout->addWidget(userInfo);
    layout->addSpacing(300);

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("RegistInfo.db");
    if(!db.open()) qDebug() << db.lastError().text();

    setLayout(layout);

    connect(chngAvatar,  SIGNAL(clicked()),         this, SLOT(changeAvatar()));
    connect(send,        SIGNAL(clicked()),         this, SLOT(sendMessage()));
    connect(findUserBut, SIGNAL(clicked()),         this, SLOT(findUser()));
    connect(this,        SIGNAL(sendInfo(QString)), &mw,  SLOT(upLoadInfo(QString)));

    connect(this, SIGNAL(findUserUploadInfo(QString, QString, QString, QString)), &bu,
            SLOT(upLoadInfo(QString, QString, QString, QString)));
}

UserPage::~UserPage()
{
    QSqlQuery query(db);
    if(!query.exec(QString("UPDATE UsersInfo SET status='%1' WHERE login='%2'").arg("ofline").arg(usrName)))
        qDebug() << db.lastError().text();
}



void UserPage::upLoad(QString name, int age, int port)
{
    m_age = age;
    m_port = port;
    usrName = name;
    userName->setText(name);

    QString info = "<p style='font-size: %1;'>%2</p>";
    info         = info.arg(30).arg("Age:" + QString::number(m_age) + "<br>");
    aboutUser->setHtml(info);

    if(!db.open()) qDebug() << db.lastError().text();
   QSqlQuery query(db);
   if(!query.exec("SELECT login, avatar FROM UsersInfo")) qDebug() << db.lastError();

   while(query.next())
   {
       QString tempName = query.value(0).toString();

       if(usrName == tempName)
       {
           QString tempAvatar = query.value(1).toString();
            if(tempAvatar != "nu")
            {
                int w = 250;
                int h = 250;

                QPixmap newAvatar(tempAvatar);
                avatar->setPixmap(newAvatar.scaled(w, h, Qt::KeepAspectRatio));
            }
       }
   }

   if(!query.exec(QString("UPDATE UsersInfo SET status='%1' WHERE login='%2'").arg("online").arg(usrName)))
       qDebug() << db.lastError().text();

    emit sendInfo(usrName);
    mw.registId();
    qDebug() << port << age;
}

void UserPage::changeAvatar()
{
    QString path = QFileDialog::getOpenFileName(this, "set your avatar",
                                                    "./",
                                                    "Images (*.png)");

    if(!db.open()) qDebug() << db.lastError().text();
    QSqlQuery query(db);
    if(!query.exec(QString("UPDATE UsersInfo SET avatar='%1' WHERE login='%2'").arg(path).arg(usrName)))
        qDebug() << db.lastError().text();

    int w = avatar->width();
    int h = avatar->height();

    QPixmap newAvatar(path);
    avatar->setPixmap(newAvatar.scaled(w,h,Qt::KeepAspectRatio));
}

void UserPage::sendMessage()
{
    mw.setFixedSize(350,400);
    mw.setWindowTitle("send message");
    mw.show();
}

void UserPage::findUser()
{
   QString user = findUserLe->text();
   QString tempUser;
   QString tempAge;
   QString tempAvatar;
   QString tempStatus;

   if(user == ""){
       QMessageBox::warning(this, "", "search user field is empty");
       return;
   }
   if(user == usrName){
       QMessageBox::warning(this, "", "Can`t browse your own page");
       return;
   }

   if(!db.open()) qDebug() << db.lastError().text();
   QSqlQuery query(db);
   if(!query.exec("SELECT login, age, avatar, status FROM UsersInfo"))
       qDebug() << db.lastError().text();
   while(query.next())
   {
       tempUser = query.value(0).toString();
       if(user == tempUser)
       {
           tempAge    = query.value(1).toString();
           tempAvatar = query.value(2).toString();
           tempStatus = query.value(3).toString();

           tempAge = "Age: " + tempAge + "<br>";

           emit findUserUploadInfo(tempUser, tempAge, tempAvatar, tempStatus);

           bu.resize(700, 700);
           bu.setWindowModality(Qt::ApplicationModal);
           bu.show();
       }
   }
}


