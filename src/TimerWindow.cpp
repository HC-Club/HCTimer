#include "TimerWindow.h"

TimerWindow::TimerWindow(QWidget *parent)
    : QWidget(parent)
{
    userData = UserData::getUserData();
    monitor = Monitor::getMonitor();
    http = DOHelper::getDOHelper();

    applicationVersion = QString("HC Timer V")+VERSION_STR;

    settings = new QSettings("settings.ini", QSettings::IniFormat);
    themeColor = settings->value("Config/themeColor",0).toInt(NULL);
    userData->setThemeColor(themeColor);

    if(!settings->value("Config/isStartDesktopWidget").isNull())
        isStartDesktopWidget = settings->value("Config/isStartDesktopWidget",false).toBool();

    isClose = false;
    isNameLableChanged = false;
    loginDetectCount = 0;
    serverTimeDetectCount = 0;
    getUpdateVersionsCount = 0;

    desktopWidget = new DesktopWidget();
    if(isStartDesktopWidget)
        desktopWidget->show();
    else
        desktopWidget->hide();

    initLayout();

    createConnect();

    resize(672,452);

    if(!readConfigToLogin()){
        trayIcon->showMessage(applicationVersion,
                              tr("你好，请登录"),
                              QSystemTrayIcon::Information,200);
    }

    updater = new Updater(this);
    getUpdateVersionsCount = 0;


    detect = new QTimer(this);//用于刷新界面，还有对是否登陆的监控
    connect(detect,SIGNAL(timeout()),this,SLOT(slotDetect()));
    detect->start(1000);
}

void TimerWindow::runCMD(QString command)
{
#if WINDOWS_VERSION

    if(command.isEmpty()) return ;
//    system(command);
//    WinExec(command,SW_HIDE);
//    ShellExecute(NULL, "open", "shutdown.exe", "-s", "C:\WINDOWS\system32", SW_SHOWNORMAL);
//    ShellExecute(NULL, "open", "cmd.exe", "", "C:\WINDOWS\system32", SW_HIDE);
    QByteArray ba = command.toLatin1();
    char *cmd = ba.data();
    ShellExecuteA(NULL,"open",QByteArray(cmd),NULL,NULL,SW_SHOWNORMAL);

#endif
}

void TimerWindow::updateApp()
{
    updater->setTimerWindow(this);
    updater->startRequest(userData->downloadURL);
}

/**
 * @brief TimerWindow::closeEvent 用于控制点击主窗口关闭按钮时的行为
 */
void TimerWindow::closeEvent(QCloseEvent *event)
{
    if(isClose == false){
        event->ignore(); //忽略退出信号，回到窗口本身，程序继续运行
        this->hide();//隐藏窗口
    }else{
        event->accept();//接受退出信号让关闭事件通过，并顺利关闭窗口，程序退出
    }
}

TimerWindow::~TimerWindow()
{

}

/**
 * @brief TimerWindow::initLayout 初始化布局
 */
void TimerWindow::initLayout()
{
    //创建系统托盘
    createTrayIcon();

    this->setWindowTitle(tr("HC Timer"));
    this->setWindowIcon(QIcon(":images/icon_240x240.png"));

    //不使用系统默认标题栏
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);

    titleBar=new TitleBar();
    homeWindow=new HomeWindow();
    noticeWindow = new NoticeWindow();
    statisticsWindow = new StatisticsWindow();
    inquiryWindow = new InquiryWindow();
    tabBar=new TabBar();
    vLayoutMain=new QVBoxLayout();

    titleBar->setFixedSize(652,64);
    homeWindow->setFixedSize(652,304);
    noticeWindow->setFixedSize(652,304);
    statisticsWindow->setFixedSize(652,304);
    inquiryWindow->setFixedSize(652,304);
    tabBar->setFixedSize(652,64);

    vLayoutMain->addWidget(titleBar);
    vLayoutMain->addWidget(homeWindow);
    vLayoutMain->addWidget(noticeWindow);
    vLayoutMain->addWidget(statisticsWindow);
    vLayoutMain->addWidget(inquiryWindow);
    vLayoutMain->addWidget(tabBar);

    vLayoutMain->setAlignment(titleBar, Qt::AlignCenter|Qt::AlignBottom);
    vLayoutMain->setAlignment(homeWindow, Qt::AlignCenter);
    vLayoutMain->setAlignment(noticeWindow, Qt::AlignCenter);
    vLayoutMain->setAlignment(statisticsWindow, Qt::AlignCenter);
    vLayoutMain->setAlignment(inquiryWindow, Qt::AlignCenter);
    vLayoutMain->setAlignment(tabBar, Qt::AlignCenter|Qt::AlignTop);

    vLayoutMain->setSpacing(0);
    vLayoutMain->setContentsMargins(0,0,0,0);

    noticeWindow->hide();
    statisticsWindow->hide();
    inquiryWindow->hide();
    this->setLayout(vLayoutMain);
    setTabBarStyle(themeColor,0);
}

