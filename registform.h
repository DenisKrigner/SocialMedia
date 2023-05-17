#ifndef REGISTFORM_H
#define REGISTFORM_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSql>
#include <QVBoxLayout>
#include <QDebug>
#include <QSqlRecord>
#include <QSqlError>
#include <QRandomGenerator>
#include <QMessageBox>



class RegistForm : public QWidget
{
    Q_OBJECT
public:
    explicit RegistForm(QWidget *parent = nullptr);

private slots:
    void registUser();

private:
    QLineEdit* name;
    QLineEdit* surfname;
    QLineEdit* password;
    QLineEdit* age;

    QString userLoginName;
    QString userPassword;
    int userAge;

    QPushButton* registButton;

    QSqlDatabase db;

    int port;

};

#endif // REGISTFORM_H
