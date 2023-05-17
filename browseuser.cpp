#include "browseuser.h"
#include <QDebug>

BrowseUser::BrowseUser(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout* vLayout       = new QVBoxLayout(this);
    QHBoxLayout* hTopLayout    = new QHBoxLayout(this);
    QHBoxLayout* hLayout       = new QHBoxLayout(this);
    QHBoxLayout* hStatusLayout = new QHBoxLayout(this);

    back_button       = new QPushButton(QIcon("C:/project/SocialMedia/img/backArrow.png"), "", this);
    user_name_label   = new QLabel(this);
    avatar            = new QLabel(this);
    status_label_pix  = new QLabel(this);
    status_label_text = new QLabel(this);
    about_user        = new QTextBrowser(this);
    add_friend        = new QPushButton(QIcon("C:/project/SocialMedia/img/addFriend.png"), "", this);
    send_message      = new QPushButton(QIcon("C:/project/SocialMedia/img/sendMessage.png"), "", this);
    // допилить user_info

    add_friend->setFixedSize       (60, 50);
    send_message->setFixedSize     (80, 50);
    status_label_pix->setFixedSize (80, 50);
    status_label_text->setFixedSize(80, 50);
    QFont font = user_name_label->font();
    font.setPointSize(18);
    user_name_label->setFont(font);
    font.setPointSize(12);
    about_user->setFont(font);
    status_label_text->setFont(font);

    hTopLayout->addWidget(avatar);
    hTopLayout->addWidget(about_user);

    hLayout->addWidget(add_friend);
    hLayout->addWidget(send_message);
    //hLayout->setAlignment(Qt::AlignLeft);

    hStatusLayout->addWidget(status_label_text);
    hStatusLayout->addWidget(status_label_pix);
    hStatusLayout->setAlignment(Qt::AlignRight);

    hLayout->addLayout(hStatusLayout);

    vLayout->addWidget(back_button, 0, Qt::AlignLeft);
    vLayout->addWidget(user_name_label, 0, Qt::AlignHCenter);
    vLayout->addLayout(hTopLayout);
    vLayout->addLayout(hLayout);
    vLayout->addSpacing(300);

    setLayout(vLayout);

    connect(back_button, &QPushButton::clicked, this, [this](){
        this->close();
    });

}

void BrowseUser::upLoadInfo(QString userName, QString userInfo, QString userAvatar, QString status)
{
    m_user_name  = userName;
    m_user_info  = userInfo;

    if(userAvatar == "nu"){
        m_user_avatar = "C:/project/SocialMedia/defaultAvatar.png";
    }else
        m_user_avatar = userAvatar;

    if(status == "ofline"){
        status_label_text->setText("ofline");
        status_label_pix->setPixmap(QPixmap("C:/project/SocialMedia/img/ofline.png"));
    }else{
        status_label_text->setText("online");
        status_label_pix->setPixmap(QPixmap("C:/project/SocialMedia/img/online.png"));
    }

    user_name_label->setText(m_user_name);
    avatar->setPixmap(QPixmap(m_user_avatar).scaled(250, 250, Qt::KeepAspectRatio));
    about_user->setHtml(m_user_info);
}