/**
 * @brief TimerWindow::createConnect 建立信号和槽
 */
void TimerWindow::createConnect()
{
    connect(titleBar->avatarBtn,SIGNAL(clicked()),
            this,SLOT(slotLogin()));
    connect(titleBar->btnAddNotice, SIGNAL(clicked()),
            this, SLOT(slotBtnAddNoticeClicked()));
    connect(titleBar->btnInquirySpecificTime, SIGNAL(clicked()),
            this, SLOT(slotBtnInquirySpecificTime()));
    connect(titleBar->btnSettings, SIGNAL(clicked()),
            this, SLOT(slotBtnSettingsClicked()));
    connect(titleBar->btnMinimize, SIGNAL(clicked()),
            this, SLOT(slotBtnMinimizeClicked()));
    connect(titleBar->btnClose, SIGNAL(clicked()),
            this, SLOT(slotBtnCloseClicked()));
    connect(tabBar->btnHome, SIGNAL(clicked()),
            this, SLOT(slotBtnHomeClicked()));
    connect(tabBar->btnNotice,SIGNAL(clicked()),
            this,SLOT(slotBtnNoticeClicked()));
    connect(tabBar->btnStatistics,SIGNAL(clicked()),
            this,SLOT(slotBtnStatisticsClicked()));
    connect(tabBar->btnInquiry,SIGNAL(clicked()),
            this,SLOT(slotBtnInquiryClicked()));
    connect(tabBar->btnAbout,SIGNAL(clicked()),
            this,SLOT(slotAboutClicked()));
}

/**
 * @brief TimerWindow::creatTrayIcon 新建系统托盘图标
 */
void TimerWindow::createTrayIcon()
{
    trayIcon = SystemTrayIcon::getInstance();
    trayIcon->setIcon(QIcon(":images/icon_48x48.png"));
    trayIcon->setToolTip(tr("HC Timer"));

    trayMenu = new QMenu(this);

    trayMenu->addAction(tr("显示桌面小工具"), this, SLOT(slotShowDesktopWidget()));
    trayMenu->addAction(tr("显示主程序"), this, SLOT(slotShowMainWindow()));
    trayMenu->addAction(tr("更新时间"), this, SLOT(slotUpdateTime()));
    trayMenu->addAction(tr("关于"), this, SLOT(slotOpenUpdateUrl()));
    trayMenu->addSeparator();
    trayMenu->addAction(tr("退出"), this, SLOT(slotCloseApplication()));
    trayIcon->setContextMenu(trayMenu);

    trayIcon->show();

    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(slotTrayIconClicked(QSystemTrayIcon::ActivationReason)));
    connect(trayIcon, SIGNAL(messageClicked()),
            this, SLOT(slotShowMainWindow()));
}

/**
 * @brief TimerWindow::readConfigToLogin 读取配置文件sittings.ini并登录
 */
