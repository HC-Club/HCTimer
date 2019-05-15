#include "DesktopWidget.h"

DesktopWidget::DesktopWidget(QWidget *parent)
    : QWidget(parent)
{
    settings = new QSettings("settings.ini", QSettings::IniFormat);
    tomatoTime = settings->value("TomatoConfig/tomatoTime",25).toInt();
    restTime = settings->value("TomatoConfig/restTime",5).toInt();
    longRestTime = settings->value("TomatoConfig/longRestTime",10).toInt();
    volume = settings->value("TomatoConfig/volume",60).toInt();
    isStartWorkSound = settings->value("TomatoConfig/isStartWorkSound",false).toBool();

//    tomatoTime = 3;//测试
//    restTime = 2;//测试
//    longRestTime = 1;//测试
//    volume=100;//测试
//    isStartWorkSound = true;//测试

    isInTomatoTime = false;
    isInRestTime = false;
    isInLongRestTime = false;
    countDownTime = -1;
    tomatoFinishedCount = 0;

    bPressFlag = false;

    monitor = Monitor::getMonitor();


    playList = new QMediaPlaylist(this);

    playList->addMedia(QMediaContent(QUrl(":sounds\\di_da_sound.mp3")));
    playList->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);

    cueMediaPlayer = new QMediaPlayer(this);
    cueMediaPlayer->setVolume(volume);

    workSoundPlayer = new QMediaPlayer(this);
    workSoundPlayer->setVolume(volume);

  //  workSoundPlayer->setPlaylist(playList);                               //神级bug代码，开了像病毒一样强，占30%CPU


    tomatoTimer = new QTimer(this);
    connect(tomatoTimer,SIGNAL(timeout()),this,SLOT(slotTomatoTimer()));

    initInterface();
}

