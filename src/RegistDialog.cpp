#include "RegistDialog.h"

RegistDialog::RegistDialog(QDialog *parent) : QDialog(parent)
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
    themeColor = 1;
    initLayout();
}

void RegistDialog::initLayout()
{
    closeBtn = new QPushButton(this);
    closeBtn->setGeometry(334,14,25,25);
    closeBtn->setStyleSheet("QPushButton{border-image: url(:images/close_small.png);}"
                            "QPushButton:hover{border-image: url(:images/close_small_hover.png);}"
                            "QPushButton:pressed{border-image: url(:images/close_small.png);}");
    connect(closeBtn,SIGNAL(clicked()),this,SLOT(close()));

    QColor titleColor(102,102,102);
    QColor textColor(184,184,184);
    QPalette pa;

    QFont ft;
    ft.setPixelSize(30);
    ft.setFamily("冬青黑体简体中文 W3");

    titileLable = new QLabel(this);
    titileLable->setText(tr("注册"));
    titileLable->setFont(ft);
    pa.setColor(QPalette::WindowText,titleColor);
    titileLable->setPalette(pa);
    titileLable->move(154,32);

    hintLabel = new QLabel(this);
    ft.setBold(true);
    hintLabel->setText(tr("以下信息请认真填写"));
    ft.setPixelSize(16);
    hintLabel->setFont(ft);
    pa.setColor(QPalette::WindowText,textColor);
    hintLabel->setPalette(pa);
    hintLabel->move(112,80);

    accountEdit = new QLineEdit(this);
    accountEdit->setPlaceholderText(tr("  学号"));
    accountEdit->setMaxLength(20);
    accountEdit->resize(144,32);
    accountEdit->move(34,122);

    userNameEdit = new QLineEdit(this);
    userNameEdit->setPlaceholderText(tr("  真实姓名"));
    userNameEdit->setMaxLength(20);
    userNameEdit->resize(144,32);
    userNameEdit->move(194,122);

    pwdEdit = new QLineEdit(this);
    pwdEdit->setPlaceholderText(tr("  密码"));
    pwdEdit->setEchoMode(QLineEdit::Password);
    pwdEdit->setMaxLength(20);//设置密码长度最大为20位
    pwdEdit->resize(144,32);
    pwdEdit->move(34,186);

    gradeEdit = new QLineEdit(this);
    gradeEdit->setPlaceholderText(tr("  年级"));
    gradeEdit->setMaxLength(10);

    gradeEdit->setStyleSheet("background-color:#FFFFFF;");
    gradeEdit->resize(144,32);
    gradeEdit->move(194,186);

    confirmPwdEdit = new QLineEdit(this);
    confirmPwdEdit->setPlaceholderText(tr("  密码确认"));
    confirmPwdEdit->setMaxLength(20);
    confirmPwdEdit->setEchoMode(QLineEdit::Password);
    confirmPwdEdit->resize(144,32);
    confirmPwdEdit->move(34,250);

    sexComboBox = new QComboBox(this);
    sexComboBox->setEditable(true);
    sexComboBox->setStyleSheet(  "QComboBox QAbstractItemView::item{height:25px;}" //下拉选项高度
                                 "QComboBox::down-arrow{image:url(:/images/btn_select.png);}" //下拉箭头
                                 "QComboBox::drop-down{border:1px;}"); //下拉按钮
    sexComboBox->setView(new QListView());
    sexComboBox->addItem("男");
    sexComboBox->addItem("女");
    sexComboBox->resize(144,32);
    sexComboBox->move(194,250);

    confirmBtn = new QPushButton(tr("确认"), this);
    confirmBtn->setFocus();
    confirmBtn->setShortcut(QKeySequence::InsertParagraphSeparator);
    if(themeColor==0){
        confirmBtn->setStyleSheet("background-color:#4FCFFF;color:white;border:none;");
    }
    else if(themeColor==1){
        confirmBtn->setStyleSheet("background-color:#8AE6C7;color:white;border:none;");
    }
    else if(themeColor==2){
        confirmBtn->setStyleSheet("background-color:#FFB266;color:white;border:none;");
    }
    else{
        confirmBtn->setStyleSheet("background-color:#FF7F7F;color:white;border:none;");
    }
    confirmBtn->resize(304,32);
    confirmBtn->move(34,314);
    connect(confirmBtn, SIGNAL(clicked()),
            this, SLOT(soltConfirmBtn()));
}

