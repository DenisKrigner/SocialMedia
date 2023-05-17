#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    connect(this,SIGNAL(sendUserInfo(QString,int,int)), &user, SLOT(upLoad(QString,int,int)));

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_registButton_clicked()
{
    regist.setFixedSize(300,300);
    regist.setWindowTitle("Regist form");
    regist.show();

}


void MainWindow::on_loginButton_clicked()
{
    QString leLogin = ui->loginEdit->text();
    QString lePassword = ui->passwordEdit->text();

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("RegistInfo.db");
    if(!db.open()) qDebug() <<db.lastError().text();

    QSqlQuery query(db);
    query.exec("SELECT login, password, age, port FROM UsersInfo");

    while(query.next())
    {
        QString tempName = query.value(0).toString();
        QString tempPassword = query.value(1).toString();
        int tempAge = query.value(2).toInt();
        int tempPort = query.value(3).toInt();

        if(tempName == leLogin && tempPassword == lePassword)
        {
            emit sendUserInfo(tempName,tempAge,tempPort);

            user.resize(700,700);
            user.setWindowTitle(tempName + " Page");
            user.show();

            this->hide();
            qDebug() << tempName << tempPassword;

            break;
        }else{
            QMessageBox::warning(this,"warning","wrong login or password !");}
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
        this->on_loginButton_clicked();
}

