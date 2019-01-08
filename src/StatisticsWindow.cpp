#include "StatisticsWindow.h"

StatisticsWindow::StatisticsWindow(QWidget *parent) : QWidget(parent)
{
    //背景设置
    QPalette bgPalette;
    bgPalette.setColor(QPalette::Background, QColor(230,230,230));
    this->setPalette(bgPalette);
    this->setAutoFillBackground(true);

    resize(652,320);

    userData = UserData::getUserData();
    themeColor = userData->getThemeColor();
    initTimeCoord();
    createLable();

    todayNum = 7;
}

void StatisticsWindow::createLable()
{
    in = new QLabel(this);
    dayCount = new QLabel(this);
    day = new QLabel(this);
    count = new QLabel(this);
    hourCount = new QLabel(this);
    hour = new QLabel(this);

    triLabel = new QLabel(this);
    triLabel->setPixmap(QPixmap(":images/tri.png"));
    triLabel->setGeometry(248,290,16,16);

    QFont ft;
    ft.setBold(true);
    ft.setFamily("冬青黑体简体中文 W3");
    ft.setPixelSize(14);
    QPalette pa;
    pa.setColor(QPalette::WindowText,QColor(184,184,184));

    for(int i=0;i<7;i++)
    {
        timeLable[i] = new QLabel(this);
        weekLable[i] = new QLabel(this);
        timeLable[i]->setFont(ft);
        weekLable[i]->setFont(ft);
        timeLable[i]->setPalette(pa);
        weekLable[i]->setPalette(pa);
    }

    ft.setPixelSize(16);
    in->setFont(ft);
    day->setFont(ft);
    count->setFont(ft);
    hour->setFont(ft);

    pa.setColor(QPalette::WindowText,QColor(102,102,102));
    in->setPalette(pa);
    day->setPalette(pa);
    count->setPalette(pa);
    hour->setPalette(pa);

    ft.setPixelSize(48);

    if(themeColor==0)
        pa.setColor(QPalette::WindowText,QColor(85,195,239));
    else if(themeColor==1)
        pa.setColor(QPalette::WindowText,QColor(138,230,199));
    else if(themeColor==2)
        pa.setColor(QPalette::WindowText,QColor(255,178,102));
    else
        pa.setColor(QPalette::WindowText,QColor(255,127,127));

    dayCount->setFont(ft);
    hourCount->setFont(ft);
    dayCount->setPalette(pa);
    hourCount->setPalette(pa);

    in->setText(tr("在"));
    dayCount->setText(tr("7"));
    day->setText(tr("天里"));
    count->setText(tr("累计"));
    hour->setText(tr("小时"));

    timeLable[0]->setText(tr("0"));
    timeLable[1]->setText(tr("2"));
    timeLable[2]->setText(tr("4"));
    timeLable[3]->setText(tr("6"));
    timeLable[4]->setText(tr("8"));
    timeLable[5]->setText(tr("10"));
    timeLable[6]->setText(tr("12+"));

    weekLable[0]->setText(tr("Mon"));
    weekLable[1]->setText(tr("Tue"));
    weekLable[2]->setText(tr("Wed"));
    weekLable[3]->setText(tr("Thu"));
    weekLable[4]->setText(tr("Fri"));
    weekLable[5]->setText(tr("Sat"));
    weekLable[6]->setText(tr("Sun"));

    for(int i=0;i<5;i++)
    {
        timeLable[i]->move(264,232-i*32);
    }
    timeLable[5]->move(256,72);
    timeLable[6]->move(252,40);

    for(int i=0;i<7;i++)
    {
        weekLable[i]->move(292+48*i,248);
    }

    in->move(48,80);
    dayCount->move(78,55);
    day->move(112,80);
    count->move(48,160);
    hourCount->move(89,135);
    hour->move(158,160);
}

void StatisticsWindow::initTimeCoord()
{
    for(int i=0;i<7;i++)
    {
        timeCoord[i].setX(306+i*48);
        timeCoord[i].setY(240);
    }
}

void StatisticsWindow::setTimeCoord()
{
    if(userData->getServerDate().isNull())
        return;
    int temp,i;
    for(i=0;i<userData->getServerDate().dayOfWeek()-1;i++)
    {
        temp = 240 - (int)((float)userData->userTime[i]/43200*192);
        if(userData->userTime[i] > 43200)
            temp = 48;
        timeCoord[i].setY(temp);
    }
    temp = 240 - (int)((float)(userData->userTime[i] + userData->getTimeCount())/43200*192);
    if(userData->userTime[i] > 43200)
        temp = 48;
    timeCoord[i].setY(temp);
    update();
}

void StatisticsWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setPen(Qt::white);
    painter.setBrush(Qt::white);
    painter.drawRect(240,16,384,256);
    painter.setPen(Qt::gray);
    for(int i=0;i<7;i++)
    {
       painter.drawLine(288,48+i*32,608,48+i*32);
    }
    painter.setRenderHint( QPainter::Antialiasing, true );

    if(themeColor==0){
        painter.setBrush(QColor(85,195,239));
        painter.setPen(QColor(85,195,239));
    }
    else if(themeColor==1){
        painter.setBrush(QColor(138,230,199));
        painter.setPen(QColor(138,230,199));
    }
    else if(themeColor==2){
        painter.setBrush(QColor(255,178,102));
        painter.setPen(QColor(255,178,102));
    }
    else{
        painter.setBrush(QColor(255,127,127));
        painter.setPen(QColor(255,127,127));
    }

    if(!userData->getServerDate().isNull()){
        todayNum = userData->getServerDate().dayOfWeek();
    }
    else{
        todayNum = 7;
    }
    for(int i=0; i < todayNum-1; i++)
    {
        painter.drawLine(timeCoord[i],timeCoord[i+1]);
    }
    for(int i=0; i < todayNum; i++)
    {
       painter.drawEllipse(timeCoord[i],3,3);
    }

    int totalTime = userData->getTotalTime()/3600;
    if(totalTime<10)
    {
        hourCount->setText(" "+QString::number(totalTime));
    }
    else
    {
        hourCount->setText(QString::number(totalTime));
    }
    hourCount->adjustSize();
}
