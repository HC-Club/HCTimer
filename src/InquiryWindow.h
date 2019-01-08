#ifndef INQUIRYWINDOW_H
#define INQUIRYWINDOW_H

#include <QWidget>
#include <QLabel>
#include "UserData.h"
#include "DOHelper.h"
#include <QListWidget>
#include <QListWidgetItem>
#include <QPropertyAnimation>

class InquiryWindow : public QWidget
{
    Q_OBJECT
public:
    explicit InquiryWindow(QWidget *parent = 0);
    void initLayout();
    void showAllUserTime();

    UserData *userData;
    DOHelper *http;

    QLabel *weekCount;
    QLabel *timeQualified;

    QListWidget* listWidget;
    QListWidgetItem* listItem;

    QString isQualified;

    int themeColor;

signals:

public slots:
    void changeIsQualified(QString currentText);
};

#endif // INQUIRYWINDOW_H
