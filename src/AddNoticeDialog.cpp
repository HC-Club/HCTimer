#include "AddNoticeDialog.h"

AddNoticeDialog::AddNoticeDialog(QDialog *parent) : QDialog(parent)
{
    resize(260,292);
    bPressFlag = false;
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    //白色背景设置
    QPalette bgPalette;
    bgPalette.setColor(QPalette::Background, QColor("#FFF"));
    this->setPalette(bgPalette);
    this->setAutoFillBackground(false);


    themeColor = 0;

    initLayout();
}

void AddNoticeDialog::initLayout()
{
    closeBtn = new QPushButton(this);
    closeBtn->setGeometry(222,14,25,25);
    closeBtn->setStyleSheet("QPushButton{border-image: url(:images/close_small.png);}"
                            "QPushButton:hover{border-image: url(:images/close_small_hover.png);}"
                            "QPushButton:pressed{border-image: url(:images/close_small.png);}");
    connect(closeBtn,SIGNAL(clicked()),this,SLOT(close()));

    year = new QLineEdit(this);
    year->setPlaceholderText(tr("    年"));
    year->setMaxLength(10);
    year->setGeometry(28,58,72,32);

    month = new QLineEdit(this);
    month->setPlaceholderText(tr("  月"));
    month->setMaxLength(2);
    month->setGeometry(118,58,48,32);

    day = new QLineEdit(this);
    day->setPlaceholderText(tr("  日"));
    day->setMaxLength(2);
    day->setGeometry(182,58,48,32);

    content = new QTextEdit(this);
    content->setAlignment(Qt::AlignVCenter);
    content->setStyleSheet("QTextEdit{background-color:#FFF;color:black;}"
                           "QScrollBar{background:transparent; height:10px; }");
    content->setPlaceholderText(tr("      公告内容(180个字以内)"));
    content->setGeometry(26,105,208,128);

    finishBtn = new QPushButton(tr("完成"), this);
    finishBtn->setFocus();
    finishBtn->setShortcut(QKeySequence::InsertParagraphSeparator);
    if(themeColor==0){
        finishBtn->setStyleSheet("background-color:#FFFFFF;color:#4FCFFF;border:none;");
    }
    else if(themeColor==1){
        finishBtn->setStyleSheet("background-color:#FFFFFF;color:#8AE6C7;border:none;");
    }
    else if(themeColor==2){
        finishBtn->setStyleSheet("background-color:#FFFFFF;color:#FFB266;border:none;");
    }
    else{
        finishBtn->setStyleSheet("background-color:#FFFFFF;color:#FF7F7F;border:none;");
    }

    finishBtn->setGeometry(202,242,32,32);
    connect(finishBtn,SIGNAL(clicked()),
            this,SLOT(slotFinishBtn()));
}

void AddNoticeDialog::slotFinishBtn()
{

    if(year->text().isEmpty() || month->text().isEmpty() || day->text().isEmpty()
            || content->toPlainText().isEmpty()){
        QMessageBox::about(this, "提示", "有些相关信息为空，请认真填写！");
    }
    else{
        int y,m,d;
        y = year->text().toInt(NULL,10);
        m = month->text().toInt(NULL,10);
        d = day->text().toInt(NULL,10);
        if( y<=0 || y>9999|| m<=0 || m>12 || d<=0 || d>31)
            QMessageBox::about(this, "提示", "时间格式不正确，请认真填写！");
        else if(content->toPlainText().length()>180)
            QMessageBox::about(this, "提示", "公告内容字数超出限制，请认真填写！");
        else{
            QDate date;
            date = QDate(y,m,d);
//            http->addNoticeRequst(date.toString("yyyy-MM-dd"),content->toPlainText());
            this->close();
        }
    }


}

void AddNoticeDialog::mousePressEvent(QMouseEvent *event)
{
    bPressFlag = true;
    beginDrag = event->pos();
    QWidget::mousePressEvent(event);
}

void AddNoticeDialog::mouseMoveEvent(QMouseEvent *event)
{
    if (bPressFlag) {
        QPoint relaPos(QCursor::pos() - beginDrag);
        move(relaPos);
    }
    QWidget::mouseMoveEvent(event);
}

void AddNoticeDialog::mouseReleaseEvent(QMouseEvent *event)
{
    bPressFlag = false;
    QWidget::mouseReleaseEvent(event);
}

void AddNoticeDialog::paintEvent(QPaintEvent *)
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
