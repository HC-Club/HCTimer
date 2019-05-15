#ifndef INQUIRYWINDOW_H
#define INQUIRYWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QListWidget>
#include <QListWidgetItem>
#include <QPropertyAnimation>
#include <QDebug>
#include "tool.h"
class InquiryWindow : public QWidget
{
    Q_OBJECT
public:
    explicit InquiryWindow(QWidget *parent = 0);
    void initLayout();


    QLabel *weekCount;
    QLabel *timeQualified;

    QListWidget* listWidget;
    QListWidgetItem* listItem;

    QString isQualified;
    QLabel *text1 ;
    QLabel *text2 ;
    QLabel *text3 ;
    QPalette pa;

    int themeColor;

    void setStatisticBags(const QList<StatisticBag> &list);
    void setUser(const User &user);
private:

    void setThemeColor(const int &_themeColor);

signals:

public slots:
    void changeIsQualified(QString currentText);
};

#endif // INQUIRYWINDOW_H
