#include "registform.h"

#include <cstdlib>


RegistForm::RegistForm(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout* layout = new QVBoxLayout(this);

    name         = new QLineEdit(this);
    surfname     = new QLineEdit(this);
    password     = new QLineEdit(this);
    age          = new QLineEdit(this);
    registButton = new QPushButton("Regist",this);

    name->setPlaceholderText("Name");
    surfname->setPlaceholderText("Surfname");
    password->setPlaceholderText("password");
    password->setEchoMode(QLineEdit::Password);
    age->setPlaceholderText("age");



    layout->addWidget(name);
    layout->addWidget(surfname);
    layout->addWidget(password);
    layout->addWidget(age);
    layout->addWidget(registButton);

    setLayout(layout);

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("RegistInfo.db");
    if(!db.open()) qDebug() << db.lastError().text();

    connect(registButton,SIGNAL(clicked()),this,SLOT(registUser()));

}

void RegistForm::registUser()
{
    QSqlQuery query(db);

    std::random_device random_device;
    std::mt19937 generator(random_device());

    std::uniform_int_distribution<> distribution(10, 65000);

    port = distribution(generator);

    userLoginName = name->text() + " " + surfname->text();
    userPassword = password->text();
    userAge = age->text().toInt();


    if(!query.exec("CREATE TABLE UsersInfo("
                   "login VARCHAR(200),"
                   "password VARCHAR(200),"
                   "age INT(120),"
                   "port INT(120),"
                   "avatar VARCHAR(2000),"
                   "status VARCHAR(200)"
                   ")"
                   )){
        qDebug() << db.lastError().text();
    }

    query.prepare(
                "INSERT INTO UsersInfo(login,password,age,port,avatar,status)"
                " VALUES(:login,:password,:age,:port,:avatar,:status)"
                );

    query.bindValue(":login", userLoginName);
    query.bindValue(":password",userPassword);
    query.bindValue(":age", userAge);
    query.bindValue(":port", port);
    query.bindValue(":avatar", "nu" );
    query.bindValue(":status", "ofline");

    if(!query.exec()) qDebug() << db.lastError().text();

    if(!query.exec("SELECT * FROM UsersInfo")) qDebug() << db.lastError().text();

    if(name->text() == "" || surfname->text() == "")
    {
        QMessageBox::warning(this,"warning","login name field is empty");
        return;
    }else if(userPassword == "")
    {
        QMessageBox::warning(this,"warning","passwod is emprty");
        return;
    }else if(!userAge)
    {
        QMessageBox::warning(this,"warning","age field is empty");
        return;
    }else{
        QMessageBox::information(this, "", "you are successfully registed");
        name->clear(); surfname->clear(); password->clear(); age->clear();
        this->hide();
    }
}