bool TimerWindow::readConfigToLogin()
{
    QString account;
    QString password;
    QString userID;

    userID = settings->value("UserData/id").toString();
    account = settings->value("UserData/account").toString();
    password = settings->value("UserData/password").toString();

    if(!userData->getServerDate().isValid() || !userData->isGetServerTime){
        http->getServerDateRequst();
    }
    if(!userID.isEmpty())
        userData->setUserID(userID);
    else
        return false;

    if(!account.isEmpty())
        userData->setUserAccount(account);
    else
        return false;

    if(!password.isEmpty())
        userData->setUserPassWord(password);
    else
        return false;

    return true;
}

/**
 * @brief TimerWindow::slotDetect 定时器监控函数，用于监控网络延时造成用户名标签没更新，
 *                                没有获取服务器时间，没有登录等情况
 */
void TimerWindow::slotDetect()
{
    homeWindow->updateUserData();
    if(userData->isLogin && !userData->getUserName().isEmpty())
    {
        titleBar->nameLable->setText(userData->getUserName());
        isNameLableChanged = false;
    }
    else
    {
        if(!isNameLableChanged)
        {
            titleBar->nameLable->setText(tr("请登录"));
//            userData->initData();
            isNameLableChanged = true;
        }
    }
//    qDebug()<<userData->isGetServerTime<<"服务器时间："<<userData->getServerDate().isValid()<<"  "<<userData->getServerDate();
    //判断是否获取服务器时间，没有获取请求获取，然后将获取服务器时间计数器置零，时间间隔为10分钟
    if(!userData->getServerDate().isValid() || !userData->isGetServerTime){
        serverTimeDetectCount++;
        if(serverTimeDetectCount > 600){
            http->getServerDateRequst();
            serverTimeDetectCount = 0;
        }
    }
    //判断是否登录，没有登录请求登录，然后将登录计数器置零，时间间隔为30分钟
    if(!userData->isLogin){
        loginDetectCount++;
        if(loginDetectCount > 1800){
            if(!readConfigToLogin()){
                trayIcon->showMessage(applicationVersion,
                                      tr("你好，请登录"),
                                      QSystemTrayIcon::Information,200);
            }
            else{
                http->loginRequst(userData->getUserAccount(),userData->getUserPassword());
            }
            loginDetectCount = 0;
        }
    }

    //判断是否获取服务器计时器更新版本号,都没有获取到则15秒后再次获取，最多获取1次
    if(!userData->isGetUpdateVersion && getUpdateVersionsCount != -1){
        getUpdateVersionsCount++;
        if(getUpdateVersionsCount > 15){
            http->getUpdateVersionsRequst();
            getUpdateVersionsCount = -1;
        }
    }
    else if(userData->isGetUpdateVersion && getUpdateVersionsCount == -1){
        getUpdateVersionsCount = -2;
        QString currentVersion = VERSION_STR;
        if(userData->updateVersions.toFloat() > currentVersion.toFloat())
        {
            updateApp();
        }
    }
}

/**
 * @brief TimerWindow::slotLogin() 登录按钮响应槽
 */
void TimerWindow::slotLogin()
{
    if(userData->isLogin && !userData->getUserName().isEmpty())
    {
        titleBar->avatarBtn->setToolTip(tr("查看用户信息"));
        UserInfoDialog userInfoDialog;
        userInfoDialog.move(this->pos().x()+152,this->pos().y()+32);
        userInfoDialog.exec();
    }
    else
    {
        titleBar->avatarBtn->setToolTip(tr("登录"));
        LoginDialog loginWidget;
        QString account = settings->value("UserData/account").toString();
        QString password = settings->value("UserData/password").toString();
        loginWidget.accountEdit->setText(account);
        loginWidget.passwordEdit->setText(password);
        loginWidget.move(this->pos().x()+208,this->pos().y()+64);
        loginWidget.exec();
    }
}

/**
 * @brief TimerWindow::slotBtnEditNoticeClicked 添加公告按钮响应槽
 */
void TimerWindow::slotBtnAddNoticeClicked()
{
    AddNoticeDialog addNoticeDialog;
    addNoticeDialog.move(this->pos().x()+208,this->pos().y()+64);
    addNoticeDialog.exec();
}

