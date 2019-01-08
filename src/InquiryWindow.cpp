#include "InquiryWindow.h"

InquiryWindow::InquiryWindow(QWidget *parent) : QWidget(parent)
{
    resize(652,320);
    userData = UserData::getUserData();
    http = DOHelper::getDOHelper();
    themeColor = userData->getThemeColor();
    initLayout();
//    showAllUserTime();
}

void InquiryWindow::initLayout()
{
    //背景设置
    QPalette pa;
    pa.setColor(QPalette::Background, QColor(230,230,230));
    this->setPalette(pa);
    this->setAutoFillBackground(true);

    pa.setColor(QPalette::WindowText,QColor(102,102,102));

    QFont ft;
    ft.setBold(true);
    ft.setFamily("冬青黑体简体中文 W3");
    ft.setPixelSize(14);

    weekCount = new QLabel(this);
    timeQualified = new QLabel(this);

    QLabel *triLabel;
    triLabel = new QLabel(this);
    triLabel->setPixmap(QPixmap(":images/tri.png"));
    triLabel->setGeometry(344,290,16,16);

    QLabel *text1 = new QLabel(this);
    QLabel *text2 = new QLabel(this);
    QLabel *text3 = new QLabel(this);

    text1->setText(tr("以"));
    text1->setFont(ft);
    text1->setPalette(pa);
    text1->move(48,88);

    text2->setText(tr("周计算"));
    text2->setFont(ft);
    text2->setPalette(pa);
    text2->move(128,88);

    text3->setText(tr("时间"));
    text3->setFont(ft);
    text3->setPalette(pa);
    text3->move(48,160);

    ft.setPixelSize(48);
    ft.setBold(true);

    if(themeColor==0){
        pa.setColor(QPalette::WindowText,QColor(85,195,239));
    }
    else if(themeColor==1){
        pa.setColor(QPalette::WindowText,QColor(138,230,199));
    }
    else if(themeColor==2){
        pa.setColor(QPalette::WindowText,QColor(255,178,102));
    }
    else{
        pa.setColor(QPalette::WindowText,QColor(255,127,127));
    }

    weekCount->setText(tr("1"));
    weekCount->setFont(ft);
    weekCount->setPalette(pa);
    weekCount->move(84,56);

    ft.setPixelSize(26);

    timeQualified->setText("...");
    timeQualified->setFont(ft);
    timeQualified->setPalette(pa);
    timeQualified->move(92,150);

    listWidget = new QListWidget(this);

    listWidget->setFrameShape(QListWidget::NoFrame);
    if(themeColor==0){
        listWidget->setStyleSheet(
                    "QListWidget{background:transparent;}"
                    "QListWidget::Item:hover{background:#F0F8FF; }"
                    "QListWidget::item:selected{background:white;color:#55C3EF; }"
                    "QScrollBar{background:transparent; height:10px; }"
                    );
    }
    else if(themeColor==1){
        listWidget->setStyleSheet(
                    "QListWidget{background:transparent;}"
                    "QListWidget::Item:hover{background:#F0FFF0; }"
                    "QListWidget::item:selected{background:white;color:#8AE6C7; }"
                    "QScrollBar{background:transparent; height:10px; }"
                    );
    }
    else if(themeColor==2){
        listWidget->setStyleSheet(
                    "QListWidget{background:transparent;}"
                    "QListWidget::Item:hover{background:#FFFAF0; }"
                    "QListWidget::item:selected{background:white;color:#FFD700; }"
                    "QScrollBar{background:transparent; height:10px; }"
                    );
    }
    else{
        listWidget->setStyleSheet(
                    "QListWidget{background:transparent;}"
                    "QListWidget::Item:hover{background:#FFF0FA; }"
                    "QListWidget::item:selected{background:white;color:#FF7F7F; }"
                    "QScrollBar{background:transparent; height:10px; }"
                    );
    }
    listWidget->move(240,0);
    listWidget->setIconSize(QSize(64, 40));
    listWidget->resize(384,288);

    connect(listWidget, SIGNAL(currentTextChanged(QString)),
            this, SLOT(changeIsQualified(QString)));
}

void InquiryWindow::changeIsQualified(QString currentText)
{
    int currentUserTime=0;
    bool flag = true;
    QString userTime;
    if(!currentText.isEmpty()){
        for(int i=0;i<currentText.length();i++){
            if(flag && currentText.at(i).isNumber()){
                userTime += QString(currentText.at(i));
                flag = false;
            }
            else if(!flag && currentText.at(i).isNumber()){
                userTime += QString(currentText.at(i));
            }
            else if(!flag && !currentText.at(i).isNumber())
                break;
        }
    }
    currentUserTime = userTime.toInt(NULL,10);

    if(currentUserTime>=24)
        timeQualified->setText("已达标");
    else
        timeQualified->setText("未达标");

    timeQualified->adjustSize();
}

void InquiryWindow::showAllUserTime()
{
    QFont ft;
    ft.setPixelSize(18);
    ft.setFamily("冬青黑体简体中文 W3");
    ft.setBold(false);

    if(!userData->getstartDate_all().isNull() && !userData->getendDate_all().isNull())
        http->getAllUserTimesRequst(QString(userData->getstartDate_all().toString("yyyy-MM-dd")),
                                    QString(userData->getendDate_all().toString("yyyy-MM-dd")));
    else
        return;

    QList<AllUsers> temp = userData->getAllUsers();

    if(temp.isEmpty())
        return;

    for(int i=0;i<temp.length();i++){
        QString avatarPath = ":/images/avatar"+QString::number(i%5+1)+".png";
        QString tempStr;
        int tempCount = temp.at(i).timeCount.toInt();
        if(temp.at(i).name.length()==3)
            tempStr = temp.at(i).name+QString("               ")+QString::number(tempCount/3600)
                    +QString("时")+QString::number((tempCount/60)%60)+QString("分")
                    +QString::number(tempCount%60%60)+QString("秒");
        else if(temp.at(i).name.length()==2)
            tempStr = temp.at(i).name+QString("                  ")+QString::number(tempCount/3600)
                    +QString("时")+QString::number((tempCount/60)%60)+QString("分")
                    +QString::number(tempCount%60%60)+QString("秒");
        else if(temp.at(i).name.length()==4)
            tempStr = temp.at(i).name+QString("            ")+QString::number(tempCount/3600)
                    +QString("时")+QString::number((tempCount/60)%60)+QString("分")
                    +QString::number(tempCount%60%60)+QString("秒");
        else
            tempStr = temp.at(i).name+QString("             ")+QString::number(tempCount/3600)
                    +QString("时")+QString::number((tempCount/60)%60)+QString("分")
                    +QString::number(tempCount%60%60)+QString("秒");
        QListWidgetItem *userTimeItem = new QListWidgetItem();
        userTimeItem->setSizeHint(QSize(360,48));
        userTimeItem->setIcon(QIcon(avatarPath));
        userTimeItem->setText(QString(" ")+tempStr);
        userTimeItem->setFont(ft);
        userTimeItem->setTextColor(QColor(184,184,184));
        userTimeItem->setBackground(QColor(242,242,242));

        QListWidgetItem *space = new QListWidgetItem();
        space->setSizeHint(QSize(360,12));
        space->setBackground(QColor(230,230,230));
        listWidget->addItem(userTimeItem);
        listWidget->addItem(space);
    }
    userData->clearAllUsers();
}
