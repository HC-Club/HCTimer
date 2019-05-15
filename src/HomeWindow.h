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
#include "Monitor.h"
#include "user.h"

#define AUTO_UPDATE_INTERVAL 300    //5min*60sec
#define HOURS_WEEK 86400    //24hour*60min*60sec

class HomeWindow : public QWidget
{
    Q_OBJECT
public:

    explicit HomeWindow(QWidget *parent = 0);
    ~HomeWindow();

    void setUser(const User &user);
    void setDates(const QDate &today,const QDate &begin,const QDate &end);
    void setTimer(int today,int total);

    QPushButton *updateBtn;

    /**
     * @brief 设置首页播放更新动画
     */
    void PlayUpdateBtnAnimation();

public slots:
    /**
     * @brief 首页时间槽执行更新动画
     */
    void DoUpdateBtnAnimation();

protected:
    void paintEvent(QPaintEvent *event);

private:
    void createView();

    int totalTimeVaule;
    int hour;
    int minute;
    int second;
    int autoUpdate;

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

    QTimer *timerOpacity;

    int level;
    double opacity[10] = {0.9,0.8,0.7,0.6,0.5,0.4,0.3,0.2,0.1,0.0};
    QPoint movePos[10] = {QPoint(596,225),QPoint(598,220),QPoint(600,215),QPoint(602,210)
                         ,QPoint(604,205),QPoint(602,200),QPoint(600,195),QPoint(598,190)
                         ,QPoint(596,185),QPoint(595,180)};
    int themeColor;

    void setThemeColor(const int &_themeColor);

};

#endif // HOMEWINDOW_H