/**
 * @brief TimerWindow::slotBtnInquirySpecificTime 查询具体时间响应槽
 */
void TimerWindow::slotBtnInquirySpecificTime()
{
    InquirySpecificTimeDialog inquirySpecificTimeDialog;
    inquirySpecificTimeDialog.move(this->pos().x()+128,this->pos().y()+60);
    inquirySpecificTimeDialog.exec();
}
/**
 * @brief TimerWindow::slotBtnSettingsClicked 设置按钮响应槽
 */
void TimerWindow::slotBtnSettingsClicked()
{
    SettingDialog settingDialog;
    settingDialog.move(this->pos().x()+208,this->pos().y()+64);
    settingDialog.exec();
}

/**
 * @brief TimerWindow::slotBtnMinimizeClicked 最小化按钮响应槽
 */
void TimerWindow::slotBtnMinimizeClicked()
{
    this->showMinimized();
}

/**
 * @brief TimerWindow::slotBtnCloseClicked 关闭按钮响应槽
 */
void TimerWindow::slotBtnCloseClicked()
{
    if(trayIcon->isVisible()){
        this->hide();
    }else{
        this->close();
    }
}

void TimerWindow::setTabBarStyle(int themeColor,int tabBarPressedFlag)
{
    if(themeColor == 0)
    {
        tabBar->btnNotice->setStyleSheet(
                "QPushButton{border: none;}"
                "QPushButton:hover{background:white;color:#55C3EF; }"
                "QPushButton:pressed{background:white;color:#4682B4; }"
                );
        tabBar->btnStatistics->setStyleSheet(
                "QPushButton{border: none;}"
                "QPushButton:hover{background:white;color:#55C3EF; }"
                "QPushButton:pressed{background:white;color:#4682B4; }"
                );
        tabBar->btnInquiry->setStyleSheet(
                "QPushButton{border: none;}"
                "QPushButton:hover{background:white;color:#55C3EF; }"
                "QPushButton:pressed{background:white;color:#4682B4; }"
                );
        tabBar->btnHome->setStyleSheet(
                "QPushButton{border: none;}"
                "QPushButton:hover{background:white;color:#55C3EF; }"
                "QPushButton:pressed{background:white;color:#4682B4; }"
                );
        if(tabBarPressedFlag == 0)
        {
            tabBar->btnHome->setStyleSheet(
                "QPushButton{border: none;color:#55C3EF;}"
                "QPushButton:hover{background:white;color:#55C3EF; }"
                "QPushButton:pressed{background:white;color:#4682B4; }"
                );
        }
        else if(tabBarPressedFlag == 1)
        {
            tabBar->btnNotice->setStyleSheet(
                "QPushButton{border: none;color:#55C3EF;}"
                "QPushButton:hover{background:white;color:#55C3EF; }"
                "QPushButton:pressed{background:white;color:#4682B4; }"
                );
        }
        else if(tabBarPressedFlag == 2)
        {
            tabBar->btnStatistics->setStyleSheet(
                "QPushButton{border: none;color:#55C3EF;}"
                "QPushButton:hover{background:white;color:#55C3EF; }"
                "QPushButton:pressed{background:white;color:#4682B4; }"
                );
        }
        else
        {
            tabBar->btnInquiry->setStyleSheet(
                "QPushButton{border: none;color:#55C3EF;}"
                "QPushButton:hover{background:white;color:#55C3EF; }"
                "QPushButton:pressed{background:white;color:#4682B4; }"
                );
        }


    }
    else if(themeColor == 1)
    {
        tabBar->btnNotice->setStyleSheet(
                "QPushButton{border: none;}"
                "QPushButton:hover{background:white;color:#8AE6C7; }"
                "QPushButton:pressed{background:white;color:#90EE90; }"
                );
        tabBar->btnStatistics->setStyleSheet(
                "QPushButton{border: none;}"
                "QPushButton:hover{background:white;color:#8AE6C7; }"
                "QPushButton:pressed{background:white;color:#90EE90; }"
                );
        tabBar->btnInquiry->setStyleSheet(
                "QPushButton{border: none;}"
                "QPushButton:hover{background:white;color:#8AE6C7; }"
                "QPushButton:pressed{background:white;color:#90EE90; }"
                );
        tabBar->btnHome->setStyleSheet(
                "QPushButton{border: none;}"
                "QPushButton:hover{background:white;color:#8AE6C7; }"
                "QPushButton:pressed{background:white;color:#90EE90; }"
                );
        if(tabBarPressedFlag == 0)
        {
            tabBar->btnHome->setStyleSheet(
                "QPushButton{border: none;color:#8AE6C7;}"
                "QPushButton:hover{background:white;color:#8AE6C7; }"
                "QPushButton:pressed{background:white;color:#90EE90; }"
                );
        }
        else if(tabBarPressedFlag == 1)
        {
            tabBar->btnNotice->setStyleSheet(
                "QPushButton{border: none;color:#8AE6C7;}"
                "QPushButton:hover{background:white;color:#8AE6C7; }"
                "QPushButton:pressed{background:white;color:#90EE90; }"
                );
        }
        else if(tabBarPressedFlag == 2)
        {
            tabBar->btnStatistics->setStyleSheet(
                "QPushButton{border: none;color:#8AE6C7;}"
                "QPushButton:hover{background:white;color:#8AE6C7; }"
                "QPushButton:pressed{background:white;color:#90EE90; }"
                );
        }
        else
        {
            tabBar->btnInquiry->setStyleSheet(
                "QPushButton{border: none;color:#8AE6C7;}"
                "QPushButton:hover{background:white;color:#8AE6C7; }"
                "QPushButton:pressed{background:white;color:#90EE90; }"
                );
        }
    }
    else if(themeColor == 2)
    {
        tabBar->btnNotice->setStyleSheet(
                "QPushButton{border: none;}"
                "QPushButton:hover{background:white;color:#FFB266; }"
                "QPushButton:pressed{background:white;color:#FFD700; }"
                );
        tabBar->btnStatistics->setStyleSheet(
                "QPushButton{border: none;}"
                "QPushButton:hover{background:white;color:#FFB266; }"
                "QPushButton:pressed{background:white;color:#FFD700; }"
                );
        tabBar->btnInquiry->setStyleSheet(
                "QPushButton{border: none;}"
                "QPushButton:hover{background:white;color:#FFB266; }"
                "QPushButton:pressed{background:white;color:#FFD700; }"
                );
        tabBar->btnHome->setStyleSheet(
                "QPushButton{border: none;}"
                "QPushButton:hover{background:white;color:#FFB266; }"
                "QPushButton:pressed{background:white;color:#FFD700; }"
                );
        if(tabBarPressedFlag == 0)
        {
            tabBar->btnHome->setStyleSheet(
                "QPushButton{border: none;color:#FFB266;}"
                "QPushButton:hover{background:white;color:#FFB266; }"
                "QPushButton:pressed{background:white;color:#FFD700; }"
                );
        }
        else if(tabBarPressedFlag == 1)
        {
            tabBar->btnNotice->setStyleSheet(
                "QPushButton{border: none;color:#FFB266;}"
                "QPushButton:hover{background:white;color:#FFB266; }"
                "QPushButton:pressed{background:white;color:#FFD700; }"
                );
        }
        else if(tabBarPressedFlag == 2)
        {
            tabBar->btnStatistics->setStyleSheet(
                "QPushButton{border: none;color:#FFB266;}"
                "QPushButton:hover{background:white;color:#FFB266; }"
                "QPushButton:pressed{background:white;color:#FFD700; }"
                );
        }
        else
        {
            tabBar->btnInquiry->setStyleSheet(
                "QPushButton{border: none;color:#FFB266;}"
                "QPushButton:hover{background:white;color:#FFB266; }"
                "QPushButton:pressed{background:white;color:#FFD700; }"
                );
        }
    }
    else
    {
        tabBar->btnNotice->setStyleSheet(
                "QPushButton{border: none;}"
                "QPushButton:hover{background:white;color:#FF7F7F; }"
                "QPushButton:pressed{background:white;color:#FF0000; }"
                );
        tabBar->btnStatistics->setStyleSheet(
                "QPushButton{border: none;}"
                "QPushButton:hover{background:white;color:#FF7F7F; }"
                "QPushButton:pressed{background:white;color:#FF0000; }"
                );
        tabBar->btnInquiry->setStyleSheet(
                "QPushButton{border: none;}"
                "QPushButton:hover{background:white;color:#FF7F7F; }"
                "QPushButton:pressed{background:white;color:#FF0000; }"
                );
        tabBar->btnHome->setStyleSheet(
                "QPushButton{border: none;}"
                "QPushButton:hover{background:white;color:#FF7F7F; }"
                "QPushButton:pressed{background:white;color:#FF0000; }"
                );
        if(tabBarPressedFlag == 0)
        {
            tabBar->btnHome->setStyleSheet(
                "QPushButton{border: none;color:#FF7F7F;}"
                "QPushButton:hover{background:white;color:#FF7F7F; }"
                "QPushButton:pressed{background:white;color:#FF0000; }"
                );
        }
        else if(tabBarPressedFlag == 1)
        {
            tabBar->btnNotice->setStyleSheet(
                "QPushButton{border: none;color:#FF7F7F;}"
                "QPushButton:hover{background:white;color:#FF7F7F; }"
                "QPushButton:pressed{background:white;color:#FF0000; }"
                );
        }
        else if(tabBarPressedFlag == 2)
        {
            tabBar->btnStatistics->setStyleSheet(
                "QPushButton{border: none;color:#FF7F7F;}"
                "QPushButton:hover{background:white;color:#FF7F7F; }"
                "QPushButton:pressed{background:white;color:#FF0000; }"
                );
        }
        else
        {
            tabBar->btnInquiry->setStyleSheet(
                "QPushButton{border: none;color:#FF7F7F;}"
                "QPushButton:hover{background:white;color:#FF7F7F; }"
                "QPushButton:pressed{background:white;color:#FF0000; }"
                );
        }
    }
}

