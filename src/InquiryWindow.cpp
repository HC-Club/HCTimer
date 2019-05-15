#include "InquiryWindow.h"

InquiryWindow::InquiryWindow(QWidget *parent) : QWidget(parent)
{
    resize(652,320);
    themeColor = 0;
    initLayout();
}

void InquiryWindow::initLayout()
{
    //背景设置
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

    text1 = new QLabel(this);
    text2 = new QLabel(this);
    text3 = new QLabel(this);

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
    listWidget->setStyleSheet("QListWidget{background:rgb(230,230,230)}");

    listWidget->setFrameShape(QListWidget::NoFrame);
    setThemeColor(themeColor);
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

void InquiryWindow::setStatisticBags(const QList<StatisticBag> &list)
{
    QFont ft;
    ft.setPixelSize(18);
    ft.setFamily("冬青黑体简体中文 W3");
    ft.setBold(false);










    QList<StatisticBag> temp = list;


    for(int i=temp.size()-1;i>=0;i--)
    {
        const StatisticBag a = temp.at(i);
        if(a.top!=0)
        {
            continue;
        }

        if(a.timeCount=="0")
        {
            temp.removeAt(i);
        }
    }


    qSort(temp.begin(),temp.end(),Tool::compareStatisticBag);














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
}

void InquiryWindow::setUser(const User &user)
{
    setThemeColor(user.getThemeColor());
}

void InquiryWindow::setThemeColor(const int &_themeColor)
{
    themeColor = _themeColor;

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
    text1->setPalette(pa);
    text2->setPalette(pa);
    text3->setPalette(pa);
    weekCount->setPalette(pa);
    timeQualified->setPalette(pa);

}
