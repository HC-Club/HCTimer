#include "SettingDialog.h"

SettingDialog::SettingDialog(QDialog *parent) : QDialog(parent)
{
    settings = new QSettings("settings.ini", QSettings::IniFormat);
    isAutoBoot = settings->value("Config/isAutoBoot",true).toBool();
    isStartDesktopWidget = settings->value("Config/isStartDesktopWidget",true).toBool();
    themeColor = settings->value("Config/themeColor",0).toInt();

    isChangeSettings = false;
    resize(260,292);
    bPressFlag = false;
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    //白色背景设置
    QPalette bgPalette;
    bgPalette.setColor(QPalette::Background, QColor("#FFF"));
    this->setPalette(bgPalette);
    this->setAutoFillBackground(true);
    initLayout();
}

void SettingDialog::setColorBtnGeometry(int _themeColor)
{
    switch(_themeColor)
    {
        case 0:
            blueBtn->setGeometry(42,218,32,32);
            break;
        case 1:
            greenBtn->setGeometry(90,218,32,32);
            break;
        case 2:
            orangeBtn->setGeometry(138,218,32,32);
            break;
        case 3:
            redBtn->setGeometry(186,218,32,32);
            break;
        default:
            blueBtn->setGeometry(42,218,32,32);
            break;
    }
}

void SettingDialog::initLayout()
{
    QFont ft;
    ft.setPixelSize(15);
    ft.setFamily("冬青黑体简体中文 W3");

    closeBtn = new QPushButton(this);
    closeBtn->setGeometry(222,14,25,25);
    closeBtn->setStyleSheet("QPushButton{border-image: url(:images/close_small.png);}"
                            "QPushButton:hover{border-image: url(:images/close_small_hover.png);}"
                            "QPushButton:pressed{border-image: url(:images/close_small.png);}");
    connect(closeBtn,SIGNAL(clicked()),this,SLOT(slotCloseBtn()));

    settingTitle = new QLabel(this);
    settingTitle->setFont(ft);
    settingTitle->setText("设置");
    settingTitle->setStyleSheet("background-color:none;color:#B8B8B8;border:none;");
    settingTitle->setGeometry(32,42,80,20);

    autoBoot = new QCheckBox(" 开机自启动", this);
    autoBoot->setChecked(isAutoBoot);
    autoBoot->setGeometry(74,90,112,32);
    connect(autoBoot,SIGNAL(toggled(bool )),
                this,SLOT(slotAutoBoot(bool )));

    startDesktopWidget = new QCheckBox(" 开启桌面插件", this);
    startDesktopWidget->setChecked(isStartDesktopWidget);
    startDesktopWidget->setGeometry(74,132,112,32);
    connect(startDesktopWidget,SIGNAL(toggled(bool )),
                this,SLOT(slotStartDesktopWidget(bool )));

    themeTitle = new QLabel(this);
    themeTitle->setFont(ft);
    themeTitle->setText("更换主题颜色");
    themeTitle->setStyleSheet("background-color:none;color:#B8B8B8;border:none;");
    themeTitle->setGeometry(32,186,112,20);

    blueBtn = new QPushButton(this);
    blueBtn->setStyleSheet("background-color:#4FCFFF;border:none;");
    blueBtn->setGeometry(48,224,16,16);
    connect(blueBtn,SIGNAL(clicked()),
                this,SLOT(slotBlueBtn()));

    greenBtn = new QPushButton(this);
    greenBtn->setStyleSheet("background-color:#8AE6C7;border:none;");
    greenBtn->setGeometry(96,224,16,16);
    connect(greenBtn,SIGNAL(clicked()),
                this,SLOT(slotGreenBtn()));

    orangeBtn = new QPushButton(this);
    orangeBtn->setStyleSheet("background-color:#FFB266;border:none;");
    orangeBtn->setGeometry(146,224,16,16);
    connect(orangeBtn,SIGNAL(clicked()),
                this,SLOT(slotOrangeBtn()));

    redBtn = new QPushButton(this);
    redBtn->setStyleSheet("background-color:#FF7F7F;border:none;");
    redBtn->setGeometry(194,224,16,16);
    connect(redBtn,SIGNAL(clicked()),
                this,SLOT(slotRedBtn()));

    setColorBtnGeometry(themeColor);
}

void SettingDialog::slotAutoBoot(bool b)
{
    if(!isChangeSettings)
        isChangeSettings = true;
    isAutoBoot = b;
}

void SettingDialog::slotStartDesktopWidget(bool b)
{
    if(!isChangeSettings)
        isChangeSettings = true;
    isStartDesktopWidget = b;
}

void SettingDialog::setAutoBoot(bool _isAutoBoot)
{
    QString applicationName = QApplication::applicationName();
    QSettings *settings_1 = new QSettings(REG_RUN, QSettings::NativeFormat);
    if(_isAutoBoot)
    {
        QString applicationPath = QApplication::applicationFilePath();
        settings_1->setValue(applicationName, applicationPath.replace("/", "\\"));
    }
    else
    {
        settings_1->remove(applicationName);
    }
    delete settings_1;
}


void SettingDialog::slotBlueBtn()
{
    if(!isChangeSettings)
        isChangeSettings = true;
    themeColor = 0;
    greenBtn->setGeometry(96,224,16,16);
    orangeBtn->setGeometry(146,224,16,16);
    redBtn->setGeometry(194,224,16,16);
    blueBtn->setGeometry(42,218,32,32);
}

void SettingDialog::slotGreenBtn()
{
    if(!isChangeSettings)
        isChangeSettings = true;
    themeColor = 1;
    blueBtn->setGeometry(48,224,16,16);
    orangeBtn->setGeometry(146,224,16,16);
    redBtn->setGeometry(194,224,16,16);
    greenBtn->setGeometry(90,218,32,32);
}

void SettingDialog::slotOrangeBtn()
{
    if(!isChangeSettings)
        isChangeSettings = true;
    themeColor = 2;
    blueBtn->setGeometry(48,224,16,16);
    greenBtn->setGeometry(96,224,16,16);
    redBtn->setGeometry(194,224,16,16);
    orangeBtn->setGeometry(138,218,32,32);
}

void SettingDialog::slotRedBtn()
{
    if(!isChangeSettings)
        isChangeSettings = true;
    themeColor = 3;
    blueBtn->setGeometry(48,224,16,16);
    greenBtn->setGeometry(96,224,16,16);
    orangeBtn->setGeometry(146,224,16,16);
    redBtn->setGeometry(186,218,32,32);
}

void SettingDialog::slotCloseBtn()
{
    if(isChangeSettings){
        settings->setValue("Config/themeColor",themeColor);
        settings->setValue("Config/isStartDesktopWidget",isStartDesktopWidget);
        settings->setValue("Config/isAutoBoot",isAutoBoot);
        setAutoBoot(isAutoBoot);
    }
    emit sSetting(themeColor);
    this->close();
}

void SettingDialog::mousePressEvent(QMouseEvent *event)
{
    bPressFlag = true;
    beginDrag = event->pos();
    QWidget::mousePressEvent(event);
}

void SettingDialog::mouseMoveEvent(QMouseEvent *event)
{
    if (bPressFlag) {
        QPoint relaPos(QCursor::pos() - beginDrag);
        move(relaPos);
    }
    QWidget::mouseMoveEvent(event);
}

void SettingDialog::mouseReleaseEvent(QMouseEvent *event)
{
    bPressFlag = false;
    QWidget::mouseReleaseEvent(event);
}

void SettingDialog::paintEvent(QPaintEvent *)
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
