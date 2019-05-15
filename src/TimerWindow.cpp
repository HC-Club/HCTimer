#include "TimerWindow.h"

static int local_active = 0;
HHOOK keyHook = NULL;
HHOOK mouseHook = NULL;

LRESULT CALLBACK keyProc(int ,WPARAM ,LPARAM )
{
    local_active = 0;//键盘事件正在发生，将监测时间置0
    return 0;//返回0表示将接受到的键盘信息返回，返回1表示将接收的键盘信息截住
}

LRESULT CALLBACK mouseProc(int ,WPARAM ,LPARAM )
{
    local_active =0;//鼠标事件正在发生，将监测时间置0
    return 0;//返回0表示将接受到的鼠标信息返回，返回1表示将接收的鼠标信息截住
}

void unHook()
{
    UnhookWindowsHookEx(keyHook);
    UnhookWindowsHookEx(mouseHook);
}

void setHook()
{
    keyHook =SetWindowsHookEx( WH_KEYBOARD_LL,keyProc,GetModuleHandle(NULL),0);//底层键盘钩子
    mouseHook =SetWindowsHookEx( WH_MOUSE_LL,mouseProc,GetModuleHandle(NULL),0);//底层鼠标钩子
}

TimerWindow::TimerWindow(QWidget *parent)
    : QWidget(parent)
{
    applicationVersion = QString("HC Timer V")+VERSION_STR;

    settings = new QSettings("settings.ini", QSettings::IniFormat);
    themeColor = settings->value("Config/themeColor",0).toInt(NULL);

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

    //加入
    local_timer = new QTimer();

    local_runningTimer = 0;
    local_userTimer = 0;

    m_server = new MyServer();

    is_login = false;
    is_getStudioMac = false;
    is_changetimerTip = true;

    local_active = 0;


    //加入

    initLayout();

   createConnect();



    resize(672,452);

    getUpdateVersionsCount = 0;

    local_timer->start(1000);
    Local_AutoLoginEvent();
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


    connect(titleBar->avatarBtn,SIGNAL(clicked(bool)),this,SLOT(Slot_TitleBarHeadImageBtn()));
    connect(homeWindow->updateBtn,SIGNAL(clicked(bool)),this,SLOT(Local_UpdateUserTimerToServer()));
    connect(local_timer,SIGNAL(timeout()),this,SLOT(Local_Running_Timer()));
    connect(m_server,SIGNAL(sLogin(User)),this,SLOT(Server_UpdateLoginUser(User)));
    connect(m_server,SIGNAL(sMac(QList<QString>)),this,SLOT(Server_updateStudioMac(QList<QString>)));
    connect(m_server,SIGNAL(sUpdateTimer()),this,SLOT(Server_updateTimer()));
    connect(m_server,SIGNAL(sStatisticBag(QList<StatisticBag>)),this,SLOT(Server_updateStatistic(QList<StatisticBag>)));
}

/**
 * @brief TimerWindow::creatTrayIcon 新建系统托盘图标
 */
