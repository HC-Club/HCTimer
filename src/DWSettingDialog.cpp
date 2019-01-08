#include "DWSettingDialog.h"

DWSettingDialog::DWSettingDialog(QDialog *parent) : QDialog(parent)
{
    settings = new QSettings("settings.ini", QSettings::IniFormat);
    tomatoTime = settings->value("TomatoConfig/tomatoTime",25).toInt();
    restTime = settings->value("TomatoConfig/restTime",5).toInt();
    longRestTime = settings->value("TomatoConfig/longRestTime",10).toInt();
    volume = settings->value("TomatoConfig/volume",70).toInt();
    isStartWorkSound = settings->value("TomatoConfig/isStartWorkSound",false).toBool();
    isChangeSettings = false;
    resize(342,378);

    bPressFlag = false;
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    //白色背景设置
    QPalette bgPalette;
    bgPalette.setColor(QPalette::Background, QColor("#FFF"));
    this->setPalette(bgPalette);
    this->setAutoFillBackground(true);
    initInterface();
}

void DWSettingDialog::initInterface()
{
    QFont ft;
    ft.setFamily("冬青黑体简体中文 W3");

    closeBtn = new QPushButton(this);
    closeBtn->setGeometry(300,14,25,25);
    closeBtn->setStyleSheet("QPushButton{border-image: url(:images/close_small.png);}"
                            "QPushButton:hover{border-image: url(:images/close_small_hover.png);}"
                            "QPushButton:pressed{border-image: url(:images/close_small.png);}");
    connect(closeBtn,SIGNAL(clicked()),this,SLOT(slotCloseBtn()));

    ft.setPixelSize(16);
    tomatoTimeLabel = new QLabel(this);
    tomatoTimeLabel->setFont(ft);
    tomatoTimeLabel->setText(tr("番茄时间"));
    tomatoTimeLabel->setGeometry(32,42,80,20);

    tomatoTimeSlider = new QSlider(Qt::Horizontal,this);
    tomatoTimeSlider->setMinimum(10);
    tomatoTimeSlider->setMaximum(60);
    tomatoTimeSlider->setValue(tomatoTime);
    tomatoTimeSlider->setGeometry(62,75,180,20);
    connect(tomatoTimeSlider, SIGNAL(valueChanged(int)), this, SLOT(slotSetTomatoTime(int)));

    ft.setPixelSize(12);
    tomatoValueLabel = new QLabel(this);
    tomatoValueLabel->setFont(ft);
    tomatoValueLabel->setText(QString::number(tomatoTime)+"min");
    tomatoValueLabel->setGeometry(265,69,70,20);

    ft.setPixelSize(16);
    restTimeLabel = new QLabel(this);
    restTimeLabel->setFont(ft);
    restTimeLabel->setText(tr("休息时间"));
    restTimeLabel->setGeometry(32,106,80,20);

    restTimeSlider = new QSlider(Qt::Horizontal,this);
    restTimeSlider->setMinimum(1);
    restTimeSlider->setMaximum(35);
    restTimeSlider->setValue(restTime);
    restTimeSlider->setGeometry(62,139,180,20);
    connect(restTimeSlider, SIGNAL(valueChanged(int)), this, SLOT(slotSetRestTime(int)));

    ft.setPixelSize(12);
    restValueLabel = new QLabel(this);
    restValueLabel->setFont(ft);
    restValueLabel->setText(QString::number(restTime)+"min");
    restValueLabel->setGeometry(265,133,70,20);

    ft.setPixelSize(16);
    longRestTimeLabel = new QLabel(this);
    longRestTimeLabel->setFont(ft);
    longRestTimeLabel->setText(tr("长休息时间"));
    longRestTimeLabel->setGeometry(32,170,80,20);

    longRestTimeSlider = new QSlider(Qt::Horizontal,this);
    longRestTimeSlider->setMinimum(5);
    longRestTimeSlider->setMaximum(55);
    longRestTimeSlider->setValue(longRestTime);
    longRestTimeSlider->setGeometry(62,203,180,20);
    connect(longRestTimeSlider, SIGNAL(valueChanged(int)), this, SLOT(slotSetLongRestTime(int)));

    ft.setPixelSize(12);
    longRestValueLabel = new QLabel(this);
    longRestValueLabel->setFont(ft);
    longRestValueLabel->setText(QString::number(longRestTime)+"min");
    longRestValueLabel->setGeometry(265,197,70,20);


    /*******音效部分*******/
    ft.setPixelSize(16);
    soundEffectTitle = new QLabel(this);
    soundEffectTitle->setFont(ft);
    soundEffectTitle->setText(tr("音效设置"));
    soundEffectTitle->setGeometry(32,235,80,20);

    ft.setPixelSize(12);
    volumeLabel = new QLabel(this);
    volumeLabel->setFont(ft);
    volumeLabel->setText(tr("音量"));
    volumeLabel->setStyleSheet("background-color:none;color:#666666;border:none;");
    volumeLabel->setGeometry(60,265,80,20);

    volumeSlider = new QSlider(Qt::Horizontal,this);
    volumeSlider->setMinimum(0);
    volumeSlider->setMaximum(200);
    volumeSlider->setValue(volume);
    volumeSlider->setGeometry(62,293,180,10);
    connect(volumeSlider, SIGNAL(valueChanged(int)), this, SLOT(slotSetVolume(int)));

    ft.setPixelSize(10);
    volumeValueLabel = new QLabel(this);
    volumeValueLabel->setFont(ft);
    volumeValueLabel->setText(QString::number(volume));
    volumeValueLabel->setStyleSheet("background-color:none;color:#666666;border:none;");
    volumeValueLabel->setGeometry(265,280,70,20);

    startWorkSound = new QCheckBox(" 开启嘀嗒声", this);
    startWorkSound->setStyleSheet("background-color:none;color:#666666;border:none;");
    startWorkSound->setGeometry(62,310,112,32);
    startWorkSound->setChecked(isStartWorkSound);
    connect(startWorkSound,SIGNAL(toggled(bool )),
                this,SLOT(slotStartWorkSound(bool )));

}

