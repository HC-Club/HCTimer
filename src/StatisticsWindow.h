#ifndef STATISTICSWINDOW_H
#define STATISTICSWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QString>
#include <QPainter>
#include <QPoint>
#include "UserData.h"

class StatisticsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit StatisticsWindow(QWidget *parent = 0);
    void initTimeCoord();
    void setTimeCoord();

private:
    UserData *userData;

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
    int todayNum;

    int themeColor;

    void createLable();
    void paintEvent(QPaintEvent *);
};

#endif // STATISTICSWINDOW_H
