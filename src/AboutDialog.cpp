#include "AboutDialog.h"

AboutDialog::AboutDialog(QDialog *parent) : QDialog(parent)
{
    resize(260,292);
    bPressFlag = false;
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    initInterface();
}

void AboutDialog::initInterface()
{
    //白色背景设置
    QPalette bgPalette;
    bgPalette.setColor(QPalette::Background, QColor("#FFF"));
    this->setPalette(bgPalette);
    this->setAutoFillBackground(false);

    closeBtn = new QPushButton(this);
    closeBtn->setGeometry(222,14,25,25);
    closeBtn->setStyleSheet("QPushButton{border-image: url(:images/close_small.png);}"
                            "QPushButton:hover{border-image: url(:images/close_small_hover.png);}"
                            "QPushButton:pressed{border-image: url(:images/close_small.png);}");
    connect(closeBtn,SIGNAL(clicked()),this,SLOT(close()));

    applicationLogo = new QLabel(this);
    applicationLogo->setPixmap(QPixmap(":/images/info_logo.png"));
    applicationLogo->setToolTip(tr("<img src=\":/images/hclab_logo.png\">"
                                   "&nbsp;开发人员简介："
                                   "<ul>"
                                   "<li><b>客户端部分：</b>陈潼升 张晓煌"
                                   "<li><b>服务端部分：</b>邹锋"
                                   "<li><b>UI设计部分：</b>刘毓奔<br/>"
                                   "<li><b>1.4版本：</b>林伟城，何家良<br/>"
                                   "<li><b>2.0版本：</b>杨容光<br/>"
                                   "</ul>"
                                   "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;其他："
                                   "<ul>"
                                   "<li><b>真诚鸣谢：</b>罗嘉伟师兄、陈依雯师姐、张旭辉师兄、"
                                   "郑志昭师兄以及环创电脑工作室所有成员的支持与帮助"
                                   "<li><b>寄语：</b>大学四年里，至少还有我..."
                                   "</ul>"));
    applicationLogo->setGeometry(90,58,80,80);

    QColor textColor(102,102,102);
    QPalette pa;
    QFont ft;
    ft.setPixelSize(14);
    ft.setBold(true);
    ft.setFamily("冬青黑体简体中文 W3");

    applicationName = new QLabel(this);
    applicationName->setText(tr("环创计时器"));
    applicationName->setFont(ft);
    pa.setColor(QPalette::WindowText,textColor);
    applicationName->setPalette(pa);
    applicationName->setAlignment(Qt::AlignCenter);
    applicationName->setGeometry(90,154,80,16);

    applicationVersion = new QLabel(this);
    applicationVersion->setText(QString("V")+VERSION_STR);
    applicationVersion->setFont(ft);
    applicationVersion->setPalette(pa);
    applicationVersion->setAlignment(Qt::AlignCenter);
    applicationVersion->setGeometry(90,168,80,32);

    applicationContacts =  new QLabel(this);
    applicationContacts->setText(tr("<style> a {text-decoration: none} </style> <a style='color: #5CC3EF;' href=\"http://www.hclab.cn/\">©环创电脑工作室"));
    applicationContacts->setToolTip(tr("点击有惊喜..."));
    ft.setPixelSize(13);
    applicationContacts->setFont(ft);
    applicationContacts->setGeometry(80,250,112,18);
    applicationContacts->setOpenExternalLinks(true);
    connect(applicationContacts,SIGNAL(linkActivated(QString)),
            this,SLOT(openHCLabWebUrl(QString)));
}

void AboutDialog::openHCLabWebUrl(QString url)
{
    this->close();
    QDesktopServices::openUrl(QUrl(url));
}

void AboutDialog::mousePressEvent(QMouseEvent *event)
{
    bPressFlag = true;
    beginDrag = event->pos();
    QWidget::mousePressEvent(event);
}

void AboutDialog::mouseMoveEvent(QMouseEvent *event)
{
    if (bPressFlag) {
        QPoint relaPos(QCursor::pos() - beginDrag);
        move(relaPos);
    }
    QWidget::mouseMoveEvent(event);
}

void AboutDialog::mouseReleaseEvent(QMouseEvent *event)
{
    bPressFlag = false;
    QWidget::mouseReleaseEvent(event);
}

/**
 * @brief MainWindow::paintEvent 用于绘阴影
 */
void AboutDialog::paintEvent(QPaintEvent *)
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
