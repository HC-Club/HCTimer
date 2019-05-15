#ifndef STATISTICSWINDOW_H
#define STATISTICSWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QString>
#include <QPainter>
#include <QPoint>
#include <QDebug>
#include "user.h"

class StatisticsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit StatisticsWindow(QWidget *parent = 0);
    void initTimeCoord();


    void setUser(const User &user);

private:

    QLabel *in;
    QLabel *dayCount;
    QLabel *day;
    QLabel *count;
    QLabel *hourCount;
    QLabel *hour;

    QLabel *timeLable[7];
    QLabel *weekLable[7];

    QLabel *triLabel;

    QPoint timeCoord[7];
    int totalCount;

    int todayNum;

    int themeColor;

    void createLable();
    void paintEvent(QPaintEvent *);
    void setTimeCoord(int count[]);
    void setThemeColor(const int &_themeColor);
};

#endif // STATISTICSWINDOW_H
