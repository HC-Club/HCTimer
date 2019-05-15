#include "LoginDialog.h"

QDataStream& operator <<(QDataStream &steam,const User &user)
{
    steam<<user.getAccount().toUtf8()<<user.getPassword().toUtf8()<<(qint32)user.getThemeColor();
    return steam;
}

QDataStream& operator >>(QDataStream &steam,User user)
{
    QByteArray temp;
    steam>>temp;
    user.setAccount(QString(temp));
    steam>>temp;
    user.setPassword(QString(temp));
    qint32 color;
    steam>>color;
    user.setThemeColor(color);
    return steam;
}


LoginDialog::LoginDialog(QDialog *parent) : QDialog(parent)
{

    themeColor = 1;
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


    registBtn = new QPushButton(tr("注册"), this);
    loginBtn = new QPushButton(tr("登录"), this);
    loginBtn->setFocus();
    loginBtn->setShortcut(QKeySequence::InsertParagraphSeparator);

    rememberPasswordBtn = new QCheckBox("记住密码",this);
    autoLoginBtn = new QCheckBox("自动登录",this);





    closeBtn = new QPushButton(this);
    closeBtn->setStyleSheet("QPushButton{border-image: url(:images/close_small.png);}"
                            "QPushButton:hover{border-image: url(:images/close_small_hover.png);}"
                            "QPushButton:pressed{border-image: url(:images/close_small.png);}");

//    setTabOrder(accountEdit,passwordEdit);
//    setTabOrder(passwordEdit,loginBtn);
//    setTabOrder(loginBtn,registBtn);
//    setTabOrder(registBtn,closeBtn);
//    setTabOrder(closeBtn,accountEdit);

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

    rememberPasswordBtn->move(42,156);
    autoLoginBtn->move(114,156);

    accountEdit->setMaxLength(20);
    passwordEdit->setMaxLength(20);//设置密码长度最大为20位
    passwordEdit->setEchoMode(QLineEdit::Password);

    closeBtn->move(190,14);
    accountEdit->move(42,58);
    passwordEdit->move(42,106);
    loginBtn->move(42,184);
    registBtn->move(154,235);

    connect(closeBtn,SIGNAL(clicked()),this,SLOT(close()));
    connect(loginBtn,SIGNAL(clicked()),this,SLOT(loginBtnClick()));
    connect(registBtn,SIGNAL(clicked()),this,SLOT(registBtnClick()));
    connect(passwordEdit,SIGNAL(returnPressed()),this,SLOT(loginBtnClick()),Qt::UniqueConnection);
    connect(accountEdit,SIGNAL(returnPressed()),this,SLOT(loginBtnClick()),Qt::UniqueConnection);
    connect(accountEdit,SIGNAL(textChanged(QString)),this,SLOT(Local_AccountTextChange(const QString&)));

    rememberPasswordBtn->show();
    autoLoginBtn->show();
}

void LoginDialog::setServer(MyServer *server)
{
    m_server = server;
    connect(m_server,SIGNAL(sLogin(User)),this,SLOT(Server_LoginSuccess(User)));
    connect(m_server,SIGNAL(sLoginFail(QString)),this,SLOT(Server_LoginFail(QString)));

}

void LoginDialog::setUser(const User &user)
{
    accountEdit->setText(user.getAccount());
    passwordEdit->setText(user.getPassword());
    rememberPasswordBtn->setChecked(user.getRememberPassword());
    autoLoginBtn->setChecked(user.getAutoLogin());
}

void LoginDialog::local_saveUserMessage(const User &user)
{
    User temp;
    bool autoLogin = false;
    QList<User> list = getAllUserMessageFromLocal();
    for(int i=list.size()-1;i>=0;i--)
    {
        if(list.at(i).getAccount()==user.getAccount())
        {
            list.removeAt(i);
            continue;
        }
        if(user.getAutoLogin()&&list.at(i).getAutoLogin())
        {
            temp = list.at(i);
            list.removeAt(i);
            autoLogin = true;
        }
    }
    if(autoLogin)
    {
        list.append(temp);
    }
    if(user.getRememberPassword()||user.getAutoLogin())
    {
        list.append(user);
    }
    SaveAllUserMessageFromLocal(list);
}