/**
 * @brief TimerWindow::slotBtnHomeClicked 首页按钮响应槽
 */
void TimerWindow::slotBtnHomeClicked()
{
    titleBar->btnAddNotice->hide();
    titleBar->btnInquirySpecificTime->hide();

    noticeWindow->close();
    statisticsWindow->close();
    inquiryWindow->close();
    setTabBarStyle(themeColor,0);
    homeWindow->show();
}

/**
 * @brief TimerWindow::slotBtnNoticeClicked 公告按钮响应槽
 */
void TimerWindow::slotBtnNoticeClicked()
{
    noticeWindow->noticeWidget->showCurrentNotice();

    titleBar->btnInquirySpecificTime->hide();
    titleBar->btnAddNotice->show();

    homeWindow->close();
    statisticsWindow->close();
    inquiryWindow->close();
    setTabBarStyle(themeColor,1);
    noticeWindow->show();
}

/**
 * @brief TimerWindow::slotBtnStatisticsClicked 统计按钮响应槽
 */
void TimerWindow::slotBtnStatisticsClicked()
{
    statisticsWindow->setTimeCoord();

    titleBar->btnInquirySpecificTime->hide();
    titleBar->btnAddNotice->hide();
    homeWindow->close();
    noticeWindow->close();
    inquiryWindow->close();
    setTabBarStyle(themeColor,2);
    statisticsWindow->show();
}

