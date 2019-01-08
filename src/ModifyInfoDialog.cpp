#include "ModifyInfoDialog.h"

ModifyInfoDialog::ModifyInfoDialog(QDialog *parent) : QDialog(parent)
{
    setFixedSize(372,388);
    bPressFlag = false;
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    //白色背景设置
    QPalette bgPalette;
    bgPalette.setColor(QPalette::Background, QColor("#FFF"));
    this->setPalette(bgPalette);
    this->setAutoFillBackground(true);
    http = DOHelper::getDOHelper();
    userData = UserData::getUserData();
    themeColor = userData->getThemeColor();

    initLayout();
}

void ModifyInfoDialog::initLayout()
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

//    //正则表达式验证
//    QRegExp password_reg_exp("[^\u4E00-\u9FA5]{6,20}");//非汉字
//    QRegExp user_reg_exp("[A-Za-z0-9_]{6,30}");//字母、数字、下划线组成（4-30位）
//    QRegExpValidator *validator = new QRegExpValidator(password_reg_exp);
//    if(!validator->regExp().exactMatch(password))
//    {
//        return false;
//    }

    titileLable = new QLabel(this);
    titileLable->setText(tr("修改资料"));
    titileLable->setFont(ft);
    pa.setColor(QPalette::WindowText,titleColor);
    titileLable->setPalette(pa);
    titileLable->move(122,32);

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
    accountEdit->setText(userData->getUserAccount());
    accountEdit->resize(144,32);
    accountEdit->move(34,122);

    userNameEdit = new QLineEdit(this);
    userNameEdit->setPlaceholderText(tr("  真实姓名"));
    userNameEdit->setText(userData->getUserName());
    userNameEdit->setMaxLength(20);
    userNameEdit->resize(144,32);
    userNameEdit->move(194,122);

    oldPwdEdit = new QLineEdit(this);
    oldPwdEdit->setPlaceholderText(tr("  旧密码"));
    oldPwdEdit->setEchoMode(QLineEdit::Password);
    oldPwdEdit->setMaxLength(16);//设置密码长度最大为16位
    oldPwdEdit->resize(144,32);
    oldPwdEdit->move(34,186);

    gradeEdit = new QLineEdit(this);
    gradeEdit->setPlaceholderText(tr("  年级"));
    gradeEdit->setText(userData->getUserGrade());
    gradeEdit->setStyleSheet("background-color:#FFFFFF;");
    gradeEdit->resize(144,32);
    gradeEdit->move(194,186);

    newPwdEdit = new QLineEdit(this);
    newPwdEdit->setPlaceholderText(tr("  新密码"));
    newPwdEdit->setEchoMode(QLineEdit::Password);
    newPwdEdit->setMaxLength(16);//设置密码长度最大为16位
    newPwdEdit->resize(144,32);
    newPwdEdit->move(34,250);

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

void ModifyInfoDialog::soltConfirmBtn()
{
    if(accountEdit->text().isEmpty()||userNameEdit->text().isEmpty()||oldPwdEdit->text().isEmpty()
            ||sexComboBox->currentText().isEmpty()||gradeEdit->text().isEmpty()||newPwdEdit->text().isEmpty()){
        QMessageBox::about(this, "提示", "有些相关信息为空，请认真填写！");
    }
    else if(oldPwdEdit->text()!= userData->getUserPassword()){
        QMessageBox::about(this, "提示", "旧密码错误，请确认后填写！");
    }
    else if(gradeEdit->text().toInt()<1000){
        QMessageBox::about(this, "提示", "请输入正确的年级格式(例：2014)");
    }
    else{
        if(!userData->getUserID().isEmpty())
            http->updateUserInfoRequst(userData->getUserID(),accountEdit->text(),userNameEdit->text(),newPwdEdit->text(),
                        sexComboBox->currentText(),gradeEdit->text());
        this->close();
    }
}

void ModifyInfoDialog::mousePressEvent(QMouseEvent *event)
{
    bPressFlag = true;
    beginDrag = event->pos();
    QWidget::mousePressEvent(event);
}

void ModifyInfoDialog::mouseMoveEvent(QMouseEvent *event)
{
    if (bPressFlag) {
        QPoint relaPos(QCursor::pos() - beginDrag);
        move(relaPos);
    }
    QWidget::mouseMoveEvent(event);
}

void ModifyInfoDialog::mouseReleaseEvent(QMouseEvent *event)
{
    bPressFlag = false;
    QWidget::mouseReleaseEvent(event);
}

void ModifyInfoDialog::paintEvent(QPaintEvent *)
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
