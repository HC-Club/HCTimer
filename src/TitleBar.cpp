#include "TitleBar.h"

TitleBar::TitleBar(QWidget *parent)
    : QWidget(parent)
{
    resize(652,64);

    //设置背景
    QPalette bgPalette;
    bgPalette.setColor(QPalette::Background, QColor(230,230,230));
    this->setPalette(bgPalette);
    this->setAutoFillBackground(true);

    initLayout();
}

void TitleBar::setUser(const User &user)
{
    nameLable->setText(user.getTrueName());
}

void TitleBar::setNoUser()
{
    nameLable->setText("请登录");
}

/**
 * @brief TitleBar::initLayout 初始化布局
 */
void TitleBar::initLayout()
{
    QFont ft;
    ft.setPixelSize(16);
    ft.setFamily("冬青黑体简体中文 W3");
    ft.setBold(true);
    nameLable = new QLabel(this);
    nameLable->setFont(ft);
    QPalette pa;
    pa.setColor(QPalette::WindowText,QColor(102,102,102));

    nameLable->setPalette(pa);
    nameLable->setText(tr("请登录"));
    nameLable->setGeometry(80,16,96,48);

    avatarImage = new QImage(48,48,QImage::Format_RGB32);//设置图片大小和图片类型
    avatarLabel = new QLabel(this);
    avatarLabel->setGeometry(16,16,48,48);

    avatarBtn = new QPushButton(this);
    avatarBtn->setIconSize(QSize(48,48));
    avatarBtn->setStyleSheet("background-color:none;border:none;");
    avatarBtn->setToolTip(tr("登录"));
    avatarBtn->setGeometry(16,16,48,48);

    if(avatarImage->load(":images/avatar.png")){
        avatarLabel->setPixmap(QPixmap::fromImage(*avatarImage));
    }
    else{
        avatarBtn->setIcon(QIcon(":images/avatar.png"));
    }

    //添加公告按钮控件
    btnAddNotice = new QPushButton(this);
    btnAddNotice->setFlat(true);
    btnAddNotice->setToolTip(tr("添加公告"));
    btnAddNotice->setStyleSheet("QPushButton{border-image: url(:images/btn_edit.png);}"
                               "QPushButton:hover{border-image: url(:images/btn_edit_hover.png);}"
                               "QPushButton:pressed{border-image: url(:images/btn_edit.png);}");
    btnAddNotice->setIconSize(QSize(32,32));
    btnAddNotice->setGeometry(464,16,32,32);
    btnAddNotice->hide();

    //查询成员具体时间按钮控件
    btnInquirySpecificTime = new QPushButton(this);
    btnInquirySpecificTime->setFlat(true);
    btnInquirySpecificTime->setToolTip(tr("查询具体时间"));
    btnInquirySpecificTime->setStyleSheet("QPushButton{border-image: url(:images/btn_search.png);}"
                               "QPushButton:hover{border-image: url(:images/btn_search_hover.png);}"
                               "QPushButton:pressed{border-image: url(:images/btn_search.png);}");
    btnInquirySpecificTime->setIconSize(QSize(32,32));
    btnInquirySpecificTime->setGeometry(464,16,32,32);
    btnInquirySpecificTime->hide();

    btnSettings = new QPushButton(this);
    btnSettings->setFlat(true);
    btnSettings->setToolTip(tr("设置"));
    btnSettings->setStyleSheet("QPushButton{border-image: url(:images/btn_setting.png);}"
                               "QPushButton:hover{border-image: url(:images/btn_setting_hover.png);}"
                               "QPushButton:pressed{border-image: url(:images/btn_setting.png);}");
    btnSettings->setIconSize(QSize(32,32));
    btnSettings->setGeometry(512,16,32,32);

    btnMinimize = new QPushButton(this);
    btnMinimize->setFlat(true);
    btnMinimize->setToolTip(tr("最小化"));
    btnMinimize->setStyleSheet("QPushButton{border-image: url(:images/btn_minimize.png);}"
                               "QPushButton:hover{border-image: url(:images/btn_minimize_hover.png);}"
                               "QPushButton:pressed{border-image: url(:images/btn_minimize.png);}");
    btnMinimize->setIconSize(QSize(32,32));
    btnMinimize->setGeometry(560,16,32,32);

    btnClose = new QPushButton(this);
    btnClose->setFlat(true);
    btnClose->setToolTip(tr("关闭"));
    btnClose->setStyleSheet("QPushButton{border-image: url(:images/btn_close.png);}"
                               "QPushButton:hover{border-image: url(:images/btn_close_hover.png);}"
                               "QPushButton:pressed{border-image: url(:images/btn_close.png);}");
    btnClose->setIconSize(QSize(32,32));
    btnClose->setGeometry(608,16,32,32);
}