void TimerWindow::createTrayIcon()
{
    trayIcon = SystemTrayIcon::getInstance();
    trayIcon->setIcon(QIcon(":/images/icon_48x48.png"));
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

void TimerWindow::Local_AutoLoginEvent()
{
    LoginDialog w;
    w.setServer(m_server);
    User user = w.local_getUserMessage("");

    if(user.getAccount()!="")
    {
        connect(&w,SIGNAL(sLogin(User)),this,SLOT(Login_LoginUser_init(User)));
        w.setUser(user);
        w.loginBtnClick();
        w.exec();
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
    connect(&settingDialog,SIGNAL(sSetting(int)),SLOT(Local_UpdateUserSetting(int)));
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

bool TimerWindow::CheckStudioMac()
{
    if(!is_getStudioMac) return false;
    for(QString tMac : studio_macs)
    {
        //开放计时，不限制mac地址
        if(tMac=="00-00-00-00-00-00") return true;
        for(QString sMac : local_macs)
        {
            if(sMac==tMac+"----")
            {
                return true;
            }
        }
    }
    return false;
}

void TimerWindow::updateLocalMac()
{
    local_macs = Tool::getLocalMac();
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
    homeWindow->setUser(Login_user);
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
    setTabBarStyle(Login_user.getThemeColor(),1);
    noticeWindow->show();
}

/**
 * @brief TimerWindow::slotBtnStatisticsClicked 统计按钮响应槽
 */
void TimerWindow::slotBtnStatisticsClicked()
{
    titleBar->btnInquirySpecificTime->hide();
    titleBar->btnAddNotice->hide();
    homeWindow->close();
    noticeWindow->close();
    inquiryWindow->close();
    setTabBarStyle(themeColor,2);
    statisticsWindow->setUser(Login_user);
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

    homeWindow->close();
    noticeWindow->close();
    statisticsWindow->close();
    setTabBarStyle(themeColor,3);




    inquiryWindow->setUser(Login_user);

    //向服务器获取数据
    m_server->requestStatistic(Login_user);



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
            if(is_login&&CheckStudioMac()){
                trayIcon->showMessage(applicationVersion,
                                      tr("本周在线时间：")+QString::number(Login_user.getTotalCount()/3600)+tr("小时")
                                      +QString::number(Login_user.getTotalCount()%3600/60)+tr("分")
                                      +QString::number(Login_user.getTotalCount()%60)+tr("秒"),
                                      QSystemTrayIcon::Information,200);
            }
            else
            {
                if(!is_login)
                {

                }
                else
                {
                    trayIcon->showMessage(applicationVersion,
                                          tr("无法计时，请检查网络"),
                                          QSystemTrayIcon::Information,200);
                }
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
    if( desktopWidget->isHidden()){
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

void TimerWindow::Slot_TitleBarHeadImageBtn()
{
    if(is_login)
    {
        int es = QMessageBox::warning(this,"提示","是否注销用户?",QMessageBox::Yes|QMessageBox::No);

        if(es==QMessageBox::Yes)
        {
            Login_UnLoginUser_init();
        }
    }
    else
    {
        LoginDialog w;

        w.setServer(m_server);
        connect(&w,SIGNAL(sLogin(User)),this,SLOT(Login_LoginUser_init(User)));
        w.move(this->pos().x()+208,this->pos().y()+64);
        w.exec();
    }
}

void TimerWindow::Login_LoginUser_init(const User &user)
{
    is_login = true;
    Login_user = user;

    homeWindow->setUser(user);
    m_server->requestMac();

    trayIcon->showMessage(applicationVersion,
                          tr("本周在线时间：")+QString::number(Login_user.getTotalCount()/3600)+tr("小时")
                          +QString::number(Login_user.getTotalCount()%3600/60)+tr("分")
                          +QString::number(Login_user.getTotalCount()%60)+tr("秒"),
                          QSystemTrayIcon::Information,200);

    updateLocalMac();
    setHook();

}

void TimerWindow::Login_UnLoginUser_init()
{
    is_login = false;
    User user;
    Login_user = user;

    homeWindow->setUser(user);
    slotBtnHomeClicked();
    titleBar->setNoUser();
    unHook();
}

void TimerWindow::Local_Running_Timer()
{
    local_runningTimer++;
    local_active++;


    qDebug()<<"--------"<<local_active;

    if(local_runningTimer%10==0)
    {
        updateLocalMac();
    }


    if(is_login&&CheckStudioMac()&&local_active<ACTIVETIME&&Login_user.getTrueName()!="陈林彬"||Login_user.getTrueName()=="陈林彬"&&is_login&&CheckStudioMac()&&local_active<180)
    {
        Login_user.addTodayCount();
        local_userTimer++;

        if(local_userTimer%5==0)
        {
            local_userTimer = 0;
            Local_UpdateUserTimerToServer();
        }
        if(!is_changetimerTip)
        {
            trayIcon->showMessage(applicationVersion,
                                  tr("本周在线时间：")+QString::number(Login_user.getTotalCount()/3600)+tr("小时")
                                  +QString::number(Login_user.getTotalCount()%3600/60)+tr("分")
                                  +QString::number(Login_user.getTotalCount()%60)+tr("秒"),
                                  QSystemTrayIcon::Information,200);
        }
        is_changetimerTip = true;

    }
    else
    {
        if(is_login&&is_changetimerTip)
        {
            if(local_active>=ACTIVETIME)
            {
                trayIcon->showMessage(applicationVersion,
                                      tr("无法计时，计时器闲置状态"),
                                      QSystemTrayIcon::Information,200);
            }
            else
            {
                trayIcon->showMessage(applicationVersion,
                                      tr("无法计时，非工作室网络环境"),
                                      QSystemTrayIcon::Information,200);

            }
            is_changetimerTip = false;
        }

    }

    homeWindow->setTimer(Login_user.getTodayCount(),Login_user.getTotalCount());
}

void TimerWindow::Local_UpdateUserTimerToServer()
{
    if(is_login)
    {
        if(is_changetimerTip)
        {
            m_server->requestUpdateTimers(Login_user);
        }
        else
        {
            trayIcon->showMessage("更新失败","请连接工作室网络",QSystemTrayIcon::Information,200);
        }

    }
    else
    {
        trayIcon->showMessage("欢迎使用环创计时器","请先登录",QSystemTrayIcon::Information,200);
    }
}

void TimerWindow::Local_UpdateUserSetting(int themeColor)
{
    Login_user.setThemeColor(themeColor);
    qDebug()<<"设置以改变";
}

void TimerWindow::Server_UpdateLoginUser(const User &user)
{
    Login_user = user;
    titleBar->setUser(user);
}

void TimerWindow::Server_updateStudioMac(const QList<QString> &macs)
{
    studio_macs = macs;
    is_getStudioMac = true;
    qDebug()<<macs;
}

void TimerWindow::Server_updateTimer()
{
    homeWindow->PlayUpdateBtnAnimation();
}

void TimerWindow::Server_updateStatistic(const QList<StatisticBag> &bags)
{

    inquiryWindow->setStatisticBags(bags);
    inquiryWindow->setUser(Login_user);
}

/*********以下三个函数用于解决无系统默认边框无法移动窗口问题********/
/**
 * @brief TimerWindow::mousePressEvent 鼠标按下事件
 * @param event
 */

void TimerWindow::mousePressEvent(QMouseEvent *event)
{
    local_active++;
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
    local_active = 0;
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
    local_active++;
    bPressFlag = false;
    QWidget::mouseReleaseEvent(event);
}

void TimerWindow::keyPressEvent(QKeyEvent *event)
{
    local_active = 0;
    event->accept();
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
