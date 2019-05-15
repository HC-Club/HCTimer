#include "HomeWindow.h"

HomeWindow::HomeWindow(QWidget *parent) : QWidget(parent)
{
//    setAttribute(Qt::WA_TranslucentBackground);

    resize(652,320);

    totalTimeVaule = 0;
    autoUpdate = 0;

    level = 0;

    themeColor = 0;

    createView();

    titleLable->adjustSize();

    timerOpacity = new QTimer(this);
    connect(timerOpacity,SIGNAL(timeout()),this,SLOT(DoUpdateBtnAnimation()));

    showhour->setText(QString::number(hour));
    showminute->setText(QString::number(minute));
    showsecond->setText(QString::number(second));

    showhour->adjustSize();
    showminute->adjustSize();
    showsecond->adjustSize();
    setTimer(0,0);
}

HomeWindow::~HomeWindow()
{

}

void HomeWindow::setUser(const User &user)
{
    setTimer(user.getTodayCount(),user.getTotalCount());

    setDates(user.getToday(),user.getBegin(),user.getEnd());
    setThemeColor(user.getThemeColor());
}

void HomeWindow::setDates(const QDate &today, const QDate &begin, const QDate &end)
{
    QDate todayDate = today;
    QDate beginDate = begin;
    QDate endDate = end;

    year[0]->setText(QString::number(todayDate.year()));
    year[1]->setText(QString::number(beginDate.year()));
    year[2]->setText(QString::number(endDate.year()));

    if(todayDate.month()<10)
        month[0]->setText(" "+QString::number(todayDate.month()));
    else
        month[0]->setText(QString::number(todayDate.month()));
    if(beginDate.month()<10)
        month[1]->setText(" "+QString::number(beginDate.month()));
    else
        month[1]->setText(QString::number(beginDate.month()));
    if(endDate.month()<10)
        month[2]->setText(" "+QString::number(endDate.month()));
    else
        month[2]->setText(QString::number(endDate.month()));

    if(todayDate.day()<10)
        day[0]->setText(" "+QString::number(todayDate.day()));
    else
        day[0]->setText(QString::number(todayDate.day()));
    if(beginDate.day()<10)
        day[1]->setText(" "+QString::number(beginDate.day()));
    else
        day[1]->setText(QString::number(beginDate.day()));
    if(endDate.day()<10)
        day[2]->setText(" "+QString::number(endDate.day()));
    else
        day[2]->setText(QString::number(endDate.day()));


    if(todayDate.dayOfWeek()==1){
        date->setText(tr("星期一"));
    }
    else if(todayDate.dayOfWeek()==2){
        date->setText(tr("星期二"));
    }
    else if(todayDate.dayOfWeek()==3){
        date->setText(tr("星期三"));
    }
    else if(todayDate.dayOfWeek()==4){
        date->setText(tr("星期四"));
    }
    else if(todayDate.dayOfWeek()==5){
        date->setText(tr("星期五"));
    }
    else if(todayDate.dayOfWeek()==6){
        date->setText(tr("星期六"));
    }
    else if(todayDate.dayOfWeek()==7){
        date->setText(tr("星期日"));
    }
    date->adjustSize();
    year[0]->adjustSize();year[0]->adjustSize();
    year[1]->adjustSize();year[0]->adjustSize();
    year[2]->adjustSize();year[0]->adjustSize();
    month[0]->adjustSize();
    month[1]->adjustSize();
    month[2]->adjustSize();
    day[0]->adjustSize();
    day[1]->adjustSize();
    day[2]->adjustSize();
}

void HomeWindow::setTimer(int today, int total)
{
    totalTimeVaule = total*200/HOURS_WEEK;
    hour=today/3600;
    minute=today%3600/60;
    second=today%60;

    if(hour<10){
        showhour->setText(" "+QString::number(hour));
    }
    else{
        showhour->setText(QString::number(hour));
    }
    if(minute<10){
        showminute->setText("0"+QString::number(minute));
    }
    else{
        showminute->setText(QString::number(minute));
    }
    if(second<10){
        showsecond->setText("0"+QString::number(second));
    }
    else{
        showsecond->setText(QString::number(second));
    }

    showhour->adjustSize();
    showminute->adjustSize();
    showsecond->adjustSize();
    update();
}

