#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlRecord>
#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSql>
#include <QMessageBox>

#include "userpage.h"
#include "registform.h"

class UserPage;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
signals:
   void sendUserInfo(QString,int,int);
private slots:
    void on_registButton_clicked();

    void on_loginButton_clicked();

private:
    Ui::MainWindow *ui;
    RegistForm regist;
    UserPage user;


    // QWidget interface
protected:
    void keyPressEvent(QKeyEvent *event);
};
#endif // MAINWINDOW_H