/**
 * @brief TimerWindow::slotBtnInquiryClicked 查询按钮响应槽
 */
void TimerWindow::slotBtnInquiryClicked()
{
    titleBar->btnAddNotice->hide();
    titleBar->btnInquirySpecificTime->show();

    inquiryWindow->listWidget->clear();
    inquiryWindow->showAllUserTime();
    homeWindow->close();
    noticeWindow->close();
    statisticsWindow->close();
    setTabBarStyle(themeColor,3);
    inquiryWindow->show();

}

/**
 * @brief TimerWindow::slotAboutClicked 关于按钮响应槽
 */
void TimerWindow::slotAboutClicked()
{
    AboutDialog aboutDialog;
    aboutDialog.move(this->pos().x()+208,this->pos().y()+64);
    aboutDialog.exec();
}

/**
 * @brief TimerWindow::slotTrayIconClicked 系统托盘点击相应槽
 * @param reason
 */
void TimerWindow::slotTrayIconClicked(QSystemTrayIcon::ActivationReason reason)
{
    switch(reason)
    {
        case QSystemTrayIcon::Trigger:
            this->show();
            break;
        case QSystemTrayIcon::DoubleClick:
            if(monitor->isUserOnline()){
                trayIcon->showMessage(tr("HC Timer正在计时"),
                                  QString("今日在线时间为: ")+userData->getOnlineTime(),
                                  QSystemTrayIcon::Information,200);
            }
            else
            {
                trayIcon->showMessage(applicationVersion,
                                      tr("不处于合法网络"),
                                      QSystemTrayIcon::Information,200);
            }
            break;
        default:
            break;
    }
}

