#include "NoticeWindow.h"

NoticeWindow::NoticeWindow(QWidget *parent) : QWidget(parent)
{
    initLayout();
    noticesSwitchAnimation = new QPropertyAnimation(noticeWidget,"geometry");
    resize(652,320);
}

void NoticeWindow::initLayout()
{
    //背景设置
    QPalette bgPalette;
    bgPalette.setColor(QPalette::Background, QColor(230,230,230));
    this->setPalette(bgPalette);
    this->setAutoFillBackground(true);

    noticeWidget = new NoticeWidget(this);
    noticeWidget->move(0,0);

    backBtn = new QPushButton(this);
    backBtn->setIcon(QIcon(":images/btn_back.png"));
    backBtn->setIconSize(QSize(32,32));
    backBtn->setStyleSheet("border:none");
    backBtn->setToolTip("后退");
    backBtn->resize(32,32);
    backBtn->move(6,128);
    connect(backBtn, SIGNAL(clicked()),
            this, SLOT(slotBackSwitch()));

    forwardBtn = new QPushButton(this);
    forwardBtn->setIcon(QIcon(":images/btn_forward.png"));
    forwardBtn->setIconSize(QSize(32,32));
    forwardBtn->setStyleSheet("border:none");
    forwardBtn->setToolTip("前进");
    forwardBtn->resize(32,32);
    forwardBtn->move(616,128);
    connect(forwardBtn, SIGNAL(clicked()),
            this, SLOT(slotForwardSwitch()));

    triLabel = new QLabel(this);
    triLabel->setPixmap(QPixmap(":images/tri.png"));
    triLabel->setGeometry(152,290,16,16);
}

void NoticeWindow::slotForwardSwitch()
{
    noticeWidget->showNewNotice();
    noticesSwitchAnimation->setDuration(900);//速度,越小越快
    noticesSwitchAnimation->setStartValue(QRect(-652,0,652,300));
    noticesSwitchAnimation->setEndValue(QRect(0,0,652,300));
    noticesSwitchAnimation->setEasingCurve(QEasingCurve::OutBack);
    noticesSwitchAnimation->start();
}

void NoticeWindow::slotBackSwitch()
{
    noticeWidget->showOldNotice();
    noticesSwitchAnimation->setDuration(900);//速度,越小越快
    noticesSwitchAnimation->setStartValue(QRect(652,0,652,300));
    noticesSwitchAnimation->setEndValue(QRect(0,0,652,300));
    noticesSwitchAnimation->setEasingCurve(QEasingCurve::OutBack);
    noticesSwitchAnimation->start();
}
