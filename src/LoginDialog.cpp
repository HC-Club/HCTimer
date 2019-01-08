#include "LoginDialog.h"

LoginDialog::LoginDialog(QDialog *parent) : QDialog(parent)
{
    http = DOHelper::getDOHelper();
    userData = UserData::getUserData();
    themeColor = userData->getThemeColor();
    resize(228,292);
    bPressFlag = false;

    initInterface();
}
void LoginDialog::initInterface()
{
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    //白色背景设置
    QPalette bgPalette;
    bgPalette.setColor(QPalette::Background, QColor("#FFF"));
    this->setPalette(bgPalette);
    this->setAutoFillBackground(true);

    accountEdit = new QLineEdit(this);
    accountEdit->setPlaceholderText(tr("  学号"));
    accountEdit->setContextMenuPolicy(Qt::NoContextMenu);
    passwordEdit = new QLineEdit(this);
    passwordEdit->setPlaceholderText(tr("  密码"));
    closeBtn = new QPushButton(this);
    closeBtn->setStyleSheet("QPushButton{border-image: url(:images/close_small.png);}"
                            "QPushButton:hover{border-image: url(:images/close_small_hover.png);}"
                            "QPushButton:pressed{border-image: url(:images/close_small.png);}");
    loginBtn = new QPushButton(tr("登录"), this);
    loginBtn->setFocus();
    loginBtn->setShortcut(QKeySequence::InsertParagraphSeparator);
    registBtn = new QPushButton(tr("注册"), this);
    if(themeColor==0){
        loginBtn->setStyleSheet("background-color:#4FCFFF;color:white;border:none;");
        registBtn->setStyleSheet("background-color:#FFFFFF;color:#4FCFFF;border:none;");
    }
    else if(themeColor==1){
        loginBtn->setStyleSheet("background-color:#8AE6C7;color:white;border:none;");
        registBtn->setStyleSheet("background-color:#FFFFFF;color:#8AE6C7;border:none;");
    }
    else if(themeColor==2){
        loginBtn->setStyleSheet("background-color:#FFB266;color:white;border:none;");
        registBtn->setStyleSheet("background-color:#FFFFFF;color:#FFB266;border:none;");
    }
    else{
        loginBtn->setStyleSheet("background-color:#FF7F7F;color:white;border:none;");
        registBtn->setStyleSheet("background-color:#FFFFFF;color:#FF7F7F;border:none;");
    }

    accountEdit->resize(144,32);
    passwordEdit->resize(144,32);
    loginBtn->resize(144,32);
    closeBtn->resize(25,25);
    registBtn->resize(32,32);

    accountEdit->setMaxLength(20);
    passwordEdit->setMaxLength(20);//设置密码长度最大为20位
    passwordEdit->setEchoMode(QLineEdit::Password);

    closeBtn->move(190,14);
    accountEdit->move(42,98);
    passwordEdit->move(42,146);
    loginBtn->move(42,194);
    registBtn->move(154,235);

    connect(closeBtn,SIGNAL(clicked()),this,SLOT(close()));
    connect(loginBtn,SIGNAL(clicked()),this,SLOT(loginBtnClick()));
    connect(registBtn,SIGNAL(clicked()),this,SLOT(registBtnClick()));
}

void LoginDialog::mousePressEvent(QMouseEvent *event)
{
    bPressFlag = true;
    beginDrag = event->pos();
    QWidget::mousePressEvent(event);
}

void LoginDialog::mouseMoveEvent(QMouseEvent *event)
{
    if (bPressFlag) {
        QPoint relaPos(QCursor::pos() - beginDrag);
        move(relaPos);
    }
    QWidget::mouseMoveEvent(event);
}

void LoginDialog::mouseReleaseEvent(QMouseEvent *event)
{
    bPressFlag = false;
    QWidget::mouseReleaseEvent(event);
}

void LoginDialog::loginBtnClick()
{    
    if(accountEdit->text().isEmpty()||passwordEdit->text().isEmpty()){
        QMessageBox::about(this, "提示", "账号或密码为空，请认真填写！");
    }
    else{
        //正则表达式验证
        QRegExp accountRegExp("[0-9]{4,16}");//数字组成（4-16位）
        QRegExp passwordRegExp("[^\u4E00-\u9FA5]{4,16}");//非汉字
        QRegExpValidator *validator = new QRegExpValidator(accountRegExp);
        if(!validator->regExp().exactMatch(accountEdit->text()))
        {
            QMessageBox::about(this, "提示", "请填写4~16位，且都为数字的合法学号！");
            delete validator;
            return;
        }
        validator->setRegExp(passwordRegExp);
        if(!validator->regExp().exactMatch(passwordEdit->text()))
        {
            QMessageBox::about(this, "提示", "请填写4~16位，且都为非汉字的密码！");
            delete validator;
            return;
        }
        userData->setTodayTime(0);
        userData->setTotalTime(0);
        userData->setUserAccount(accountEdit->text());
        userData->setUserPassWord(passwordEdit->text());
        http->loginRequst(userData->getUserAccount(),userData->getUserPassword());
        if(!userData->getUserID().isEmpty())
            http->getUserInfoRequst(userData->getUserID());

        delete validator;

        this->close();
    }
}

void LoginDialog::registBtnClick()
{
    RegistDialog registDialog;
    registDialog.move(this->pos().x()-56,this->pos().y()-32);
    this->close();
    registDialog.exec();
}

void LoginDialog::paintEvent(QPaintEvent *)
{
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);
    path.addRect(10, 10, this->width()-20, this->height()-20);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.fillPath(path, QBrush(Qt::white));

    QColor color(200, 200, 200, 50);//CMYK色彩模式

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
