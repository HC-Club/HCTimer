#include "InquirySpecificTimeDialog.h"

InquirySpecificTimeDialog::InquirySpecificTimeDialog(QDialog *parent) : QDialog(parent)
{

    resize(392,342);

    bPressFlag = false;

    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    //白色背景设置
    QPalette bgPalette;
    bgPalette.setColor(QPalette::Background, QColor("#FFF"));
    this->setPalette(bgPalette);
    this->setAutoFillBackground(true);

    themeColor = 0;

    initInterface();
}

void InquirySpecificTimeDialog::initInterface()
{
    QFont ft;
    ft.setFamily("冬青黑体简体中文 W3");
    ft.setPixelSize(16);

    closeBtn = new QPushButton(this);
    closeBtn->setGeometry(350,14,25,25);
    closeBtn->setStyleSheet("QPushButton{border-image: url(:images/close_small.png);}"
                            "QPushButton:hover{border-image: url(:images/close_small_hover.png);}"
                            "QPushButton:pressed{border-image: url(:images/close_small.png);}");
    connect(closeBtn,SIGNAL(clicked()),this,SLOT(close()));

    startYear = new QLineEdit(this);
    startYear->setAlignment(Qt::AlignCenter);
    startYear->setPlaceholderText(tr("年"));
    startYear->setMaxLength(10);
    startYear->setGeometry(28,50,64,24);

    startMonth = new QLineEdit(this);
    startMonth->setAlignment(Qt::AlignCenter);
    startMonth->setPlaceholderText(tr("月"));
    startMonth->setMaxLength(2);
    startMonth->setGeometry(100,50,32,24);

    startDay = new QLineEdit(this);
    startDay->setAlignment(Qt::AlignCenter);
    startDay->setPlaceholderText(tr("日"));
    startDay->setMaxLength(2);
    startDay->setGeometry(140,50,32,24);

    spacedLine = new QLabel(this);
    spacedLine->setText(tr("---"));
    spacedLine->setGeometry(188,50,64,24);

    endYear = new QLineEdit(this);
    endYear->setAlignment(Qt::AlignCenter);
    endYear->setPlaceholderText(tr("年"));
    endYear->setMaxLength(10);
    endYear->setGeometry(220,50,64,24);

    endMonth = new QLineEdit(this);
    endMonth->setAlignment(Qt::AlignCenter);
    endMonth->setPlaceholderText(tr("月"));
    endMonth->setMaxLength(2);
    endMonth->setGeometry(292,50,32,24);

    endDay = new QLineEdit(this);
    endDay->setAlignment(Qt::AlignCenter);
    endDay->setPlaceholderText(tr("日"));
    endDay->setMaxLength(2);
    endDay->setGeometry(332,50,32,24);

    listWidget = new QListWidget(this);
    listWidget->setFrameShape(QListWidget::NoFrame);
    listWidget->setStyleSheet(
                "QListWidget{background:transparent;}"
                "QListWidget::Item:hover{background:#F0F8FF; }"
                "QListWidget::item:selected{background:white;color:#55C3EF; }"
                "QScrollBar{background:transparent; height:10px; }"
                );
    listWidget->move(26,90);
    listWidget->setIconSize(QSize(64, 40));
    listWidget->resize(340,190);

    searchBtn = new QPushButton(this);
    searchBtn->setGeometry(310,297,60,24);
    searchBtn->setText(tr("查询"));
    searchBtn->setStyleSheet(
            "QPushButton{background-color:#4FCFFF;color:white;border:none;border-radius:4px;}"
            "QPushButton:pressed{background-color:#87CEFA;}");
    connect(searchBtn,SIGNAL(clicked()),this,SLOT(slotSearchBtn()));

//    if(!userData->getServerDate().isNull())
//    {
//        QDate tempDate;
//        tempDate = userData->getServerDate().addDays(-6-userData->getServerDate().dayOfWeek());
//        startYear->setText(QString::number(tempDate.year()));
//        startMonth->setText(QString::number(tempDate.month()));
//        startDay->setText(QString::number(tempDate.day()));

//        tempDate = userData->getServerDate().addDays(7-userData->getServerDate().dayOfWeek());
//        endYear->setText(QString::number(tempDate.year()));
//        endMonth->setText(QString::number(tempDate.month()));
//        endDay->setText(QString::number(tempDate.day()));
//    }
}

