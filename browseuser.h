#ifndef BROWSEUSER_H
#define BROWSEUSER_H

#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QTextBrowser>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFont>
#include <QPushButton>

class BrowseUser : public QWidget
{
    Q_OBJECT
public:
    explicit BrowseUser(QWidget *parent = nullptr);

public slots:
    void upLoadInfo(QString, QString, QString, QString);

private:
    QPushButton*  back_button;
    QPushButton*   add_friend;
    QPushButton* send_message;
    QLabel*            avatar;
    QLabel*  status_label_pix;
    QLabel* status_label_text;
    QLabel*   user_name_label;
    QTextBrowser*  about_user;
    QTextBrowser*   user_info;

    QString   m_user_name;
    QString   m_user_info;
    QString m_user_avatar;
};

#endif // BROWSEUSER_H
