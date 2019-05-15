#include "UserInfoDialog.h"

UserInfoDialog::UserInfoDialog(QDialog *parent) : QDialog(parent)
{
    resize(372,388);
    bPressFlag = false;
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    //白色背景设置
    QPalette bgPalette;
    bgPalette.setColor(QPalette::Background, QColor("#FFF"));
    this->setPalette(bgPalette);
    this->setAutoFillBackground(true);
    themeColor = 0;
    initLayout();
}

void UserInfoDialog::initLayout()
{
    closeBtn = new QPushButton(this);
    closeBtn->setGeometry(334,14,25,25);
    closeBtn->setStyleSheet("QPushButton{border-image: url(:images/close_small.png);}"
                            "QPushButton:hover{border-image: url(:images/close_small_hover.png);}"
                            "QPushButton:pressed{border-image: url(:images/close_small.png);}");
    connect(closeBtn,SIGNAL(clicked()),this,SLOT(close()));

    QColor titleColor(102,102,102);
    QPalette pa;

    QFont ft;
    ft.setPixelSize(30);
    ft.setFamily("冬青黑体简体中文 W3");

    titileLable = new QLabel(this);
    titileLable->setText(tr("个人资料"));
    titileLable->setFont(ft);
    pa.setColor(QPalette::WindowText,titleColor);
    titileLable->setPalette(pa);
    titileLable->move(120,30);

    ft.setPixelSize(15);
    ft.setFamily("冬青黑体简体中文 W3");

    QString userAccount;
    QString userName;
    QString userGrade;
    QString userSex;

    QSettings settings("settings.ini", QSettings::IniFormat);
    userAccount = settings.value("UserData/account").toString();
    userName = settings.value("UserData/name").toString();
    userGrade = settings.value("UserData/grade").toString();
    userSex = settings.value("UserData/sex").toString();

    avatarImage = new QImage(80,80,QImage::Format_RGB32);//设置图片大小和图片类型
    avatarLabel = new QLabel(this);
    avatarLabel->setGeometry(144,80,80,80);

    avatarBtn = new QPushButton(this);
    avatarBtn->setIconSize(QSize(80,80));
    avatarBtn->setStyleSheet("background-color:none;border:none;");
    avatarBtn->setToolTip(tr("编辑头像"));
    avatarBtn->setGeometry(144,80,80,80);
    connect(avatarBtn, SIGNAL(clicked()),
            this, SLOT(changeAvatar()));

    if((avatarImage->load(":images/my_avatar.png"))){
        avatarLabel->setPixmap(QPixmap::fromImage(*avatarImage));
    }
    else{
        avatarBtn->setIcon(QIcon(":images/my_avatar.png"));
    }

    accountLabel = new QLabel(this);
    accountLabel->setText(userAccount);
    accountLabel->setStyleSheet("border-width: 1px; border-style: solid; border-color: rgb(194,194,194);");
    accountLabel->setFont(ft);
    accountLabel->setPalette(pa);
    accountLabel->adjustSize();
    accountLabel->resize(144,32);
    accountLabel->move(34,186);

    userNameLabel = new QLabel(this);
    userNameLabel->setText(userName);
    userNameLabel->setStyleSheet("border-width: 1px; border-style: solid; border-color: rgb(194,194,194);");
    userNameLabel->setFont(ft);
    userNameLabel->setPalette(pa);
    userNameLabel->resize(144,32);
    userNameLabel->move(194,186);

    gradeLabel = new QLabel(this);
    gradeLabel->setText(userGrade);
    gradeLabel->setStyleSheet("border-width: 1px; border-style: solid; border-color: rgb(194,194,194);");
    gradeLabel->setFont(ft);
    gradeLabel->setPalette(pa);
    gradeLabel->resize(144,32);
    gradeLabel->move(34,250);

    sexLabel = new QLabel(this);
    sexLabel->setText(userSex);
    sexLabel->setStyleSheet("border-width: 1px; border-style: solid; border-color: rgb(194,194,194);");
    sexLabel->setFont(ft);
    sexLabel->setPalette(pa);
    sexLabel->resize(144,32);
    sexLabel->move(194,250);

    logoutBtn = new QPushButton(tr("注销"), this);
    logoutBtn->setStyleSheet("background-color:#FF7F7F;color:white;border:none;");
    logoutBtn->resize(304,32);
    logoutBtn->move(34,310);
    connect(logoutBtn, SIGNAL(clicked()),
            this, SLOT(soltLogoutBtn()));

    modifyInfoBtn = new QPushButton(tr("修改资料"), this);
    if(themeColor==0){
        modifyInfoBtn->setStyleSheet("background-color:none;color:#4FCFFF;border:none;");
    }
    else if(themeColor==1){
        modifyInfoBtn->setStyleSheet("background-color:none;color:#8AE6C7;border:none;");
    }
    else if(themeColor==2){
        modifyInfoBtn->setStyleSheet("background-color:none;color:#FFB266;border:none;");
    }
    else{
        modifyInfoBtn->setStyleSheet("background-color:none;color:#FF7F7F;border:none;");
    }
    modifyInfoBtn->move(272,338);
    modifyInfoBtn->resize(74,42);
    connect(modifyInfoBtn, SIGNAL(clicked()),
            this, SLOT(soltModifyInfoBtn()));
}

void UserInfoDialog::setUserInfo()
{
    QString userAccount = "";
    QString userName = "";
    QString userGrade = "";
    QString userSex = "";

    if(!userAccount.isEmpty())
        accountLabel->setText(userAccount);
    if(!userName.isEmpty())
        userNameLabel->setText(userName);
    if(!userGrade.isEmpty())
        gradeLabel->setText(userGrade);
    if(!userSex.isEmpty())
        sexLabel->setText(userSex);

}

void UserInfoDialog::changeAvatar()
{
    QString fileName;
    fileName = QFileDialog::getOpenFileName(this,
                                          tr("选择图像"),
                                          "",
                                          tr("Images (*.png *.bmp *.jpg *.tif *.GIF )"));
    if(fileName.isEmpty())
    {
         return;
    }
    else
    {
        QImage* img=new QImage(80,80,QImage::Format_RGB32);
        if(! (img->load(fileName)) ) //加载图像
        {

            QMessageBox::information(this,
                                     tr("提示"),
                                     tr("打开图像失败!"));
            delete img;
            return;
        }
        qDebug()<<"图片路径为："<<fileName;
        avatarLabel->setPixmap(QPixmap::fromImage(*img));
    }
}

void UserInfoDialog::soltLogoutBtn()
{

    this->close();
}

void UserInfoDialog::soltModifyInfoBtn()
{
    ModifyInfoDialog modifyInfoDialog;
    modifyInfoDialog.move(this->pos().x(),this->pos().y());
    this->close();
    modifyInfoDialog.exec();
}

void UserInfoDialog::mousePressEvent(QMouseEvent *event)
{
    bPressFlag = true;
    beginDrag = event->pos();
    QWidget::mousePressEvent(event);
}

void UserInfoDialog::mouseMoveEvent(QMouseEvent *event)
{
    if (bPressFlag) {
        QPoint relaPos(QCursor::pos() - beginDrag);
        move(relaPos);
    }
    QWidget::mouseMoveEvent(event);
}

void UserInfoDialog::mouseReleaseEvent(QMouseEvent *event)
{
    bPressFlag = false;
    QWidget::mouseReleaseEvent(event);
}

void UserInfoDialog::paintEvent(QPaintEvent *)
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