void InquirySpecificTimeDialog::showListResult(QString startDate,QString endDate)
{
    QFont ft;
    ft.setFamily("冬青黑体简体中文 W3");
    ft.setPixelSize(14);

    listWidget->clear();



    QList<StatisticBag> temp ;

    if(temp.isEmpty())
        return;

    for(int i=0;i<temp.length();i++){
        QString tempStr;
        int tempCount = temp.at(i).timeCount.toInt();
        if(temp.at(i).name.length()==3)
            tempStr = temp.at(i).name+QString("                             ")+QString::number(tempCount/3600)
                    +QString("时")+QString::number((tempCount/60)%60)+QString("分")
                    +QString::number(tempCount%60%60)+QString("秒");
        else if(temp.at(i).name.length()==2)
            tempStr = temp.at(i).name+QString("                                ")+QString::number(tempCount/3600)
                    +QString("时")+QString::number((tempCount/60)%60)+QString("分")
                    +QString::number(tempCount%60%60)+QString("秒");
        else if(temp.at(i).name.length()==4)
            tempStr = temp.at(i).name+QString("                          ")+QString::number(tempCount/3600)
                    +QString("时")+QString::number((tempCount/60)%60)+QString("分")
                    +QString::number(tempCount%60%60)+QString("秒");
        else
            tempStr = temp.at(i).name+QString("                           ")+QString::number(tempCount/3600)
                    +QString("时")+QString::number((tempCount/60)%60)+QString("分")
                    +QString::number(tempCount%60%60)+QString("秒");
        QListWidgetItem *userTimeItem = new QListWidgetItem();
        userTimeItem->setSizeHint(QSize(340,32));
        userTimeItem->setText(QString(" ")+tempStr);
        userTimeItem->setFont(ft);
        userTimeItem->setBackground(QColor(255,255,255));

        listWidget->addItem(userTimeItem);
    }
}

void InquirySpecificTimeDialog::slotSearchBtn()
{
    if(startYear->text().isEmpty() || startMonth->text().isEmpty() || startDay->text().isEmpty()
        || endYear->text().isEmpty() || endMonth->text().isEmpty() || endDay->text().isEmpty()){
        QMessageBox::about(this, "提示", "有些相关信息为空，请认真填写！");
    }
    else{
        int startY,startM,startD;
        int endY,endM,endD;
        startY = startYear->text().toInt(NULL,10);
        startM = startMonth->text().toInt(NULL,10);
        startD = startDay->text().toInt(NULL,10);

        endY = endYear->text().toInt(NULL,10);
        endM = endMonth->text().toInt(NULL,10);
        endD = endDay->text().toInt(NULL,10);

        if( startY<=0 || startY>9999|| startM<=0 || startM>12 || startD<=0 || startD>31){
            QMessageBox::about(this, "提示", "起始时间格式不正确，请认真填写！");
        }
        else if( endY<=0 || endY>9999|| endM<=0 || endM>12 || endD<=0 || endD>31){
            QMessageBox::about(this, "提示", "结束时间格式不正确，请认真填写！");
        }
        else{
            QDate startDate,endDate;
            startDate = QDate(startY,startM,startD);
            endDate = QDate(endY,endM,endD);
            showListResult(startDate.toString("yyyy-MM-dd"),endDate.toString("yyyy-MM-dd"));
        }
    }
}

void InquirySpecificTimeDialog::mousePressEvent(QMouseEvent *event)
{
    bPressFlag = true;
    beginDrag = event->pos();
    QWidget::mousePressEvent(event);
}

void InquirySpecificTimeDialog::mouseMoveEvent(QMouseEvent *event)
{
    if (bPressFlag) {
        QPoint relaPos(QCursor::pos() - beginDrag);
        move(relaPos);
    }
    QWidget::mouseMoveEvent(event);
}

void InquirySpecificTimeDialog::mouseReleaseEvent(QMouseEvent *event)
{
    bPressFlag = false;
    QWidget::mouseReleaseEvent(event);
}

void InquirySpecificTimeDialog::paintEvent(QPaintEvent *)
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

