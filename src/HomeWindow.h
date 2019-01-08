#ifndef HOMEWINDOW_H
#define HOMEWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QString>
#include <QPainter>
#include <QPushButton>
#include <QPoint>
#include <QGraphicsOpacityEffect>
#include <QDebug>
#include <DOHelper.h>
#include "UserData.h"
#include "DOHelper.h"
#include "Monitor.h"

#define AUTO_UPDATE_INTERVAL 300    //5min*60sec
#define HOURS_WEEK 86400    //24hour*60min*60sec

class HomeWindow : public QWidget
{
    Q_OBJECT
public:
    void updateUserData();
    explicit HomeWindow(QWidget *parent = 0);
    ~HomeWindow();

protected:
    void setUserValue(int _totalTime,int _todayTime);
    void paintEvent(QPaintEvent *event);

private:
    void createView();
    void setDate();

    int totalTimeVaule;
    int hour;
    int minute;
    int second;
    int autoUpdate;

    QPushButton *updateBtn;

    QLabel *todayLable;
    QLabel *date;
    QLabel *year[3];
    QLabel *yearLable[3];
    QLabel *month[3];
    QLabel *monthLable[3];
    QLabel *day[3];
    QLabel *dayLable[3];
    QLabel *weekLable;
    QLabel *toLable;
    QLabel *headLable;
    QLabel *titleLable;
    QLabel *showhour;
    QLabel *hourLable;
    QLabel *showminute;
    QLabel *minuteLable;
    QLabel *showsecond;
    QLabel *secondLable;
    QLabel *triLabel;
    QLabel *addOne;

    UserData *userData;
    DOHelper *http;
    Monitor *monitor;

    QTimer *updateTimer;
    QTimer *timer;
    QTimer *timerOpacity;

    int level;
    double opacity[10] = {0.9,0.8,0.7,0.6,0.5,0.4,0.3,0.2,0.1,0.0};
    QPoint movePos[10] = {QPoint(596,225),QPoint(598,220),QPoint(600,215),QPoint(602,210)
                         ,QPoint(604,205),QPoint(602,200),QPoint(600,195),QPoint(598,190)
                         ,QPoint(596,185),QPoint(595,180)};
    int themeColor;

private slots:
    void updateBtnAnimation();
    void slotUpdateBtn();

};

#endif // HOMEWINDOW_H
