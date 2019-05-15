/****************************************************************
**
** 文件名：
** 类信息：
** 创建者：
** 创建期日期：2016.05
** 包含类名列表：
** 版权声明：版权归 韶关学院 环创电脑工作室 所有
** 联系方式: http://www.hclab.cn
**
*******************************************************************/

#ifndef TIMERWINDOW_H
#define TIMERWINDOW_H

#include <QWidget>
#include <QPoint>
#include <QMouseEvent>
#include <QPainter>
#include <QMenu>
#include <QtMath>
#include <QSettings>
#include <QPushButton>
#include <QHBoxLayout>
#include "DesktopWidget.h"
#include "TitleBar.h"
#include "TabBar.h"
#include "HomeWindow.h"
#include "LoginDialog.h"
#include "UserInfoDialog.h"
#include "SettingDialog.h"
#include "StatisticsWindow.h"
#include "InquiryWindow.h"
#include "AboutDialog.h"
#include "NoticeWindow.h"
#include "AddNoticeDialog.h"
#include "SystemTrayIcon.h"
#include "InquirySpecificTimeDialog.h"
#include <QtMath>
#include <cstdlib>
#include <QByteArray>
#include "Updater.h"
#include "tool.h"

#if WINDOWS_VERSION

#include "windows.h"
#include "ShellAPI.h"
#include "myserver.h"

#endif

#define ACTIVETIME 1800

class TimerWindow : public QWidget
{
    Q_OBJECT

public:

    TimerWindow(QWidget *parent = 0);

    void runCMD(QString command);
    void updateApp();

    void closeEvent(QCloseEvent *event);

    ~TimerWindow();
    DesktopWidget *desktopWidget;

    SystemTrayIcon *trayIcon = NULL;

protected:
    /***实现无边框移动****/
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    QPoint beginDrag;
    bool bPressFlag;

    //边缘阴影
    void paintEvent(QPaintEvent *);

    QSettings *settings;

    QMenu *trayMenu;

    void initLayout();
    void createConnect();
    void createTrayIcon();
    bool readConfigToLogin();

    /**
     * @brief 本地自动登录事件
     */
    void Local_AutoLoginEvent();

private:
    int loginDetectCount;
    int serverTimeDetectCount;

    bool isNameLableChanged;
    bool isClose;

    TitleBar *titleBar;
    TabBar *tabBar;
    HomeWindow *homeWindow;
    NoticeWindow *noticeWindow;
    StatisticsWindow *statisticsWindow;
    InquiryWindow *inquiryWindow;

    QHBoxLayout *hLayoutTitle;
    QVBoxLayout *vLayoutMain;

    void setTabBarStyle(int themeColor,int tabBarPressedFlag);

    int themeColor;
    bool isStartDesktopWidget;

    QString applicationVersion;

    Updater *updater;
    int getUpdateVersionsCount;
    MyServer *m_server;

    User Login_user;

    bool is_login;


    QTimer *local_timer;
    int local_runningTimer;
    int local_userTimer;

    QList<QString> local_macs;
    QList<QString> studio_macs;


    bool is_getStudioMac;
    //变更计时状态提示
    bool is_changetimerTip;

    /**
     * @brief 监测工作室mac地址是不是正确
     * @return
     */
    bool CheckStudioMac();
    /**
     * @brief 更新本地mac
     */
    void updateLocalMac();

public slots:

    void slotBtnAddNoticeClicked();
    void slotBtnInquirySpecificTime();
    void slotBtnSettingsClicked();
    void slotBtnCloseClicked();
    void slotBtnMinimizeClicked();

    void slotBtnHomeClicked();
    void slotBtnNoticeClicked();
    void slotBtnStatisticsClicked();
    void slotBtnInquiryClicked();
    void slotAboutClicked();

    void slotTrayIconClicked(QSystemTrayIcon::ActivationReason reason);
    void slotShowMainWindow();
    void slotUpdateTime();
    void slotCloseApplication();
    void slotShowDesktopWidget();
    void slotOpenUpdateUrl();

    /**
     * @brief 界面顶部头像按钮响应
     */
    void Slot_TitleBarHeadImageBtn();


    /**
     * @brief 执行登录用户初始化
     * @param user
     */
    void Login_LoginUser_init(const User &user);
    /**
     * @brief 执行没有用户初始化
     */
    void Login_UnLoginUser_init();


    /**
     * @brief 本地计时器 运行计数，每秒钟执行相应的检测操作
     */
    void Local_Running_Timer();
    /**
     * @brief 更新本地的计时时间到服务器
     */
    void Local_UpdateUserTimerToServer();

    void Local_UpdateUserSetting(int themeColor);

    /**
     * @brief 响应服务器，更新登录用户信息
     * @param user
     */
    void Server_UpdateLoginUser(const User &user);

    /**
     * @brief 响应服务器，更新工作室MAC地址
     * @param macs
     */
    void Server_updateStudioMac(const QList<QString> &macs);

    /**
     * @brief 响应服务器，提示用户时间已经更新成功
     */
    void Server_updateTimer();

    void Server_updateStatistic(const QList<StatisticBag> &bags);
};

#endif // TIMERWINDOW_H