User LoginDialog::local_getUserMessage(const QString &userName)
{
    QList<User> list = getAllUserMessageFromLocal();

    User user;

    if(list.size()==0)
    {
        return user;
    }

    for(int i=0;i<list.size();i++)
    {
        if(list.at(i).getAccount()==userName&&userName!=""||userName==""&&list.at(i).getAutoLogin()==true)
        {
            return list.at(i);
        }
    }
    return user;
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
    User t = local_getUserMessage("");
    if(accountEdit->text().isEmpty()||passwordEdit->text().isEmpty()){
        QMessageBox::about(this, "提示", "账号或密码为空，请认真填写！");
        return;
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


        delete validator;

        User user;
        user.setAccount(accountEdit->text().trimmed());
        user.setPassword(passwordEdit->text().trimmed());
        m_server->login(user);
    }
}

void LoginDialog::registBtnClick()
{
    RegistDialog registDialog;
    registDialog.setServer(m_server);
    registDialog.move(this->pos().x()-56,this->pos().y()-32);
    this->close();
    registDialog.exec();
}

void LoginDialog::Server_LoginSuccess(const User &user)
{
    User LoginUser = user;

    LoginUser.setRememberPassword(rememberPasswordBtn->isChecked());
    LoginUser.setAutoLogin(autoLoginBtn->isChecked());

    local_saveUserMessage(LoginUser);

    emit sLogin(LoginUser);

    close();
}

void LoginDialog::Server_LoginFail(const QString &message)
{
    QMessageBox::information(this,"登录失败",message);
}

void LoginDialog::Local_AccountTextChange(const QString &text)
{
    User user = local_getUserMessage(text);
    if(user.getAccount()!="")
    {
        accountEdit->setText(user.getAccount());
        passwordEdit->setText(user.getPassword());
        rememberPasswordBtn->setChecked(user.getRememberPassword());
        autoLoginBtn->setChecked(user.getAutoLogin());
    }
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

void LoginDialog::keyPressEvent(QKeyEvent *event)
{

}

void LoginDialog::CreateLocalDatabase()
{
    QFile file(FILENAME);

    file.open(QIODevice::WriteOnly);

    file.reset();
    QDataStream steam(&file);

    qint32 code = 20190409;
    qint32 people = 0;
    steam<<code<<people;

    file.close();
}

QList<User> LoginDialog::getAllUserMessageFromLocal()
{
    QList<User> list;

    QFile file(FILENAME);

    if(!file.exists())
    {
        CreateLocalDatabase();
    }

    file.open(QIODevice::ReadOnly);

    QDataStream steam(&file);

    qint32 code;
    qint32 people;

    steam>>code>>people;
    if(code!=20190409)
    {
        return list;
    }

    QByteArray temp;
    User user;
    qint32 color;
    for(int i=0;i<people;i++)
    {
        steam>>temp;
        user.setAccount(QString(temp));
        steam>>temp;
        user.setPassword(deCode(QString(temp)));
        steam>>color;
        user.setThemeColor(color);
        steam>>color;
        user.setRememberPassword((bool)color);
        steam>>color;
        user.setAutoLogin((bool)color);

        list.append(user);
    }
    file.close();
    return list;
}

void LoginDialog::SaveAllUserMessageFromLocal(const QList<User> &list)
{
    QFile file(FILENAME);

    if(!file.exists())
    {
        CreateLocalDatabase();
    }

    file.open(QIODevice::WriteOnly);
    file.reset();
    QDataStream steam(&file);

    steam<<(qint32)20190409<<(qint32)list.size();
    for(int i=0;i<list.size();i++)
    {
        User user = list.at(i);
        steam<<user.getAccount().toUtf8();
        steam<<enCode(user.getPassword()).toUtf8();
        steam<<(qint32)user.getThemeColor();
        steam<<(qint32)user.getRememberPassword();
        steam<<(qint32)user.getAutoLogin();
    }

    file.close();

}

QString LoginDialog::enCode(const QString &str)
{
    return str;
}

QString LoginDialog::deCode(const QString &str)
{
    return str;
}
