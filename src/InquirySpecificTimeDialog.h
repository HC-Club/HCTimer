#ifndef INQUIRYSPECIFICTIMEDIALOG_H
#define INQUIRYSPECIFICTIMEDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QMouseEvent>
#include <QSettings>
#include <QPainter>
#include <QtMath>
#include <QFont>
#include <QMessageBox>
#include <QListWidget>
#include <QListWidgetItem>
#include "UserData.h"
#include "DOHelper.h"
#include <QLineEdit>
#include <QDebug>

class InquirySpecificTimeDialog : public QDialog
{
    Q_OBJECT
public:
    explicit InquirySpecificTimeDialog(QDialog *parent = 0);

    void showListResult();
    UserData *userData;
    DOHelper *http;

protected:
    void initInterface();

    void showListResult(QString startDate,QString endDate);

    QPoint beginDrag;
    bool bPressFlag;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *);

private:
    QPushButton *closeBtn;

    QLineEdit *startYear;
    QLineEdit *startMonth;
    QLineEdit *startDay;

    QLabel *spacedLine;

    QLineEdit *endYear;
    QLineEdit *endMonth;
    QLineEdit *endDay;

    QListWidget* listWidget;
    QListWidgetItem* listItem;

    QPushButton *searchBtn;

    int themeColor;

public slots:
    void slotSearchBtn();
};

#endif // INQUIRYSPECIFICTIMEDIALOG_H
