#include "NoticeDialog.h"

NoticeDialog::NoticeDialog(QDialog *parent) : QDialog(parent)
{
    resize(372,388);
    userData = UserData::getUserData();
    http = DOHelper::getDOHelper();
    bPressFlag = false;
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    //白色背景设置
    QPalette bgPalette;
    bgPalette.setColor(QPalette::Background, QColor("#FFF"));
    this->setPalette(bgPalette);
    this->setAutoFillBackground(false);
    initLayout();
}

void NoticeDialog::initLayout()
{
    closeBtn = new QPushButton(this);
    closeBtn->setGeometry(334,14,25,25);
    closeBtn->setStyleSheet("QPushButton{border-image: url(:images/close_small.png);}"
                            "QPushButton:hover{border-image: url(:images/close_small_hover.png);}"
                            "QPushButton:pressed{border-image: url(:images/close_small.png);}");
    connect(closeBtn,SIGNAL(clicked()),this,SLOT(close()));

    QColor textColor(102,102,102);
    QPalette pa;
    QFont ft;
    ft.setPixelSize(16);
    ft.setBold(true);
    ft.setFamily("冬青黑体简体中文 W3");

    date = new QLabel(this);
    date->setAlignment(Qt::AlignCenter);
    date->setText(tr("公告执行日期"));
    date->setFont(ft);
    pa.setColor(QPalette::WindowText,textColor);
    date->setPalette(pa);
    date->setGeometry(122,42,114,26);

    ft.setPixelSize(14);
    ft.setBold(false);
    content = new QLabel(this);
    content->setAlignment(Qt::AlignVCenter);
    content->setWordWrap(true);
    content->setText(tr("公告内容"));
    content->setFont(ft);
    content->setPalette(pa);
    content->setGeometry(30,80,300,208);

    creatTime =  new QLabel(this);
    creatTime->setAlignment(Qt::AlignCenter);
    creatTime->setText(tr("公告创建时间：... ..."));
    ft.setPixelSize(12);
    creatTime->setFont(ft);
    creatTime->setPalette(pa);
    creatTime->setGeometry(210,300,128,18);

    noticeID =  new QLabel(this);
    noticeID->setGeometry(34,330,2,2);

    deleteBtn = new QPushButton(tr("删除"), this);
    deleteBtn->setStyleSheet("background-color:#FF7F7F;color:white;border:none;");
    deleteBtn->setGeometry(34,330,304,32);
    connect(deleteBtn,SIGNAL(clicked()),
            this,SLOT(deleteNotice()));
}

void NoticeDialog::deleteNotice()
{
    if(!noticeID->text().isEmpty()){
        http->delNoticeRequst(noticeID->text());
        this->close();
    }
    else
        QMessageBox::about(this, "提示", "此公告为空，无法删除！");
}

void NoticeDialog::mousePressEvent(QMouseEvent *event)
{
    bPressFlag = true;
    beginDrag = event->pos();
    QWidget::mousePressEvent(event);
}

void NoticeDialog::mouseMoveEvent(QMouseEvent *event)
{
    if (bPressFlag) {
        QPoint relaPos(QCursor::pos() - beginDrag);
        move(relaPos);
    }
    QWidget::mouseMoveEvent(event);
}

void NoticeDialog::mouseReleaseEvent(QMouseEvent *event)
{
    bPressFlag = false;
    QWidget::mouseReleaseEvent(event);
}

void NoticeDialog::paintEvent(QPaintEvent *)
{
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);
    path.addRect(10, 10, this->width()-20, this->height()-20);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.fillPath(path, QBrush(Qt::white));

    QColor color(200, 200, 200, 50);

    //在透明背景的外部10px矩形框绘制由半透明浅黑色渐变至白色的阴影
    for(int i=0; i<10; i++)
    {
        QPainterPath path;
        path.setFillRule(Qt::WindingFill);
        path.addRect(10-i, 10-i, this->width()-(10-i)*2, this->height()-(10-i)*2);
        color.setAlpha(150 - qSqrt(i)*50);
        painter.setPen(color);
        painter.drawPath(path);
    }
}
