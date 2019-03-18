#ifndef MONITOR_H
#define MONITOR_H

#include "define.h"

#define MONITOR_IP_PREIX "192.168.1."//IP监控范围
#define MONITOR_IP_PREXI2 "192.168.2."//hc-2.4g的ip
#define LIMIT_TIME 1800//30min*60s,检测用户在时间范围30min内的是否操作过鼠标、键盘

#include <QHostAddress>
#include <QHostInfo>
#include <QString>
#include <QObject>
#include <QTimer>
#include <QDebug>
#include "UserData.h"

#if WINDOWS_VERSION
    #include <windows.h>
#elif LINUX_VERSION

#elif MAC_VERSION

#endif

class Monitor : public QObject
{
    Q_OBJECT
public:
    bool isCanUpdate();
    bool isUserOnline();
    bool isLabRouter();
    static Monitor* getMonitor();
 //   static Monitor* p;
    bool isLabRouterMAC;

private:
    explicit Monitor(QObject *parent = 0);
    ~Monitor();
    QTimer *timer;
    UserData *userData = UserData::getUserData();

private slots:
    void upDateTime();
};

#endif // MONITOR_H