void DesktopWidget::initInterface()
{
    QFont ft;
    ft.setBold(true);
    ft.setPixelSize(26);
    ft.setFamily("冬青黑体简体中文 W3");

    //设置图标不在任务栏显示以及无边框
    this->setWindowFlags(Qt::Tool | Qt::X11BypassWindowManagerHint | Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setWindowOpacity(0.7);//设置透明度
    resize(160, 160);

    updateBtn = new QPushButton(this);
    updateBtn->setStyleSheet("QPushButton{border-image: url(:images/info_logo.png);}"
                             "QPushButton:hover{border-image: url(:images/info_logo_hover.png);}"
                             "QPushButton:pressed{border-image: url(:images/info_logo_pressed.png);}");
    updateBtn->setGeometry(40,40,80,80);
    updateBtn->setToolTip(tr("更新在线时间"));
    connect(updateBtn, SIGNAL(clicked()), this, SLOT(slotUpdateBtn()));

    countDownTimeLabel = new QLabel(this);
    countDownTimeLabel->setFont(ft);
    countDownTimeLabel->setAlignment(Qt::AlignCenter);
    countDownTimeLabel->setGeometry(20,65,120,32);
    countDownTimeLabel->hide();

    startTomatoTime = new QAction(tr("开始一个番茄"), this);
    connect(startTomatoTime, SIGNAL(triggered()), this, SLOT(slotStartTomatoTime()));
    editAndCheckTask = new QAction(tr("查看并编辑任务"), this);
    connect(editAndCheckTask, SIGNAL(triggered()), this, SLOT(slotEditAndCheckTask()));
    widgetSettings = new QAction(tr("设置"), this);
    connect(widgetSettings, SIGNAL(triggered()), this, SLOT(slotWidgetSettings()));
    close = new QAction(tr("关闭"), this);
    connect(close, SIGNAL(triggered()), this, SLOT(slotClose()));

    menu=new QMenu(this);
    menu->addAction(startTomatoTime);
    menu->addAction(editAndCheckTask);
    menu->addAction(widgetSettings);
    menu->addAction(close);

    move(QApplication::desktop()->width()-180,5);
}

void DesktopWidget::slotUpdateBtn()
{

}

void DesktopWidget::slotStartTomatoTime()
{
    if(isInTomatoTime){
        QMessageBox::StandardButton rb = QMessageBox::question(this, "提示", "当前处于番茄任务中，是否放弃此番茄?", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        if(rb == QMessageBox::Yes){
            countDownTime = tomatoTime*60;
            isInTomatoTime = true;

            updateBtn->hide();
            countDownTimeLabel->show();
            tomatoTimer->start(1000);
            if(isStartWorkSound){
                workSoundPlayer->play();
            }
        }
        else
            return;
    }
    else{
        countDownTime = tomatoTime*60;
        isInTomatoTime = true;

        updateBtn->hide();
        countDownTimeLabel->show();
        tomatoTimer->start(1000);
        if(isStartWorkSound){
            workSoundPlayer->play();
        }
    }

    qDebug()<<"开始计时器"<<tomatoFinishedCount<<"Rest"<<isInRestTime<<"longRe"<<isInLongRestTime<<"tomaT"<<isInTomatoTime;
}

void DesktopWidget::slotEditAndCheckTask()
{
    EditTaskDialog editTaskDialog;
    editTaskDialog.exec();
}

void DesktopWidget::slotWidgetSettings()
{
    DWSettingDialog dWSettingDialog;
    dWSettingDialog.exec();
}

void DesktopWidget::slotClose()
{
    if(isInTomatoTime){
        QMessageBox::StandardButton rb = QMessageBox::question(this, "提示", "当前处于番茄任务中，是否放弃此番茄?", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        if(rb == QMessageBox::Yes){
            cueMediaPlayer->stop();
            if(isStartWorkSound)
                workSoundPlayer->stop();
            tomatoTimer->stop();
            isInTomatoTime = false;
            isInRestTime = false;
            isInLongRestTime = false;
            countDownTime = -1;
            countDownTimeLabel->setText(tr(""));
            if(!countDownTimeLabel->isHidden())
                countDownTimeLabel->hide();
            if(updateBtn->isHidden())
                updateBtn->show();
            this->hide();
        }
        else
            return;
    }
    else{
        cueMediaPlayer->stop();
        tomatoTimer->stop();
        isInTomatoTime = false;
        isInRestTime = false;
        isInLongRestTime = false;
        countDownTime = -1;
        countDownTimeLabel->setText(tr(""));
        if(!countDownTimeLabel->isHidden())
            countDownTimeLabel->hide();
        if(updateBtn->isHidden())
            updateBtn->show();
        this->hide();
    }

}

void DesktopWidget::slotTomatoTimer()
{
    if(countDownTime >= 0){
        countDownTimeLabel->setText(QString::number(countDownTime/60)+":"+QString::number(countDownTime%60));
        countDownTime--;
        repaint();
//            qDebug()<<"番茄计时器运行中..."<<tomatoFinishedCount<<"Rest"<<isInRestTime<<"longRe"<<isInLongRestTime<<"tomaT"<<isInTomatoTime;
    }
    else if(tomatoFinishedCount<3 && isInTomatoTime){
        tomatoFinishedCount++;
        cueMediaPlayer->setMedia(QMediaContent(QUrl(":sounds\\after_class.mp3")));
        if(isStartWorkSound)
            workSoundPlayer->stop();
        cueMediaPlayer->play();
        QMessageBox::StandardButton rb = QMessageBox::question(this, "提示", "一个番茄计时任务已结束，是否进入短休息时间段?", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        if(rb == QMessageBox::Yes){
            cueMediaPlayer->stop();
            if(isStartWorkSound)
                workSoundPlayer->stop();
            isInRestTime = true;
            isInTomatoTime = false;
            isInLongRestTime = false;
            countDownTime = restTime*60;
        }
        else{
            cueMediaPlayer->stop();
            if(isStartWorkSound)
                workSoundPlayer->stop();
            tomatoTimer->stop();
            isInTomatoTime = false;
            isInRestTime = false;
            isInLongRestTime = false;
            countDownTimeLabel->hide();
            updateBtn->show();
        }
    }
    else if(isInRestTime){
        cueMediaPlayer->setMedia(QMediaContent(QUrl(":sounds\\class.mp3")));
        if(isStartWorkSound)
            workSoundPlayer->stop();
        cueMediaPlayer->play();
        QMessageBox::StandardButton rb = QMessageBox::question(this, "提示", "短休息时间段已结束，是否进入另一个番茄任务?", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        if(rb == QMessageBox::Yes){
            cueMediaPlayer->stop();
            if(isStartWorkSound){
                workSoundPlayer->play();
            }
            isInTomatoTime = true;
            isInRestTime = false;
            isInLongRestTime = false;
            countDownTime = tomatoTime*60;
        }
        else{
            cueMediaPlayer->stop();
            if(isStartWorkSound)
                workSoundPlayer->stop();
            tomatoTimer->stop();
            isInTomatoTime = false;
            isInRestTime = false;
            isInLongRestTime = false;
            countDownTimeLabel->hide();
            updateBtn->show();
        }
    }
    else if(tomatoFinishedCount>=3 && isInTomatoTime){
        cueMediaPlayer->setMedia(QMediaContent(QUrl(":sounds\\after_class.mp3")));
        if(isStartWorkSound)
            workSoundPlayer->stop();
        cueMediaPlayer->play();
        QMessageBox::StandardButton rb = QMessageBox::question(this, "提示", "目前已完成多个番茄计时任务，是否进入长休息时间段?", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        if(rb == QMessageBox::Yes){
            cueMediaPlayer->stop();
            if(isStartWorkSound)
                workSoundPlayer->stop();
            cueMediaPlayer->setMedia(QMediaContent(QUrl(":sounds\\moonlight_in_the_city.mp3")));
            cueMediaPlayer->play();
            tomatoFinishedCount = 0;
            isInTomatoTime = false;
            isInRestTime = false;
            isInLongRestTime = true;
            countDownTime = longRestTime*60;
        }
        else{
            cueMediaPlayer->stop();
            if(isStartWorkSound)
                workSoundPlayer->stop();
            tomatoTimer->stop();
            isInTomatoTime = false;
            isInRestTime = false;
            isInLongRestTime = false;
            countDownTimeLabel->hide();
            updateBtn->show();
        }
    }
    else if(isInLongRestTime){
        cueMediaPlayer->setMedia(QMediaContent(QUrl(":sounds\\class.mp3")));
        if(isStartWorkSound)
            workSoundPlayer->stop();
        cueMediaPlayer->play();
        QMessageBox::StandardButton rb = QMessageBox::question(this, "提示", "长休息时间段已结束，是否进入另一个番茄任务?", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        if(rb == QMessageBox::Yes){
            cueMediaPlayer->stop();
            if(isStartWorkSound){
                workSoundPlayer->play();
            }
            isInTomatoTime = true;
            isInRestTime = false;
            isInLongRestTime = false;
            countDownTime = tomatoTime*60;
        }
        else{
            cueMediaPlayer->stop();
            workSoundPlayer->stop();
            tomatoTimer->stop();
            isInTomatoTime = false;
            isInRestTime = false;
            isInLongRestTime = false;
            countDownTimeLabel->hide();
            updateBtn->show();
        }
    }
    else{
        qDebug()<<"异常错误";
    }

}

void DesktopWidget::contextMenuEvent(QContextMenuEvent *) //右键菜单项编辑
{
    QCursor cur=this->cursor();
    menu->exec(cur.pos()); //关联到光标
}

void DesktopWidget::paintEvent(QPaintEvent *)
{

    if(countDownTime >= 0 && isInTomatoTime)
        circleValue = 100-100*countDownTime/tomatoTime/60;
    else if(countDownTime >= 0 && isInRestTime)
        circleValue = 100-100*countDownTime/restTime/60;
    else if(countDownTime >= 0 && isInLongRestTime)
        circleValue = 100-100*countDownTime/longRestTime/60;
    else
        return;

    QPainter painter(this);

    painter.translate(width() / 2, height() / 2);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.rotate(180);

    painter.setPen(QPen(QColor(255,0,0), 6));
    for (int i = 0; i < circleValue ; ++i) {
        painter.drawLine(0, 73, 0, 73);
        painter.rotate(3.6);
    }
}

/*********以下三个函数用于解决无系统默认边框无法移动窗口问题********/
/**
 * @brief DesktopWidget::mousePressEvent 鼠标按下事件
 * @param event
 */

void DesktopWidget::mousePressEvent(QMouseEvent *event)
{
    bPressFlag = true;
    beginDrag = event->pos();
    QWidget::mousePressEvent(event);
}

/**
 * @brief DesktopWidget::mouseMoveEvent 鼠标移动事件
 * @param event
 */
void DesktopWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (bPressFlag) {
        QPoint relaPos(QCursor::pos() - beginDrag);
        move(relaPos);
    }
    QWidget::mouseMoveEvent(event);
}

/**
 * @brief DesktopWidget::mouseReleaseEvent 鼠标释放事件
 * @param event
 */
void DesktopWidget::mouseReleaseEvent(QMouseEvent *event)
{
    bPressFlag = false;
    QWidget::mouseReleaseEvent(event);
}
