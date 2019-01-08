#ifndef NOTICEWIDGET_H
#define NOTICEWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QTextEdit>
#include "DOHelper.h"
#include "UserData.h"
#include "NoticeDialog.h"
#include <QDebug>

class NoticeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit NoticeWidget(QWidget *parent = 0);

    QLabel *noticeIDLabel_1;
    QLabel *createTimeLabel_1;
    QLabel *titleLabel_1;
    QPushButton *dateBtn_1;
    QTextEdit *text_1;

    QLabel *noticeIDLabel_2;
    QLabel *createTimeLabel_2;
    QLabel *titleLabel_2;
    QPushButton *dateBtn_2;
    QTextEdit *text_2;

    QLabel *noticeIDLabel_3;
    QLabel *createTimeLabel_3;
    QLabel *titleLabel_3;
    QPushButton *dateBtn_3;
    QTextEdit *text_3;

    int dateBtnStyleSheetID;

    void showCurrentNotice();
    void showOldNotice();
    void showNewNotice();
    void changeDateBtnStyleSheet(int i);


    UserData *userData;
    DOHelper *http;

private:
    void initLayout();

public slots:
    void slotDateBtn_1();
    void slotDateBtn_2();
    void slotDateBtn_3();
};


#endif // NOTICEWIDGET_H