void HomeWindow::PlayUpdateBtnAnimation()
{
    level = 0;
    addOne->move(movePos[level]);
    addOne->show();
    timerOpacity->stop();
    timerOpacity->start(120);
}

void HomeWindow::createView()
{
    //背景设置
    QPalette bgPalette;
    bgPalette.setColor(QPalette::Background, QColor(230,230,230));
    this->setPalette(bgPalette);
    this->setAutoFillBackground(true);

    QColor textColor(102,102,102);
    QColor headColor(184,184,184);

    QFont ft;
    ft.setPixelSize(14);
    ft.setFamily("冬青黑体简体中文 W3");

    todayLable = new QLabel(this);
    todayLable->setText(tr("今天"));

    date = new QLabel(this);

    toLable = new QLabel(this);
    toLable->setText(tr("至"));

    weekLable = new QLabel(this);
    weekLable->setText(tr("本周"));

    titleLable = new QLabel(this);
    titleLable->setText("今日在线");

    headLable = new QLabel(this);
    headLable->setText("24h");


    hourLable = new QLabel(this);
    hourLable->setText("时");
    showhour = new QLabel(this);

    minuteLable = new QLabel(this);
    minuteLable->setText("分");
    showminute = new QLabel(this);

    secondLable = new QLabel(this);
    secondLable->setText("秒");
    showsecond = new QLabel(this);

    ft.setBold(true);
    date->setFont(ft);
    headLable->setFont(ft);
    titleLable->setFont(ft);
    hourLable->setFont(ft);
    minuteLable->setFont(ft);
    secondLable->setFont(ft);
    toLable->setFont(ft);

    triLabel = new QLabel(this);
    triLabel->setPixmap(QPixmap(":images/tri.png"));
    triLabel->setGeometry(56,290,16,16);

    QPalette pa;
    pa.setColor(QPalette::WindowText,headColor);
    headLable->setPalette(pa);

    pa.setColor(QPalette::WindowText,textColor);
    date->setPalette(pa);
    todayLable->setPalette(pa);
    weekLable->setPalette(pa);
    toLable->setPalette(pa);
    titleLable->setPalette(pa);
    hourLable->setPalette(pa);
    minuteLable->setPalette(pa);
    secondLable->setPalette(pa);

    showhour->setPalette(pa);
    showminute->setPalette(pa);
    showsecond->setPalette(pa);

    for(int i=0;i<3;i++){
        year[i] = new QLabel(this);
        year[i]->setText(tr(""));
        year[i]->setFont(ft);
        year[i]->setPalette(pa);
        yearLable[i] = new QLabel(this);
        yearLable[i]->setText(tr("年"));
        yearLable[i]->setFont(ft);
        yearLable[i]->setPalette(pa);
        month[i] = new QLabel(this);
        month[i]->setText(tr(""));
        month[i]->setFont(ft);
        month[i]->setPalette(pa);
        monthLable[i] = new QLabel(this);
        monthLable[i]->setText(tr("月"));
        monthLable[i]->setFont(ft);
        monthLable[i]->setPalette(pa);
        day[i] = new QLabel(this);
        day[i]->setText(tr(""));
        day[i]->setFont(ft);
        day[i]->setPalette(pa);
        dayLable[i] = new QLabel(this);
        dayLable[i]->setText(tr("日"));
        dayLable[i]->setFont(ft);
        dayLable[i]->setPalette(pa);
    }

    ft.setPixelSize(32);

    showhour->setFont(ft);
    showminute->setFont(ft);
    showsecond->setFont(ft);
    ft.setPixelSize(28);
    ft.setBold(false);
    todayLable->setFont(ft);
    weekLable->setFont(ft);

    headLable->move(368,0);

    titleLable->move(354,104);

    showhour->move(286,134);
    hourLable->move(332,150);

    showminute->move(352,134);
    minuteLable->move(396,150);

    showsecond->move(416,134);
    secondLable->move(460,150);

    int n=10;

    todayLable->move(48,40+n);
    date->move(114,56+n);

    year[0]->move(48,84+n);
    yearLable[0]->move(90,84+n);
    month[0]->move(108,84+n);
    monthLable[0]->move(130,84+n);
    day[0]->move(148,84+n);
    dayLable[0]->move(170,84+n);
    weekLable->move(48,120+n);

    year[1]->move(48,164+n);
    yearLable[1]->move(90,164+n);
    month[1]->move(108,164+n);
    monthLable[1]->move(130,164+n);
    day[1]->move(148,164+n);
    dayLable[1]->move(170,164+n);

    toLable->move(190,164+n);

    month[2]->move(108,194+n);
    monthLable[2]->move(130,194+n);
    day[2]->move(148,194+n);
    dayLable[2]->move(170,194+n);
    year[2]->move(48,194+n);
    yearLable[2]->move(90,194+n);

    updateBtn = new QPushButton(this);
    updateBtn->resize(65,30);
    updateBtn->move(550,255);
    updateBtn->setText("刷新");

    ft.setPixelSize(16);
    ft.setBold(true);
    addOne = new QLabel(this);
    addOne->setFont(ft);
    addOne->setText("+1");
    addOne->move(595,228);
    addOne->hide();

    setThemeColor(themeColor);
}