void DWSettingDialog::slotCloseBtn()
{
    if(isChangeSettings){
        settings->setValue("TomatoConfig/tomatoTime",tomatoTimeSlider->value());
        settings->setValue("TomatoConfig/restTime",restTimeSlider->value());
        settings->setValue("TomatoConfig/longRestTime",longRestTimeSlider->value());
        settings->setValue("TomatoConfig/volume",volumeSlider->value());
        settings->setValue("TomatoConfig/isStartWorkSound",isStartWorkSound);
        QMessageBox::about(this,"温馨提示","您的设置信息已保存，将在下次启动应用程序时生效！");
    }
    this->hide();
}

void DWSettingDialog::slotSetTomatoTime(int value)
{
    if(!isChangeSettings)
        isChangeSettings = true;
    tomatoValueLabel->setText(QString::number(value)+"min");
}

void DWSettingDialog::slotSetRestTime(int value)
{
    if(!isChangeSettings)
        isChangeSettings = true;
    restValueLabel->setText(QString::number(value)+"min");
}

void DWSettingDialog::slotSetLongRestTime(int value)
{
    if(!isChangeSettings)
        isChangeSettings = true;
    longRestValueLabel->setText(QString::number(value)+"min");
}

void DWSettingDialog::slotSetVolume(int value)
{
    if(!isChangeSettings)
        isChangeSettings = true;
    volumeValueLabel->setText(QString::number(value));
}

void DWSettingDialog::slotStartWorkSound(bool b)
{
    if(!isChangeSettings)
        isChangeSettings = true;
    isStartWorkSound = b;
}

void DWSettingDialog::mousePressEvent(QMouseEvent *event)
{
    bPressFlag = true;
    beginDrag = event->pos();
    QWidget::mousePressEvent(event);
}

void DWSettingDialog::mouseMoveEvent(QMouseEvent *event)
{
    if (bPressFlag) {
        QPoint relaPos(QCursor::pos() - beginDrag);
        move(relaPos);
    }
    QWidget::mouseMoveEvent(event);
}

void DWSettingDialog::mouseReleaseEvent(QMouseEvent *event)
{
    bPressFlag = false;
    QWidget::mouseReleaseEvent(event);
}

void DWSettingDialog::paintEvent(QPaintEvent *)
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