/**
 * @brief TimerWindow::slotShowMainWindow 系统托盘显示主界面
 */
void TimerWindow::slotShowMainWindow()
{
    this->setWindowState(Qt::WindowActive);
    this->show();
}

/**
 * @brief TimerWindow::slotUpdateTime 系统托盘更新响应槽
 */
void TimerWindow::slotUpdateTime()
{
    if(monitor->isCanUpdate()){
        if(userData->isLogin && !userData->getUserID().isEmpty() && !userData->getServerDate().isNull())
            http->updateRecordRequst(userData->getUserID(),userData->getServerDate().toString(Qt::ISODate),
                                 userData->getTodayTime()+userData->getTimeCount());
    }
    else{
        trayIcon->showMessage(applicationVersion,
                              tr("更新失败"),
                              QSystemTrayIcon::Information,200);
    }
}

/**
 * @brief TimerWindow::slotCloseApplication 系统托盘退出响应槽
 */
void TimerWindow::slotCloseApplication()
{
    isClose = true;
    this->close();
}

/**
 * @brief TimerWindow::slotShowDesktopWidget 系统托盘显示桌面插件响应槽
 */
void TimerWindow::slotShowDesktopWidget()
{
    if(desktopWidget->isHidden()){
        desktopWidget->show();
    }
    else
        return;
}

/**
 * @brief TimerWindow::slotOpenUpdateUrl 系统托盘打开更新计时器链接响应槽
 */
void TimerWindow::slotOpenUpdateUrl()
{
    QDesktopServices::openUrl(QUrl("http://bbs.hclab.cn/bbs/forum.php?mod=viewthread&tid=598&extra="));
}

/*********以下三个函数用于解决无系统默认边框无法移动窗口问题********/
/**
 * @brief TimerWindow::mousePressEvent 鼠标按下事件
 * @param event
 */

void TimerWindow::mousePressEvent(QMouseEvent *event)
{
    bPressFlag = true;
    beginDrag = event->pos();
    QWidget::mousePressEvent(event);
}

/**
 * @brief TimerWindow::mouseMoveEvent 鼠标移动事件
 * @param event
 */
void TimerWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (bPressFlag) {
        QPoint relaPos(QCursor::pos() - beginDrag);
        move(relaPos);
    }
    QWidget::mouseMoveEvent(event);
}

/**
 * @brief TimerWindow::mouseReleaseEvent 鼠标释放事件
 * @param event
 */
void TimerWindow::mouseReleaseEvent(QMouseEvent *event)
{
    bPressFlag = false;
    QWidget::mouseReleaseEvent(event);
}

/**
 * @brief TimerWindow::paintEvent 用于绘阴影
 */
void TimerWindow::paintEvent(QPaintEvent *)
{
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);
    path.addRect(10, 10, this->width()-20, this->height()-20);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.fillPath(path, QBrush(Qt::white));

    QColor color(180, 180, 180, 50);//CMYK模式颜色

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