void HomeWindow::setThemeColor(const int &_themeColor)
{
    themeColor = _themeColor;
    if(themeColor==0){
        updateBtn->setStyleSheet(
                "QPushButton{background-color:#4FCFFF;color:white;border:none;border-radius:4px;}"
                "QPushButton:pressed{background-color:#87CEFA;}");
        addOne->setStyleSheet("background-color:none;color:#4FCFFF;border:none;");
    }
    else if(themeColor==1){
        updateBtn->setStyleSheet(
                "QPushButton{background-color:#8AE6C7;color:white;border:none;border-radius:4px;}"
                "QPushButton:pressed{background-color:#90EE90;}");
        addOne->setStyleSheet("background-color:none;color:#8AE6C7;border:none;");
    }
    else if(themeColor==2){
        updateBtn->setStyleSheet(
                "QPushButton{background-color:#FFB266;color:white;border:none;border-radius:4px;}"
                "QPushButton:pressed{background-color:#FFD700;}");
        addOne->setStyleSheet("background-color:none;color:#FFB266;border:none;");
    }
    else{
        updateBtn->setStyleSheet(
                "QPushButton{background-color:#FF7F7F;color:white;border:none;border-radius:4px;}"
                "QPushButton:pressed{background-color:#FF0000;}");
        addOne->setStyleSheet("background-color:none;color:#FF7F7F;border:none;");
    }
}

void HomeWindow::DoUpdateBtnAnimation()
{
    if(level>9){
        level = 0;
        addOne->move(movePos[level]);
        addOne->hide();
        timerOpacity->stop();
        return;
    }
    QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect(addOne);
    addOne->setGraphicsEffect(opacityEffect);
    opacityEffect->setOpacity(opacity[level]);
    addOne->move(movePos[level]);
    level++;
}

void HomeWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QColor basicColor(184,184,184);
    QColor timeColor;
    if(themeColor==0)
        timeColor.setRgb(79,207,255);
    else if(themeColor==1)
        timeColor.setRgb(138,230,199);
    else if(themeColor==2)
        timeColor.setRgb(255,178,102);
    else
        timeColor.setRgb(255,127,127);


    painter.translate(width() / 2+60, height() / 2);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.rotate(180);

    painter.setPen(QPen(basicColor, 5));
    for (int i = 0; i < 200 ; ++i) {
        painter.drawLine(0, 125, 0, 125);
        painter.rotate(1.8);
    }

    painter.setPen(QPen(timeColor, 5));
    for (int i = 0; i < totalTimeVaule ; ++i) {
        painter.drawLine(0, 125 , 0, 125);
        painter.rotate(1.8);
    }
}
