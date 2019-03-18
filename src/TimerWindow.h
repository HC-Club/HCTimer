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
#include "Monitor.h"
#include "DOHelper.h"
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

#if WINDOWS_VERSION

#include "windows.h"
#include "ShellAPI.h"

#endif

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

private:
    int loginDetectCount;
    int serverTimeDetectCount;

    bool isNameLableChanged;
    UserData *userData;
    Monitor *monitor;
    DOHelper *http;

    bool isClose;

    TitleBar *titleBar;
    TabBar *tabBar;
    HomeWindow *homeWindow;
    NoticeWindow *noticeWindow;
    StatisticsWindow *statisticsWindow;
    InquiryWindow *inquiryWindow;

    QHBoxLayout *hLayoutTitle;
    QVBoxLayout *vLayoutMain;

    QTimer *detect;

    void setTabBarStyle(int themeColor,int tabBarPressedFlag);

    int themeColor;
    bool isStartDesktopWidget;

    QString applicationVersion;

    Updater *updater;
    int getUpdateVersionsCount;

public slots:

    void slotDetect();
    void slotLogin();
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
};

#endif // TIMERWINDOW_H