void RegistDialog::soltConfirmBtn()
{
    if(accountEdit->text().isEmpty()||userNameEdit->text().isEmpty()||pwdEdit->text().isEmpty()
            ||sexComboBox->currentText().isEmpty()||gradeEdit->text().isEmpty()||confirmPwdEdit->text().isEmpty()){
        QMessageBox::about(this, "提示", "有些相关信息为空，请认真填写！");
    }
    else if(pwdEdit->text()!=confirmPwdEdit->text()){
        QMessageBox::about(this, "提示", "两次密码不同，请确认后填写！");
    }
    else{
        //正则表达式验证
        QRegExp accountRegExp("[0-9]{4,16}");//数字组成（4-16位）
        QRegExp passwordRegExp("[^\u4E00-\u9FA5]{4,16}");//非汉字
        QRegExp gradeRegExp("[0-9]{4,8}");//数字组成（4-8位）
        QRegExpValidator *validator = new QRegExpValidator(accountRegExp);
        if(!validator->regExp().exactMatch(accountEdit->text()))
        {
            QMessageBox::about(this, "提示", "请填写4~16位，且都为数字的合法学号！");
            delete validator;
            return;
        }
        validator->setRegExp(passwordRegExp);
        if(!validator->regExp().exactMatch(pwdEdit->text()))
        {
            QMessageBox::about(this, "提示", "请填写4~16位，且都为非汉字的密码！");
            delete validator;
            return;
        }
        validator->setRegExp(gradeRegExp);
        if(!validator->regExp().exactMatch(gradeEdit->text()))
        {
            QMessageBox::about(this, "提示", "请输入正确的年级格式(例：2014)");
            delete validator;
            return;
        }
        User user;
        user.setAccount(accountEdit->text().trimmed());
        user.setPassword(pwdEdit->text().trimmed());
        user.setGrade(gradeEdit->text().trimmed());
        user.setSex(sexComboBox->currentText());
        user.setTrueName(userNameEdit->text().trimmed());
        m_server->userRegister(user);

        delete validator;

    }
}

void RegistDialog::Server_RegisterFail(const QString &message)
{
    QMessageBox::information(this,"注册失败",message);
}

void RegistDialog::Server_RegisterSuccess(const QString &message)
{
    QMessageBox::information(this,"环创工作室计时器新用户",message);
    this->close();
}

void RegistDialog::mousePressEvent(QMouseEvent *event)
{
    bPressFlag = true;
    beginDrag = event->pos();
    QWidget::mousePressEvent(event);
}

void RegistDialog::mouseMoveEvent(QMouseEvent *event)
{
    if (bPressFlag) {
        QPoint relaPos(QCursor::pos() - beginDrag);
        move(relaPos);
    }
    QWidget::mouseMoveEvent(event);
}

void RegistDialog::mouseReleaseEvent(QMouseEvent *event)
{
    bPressFlag = false;
    QWidget::mouseReleaseEvent(event);
}

void RegistDialog::paintEvent(QPaintEvent *)
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

void RegistDialog::setServer(MyServer *server)
{
    m_server = server;
    connect(m_server,SIGNAL(sError(QString)),this,SLOT(Server_RegisterFail(QString)));
    connect(m_server,SIGNAL(sRegister(QString)),this,SLOT(Server_RegisterSuccess(QString)));
}
