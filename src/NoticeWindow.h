#ifndef NOTICEWINDOW_H
#define NOTICEWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QPropertyAnimation>
#include "DOHelper.h"
#include "UserData.h"
#include "NoticeWidget.h"
#include "NoticeDialog.h"
#include <QDebug>

class NoticeWindow : public QWidget
{
    Q_OBJECT
public:
    explicit NoticeWindow(QWidget *parent = 0);

    QPropertyAnimation *noticesSwitchAnimation;

    NoticeWidget *noticeWidget;
    QPushButton *forwardBtn;
    QPushButton *backBtn;

    QLabel *triLabel;

private:
    void initLayout();

public slots:
    void slotForwardSwitch();
    void slotBackSwitch();
};

#endif // NOTICEWINDOW_H
