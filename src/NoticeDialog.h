#ifndef NOTICEDIALOG_H
#define NOTICEDIALOG_H

#include <QDialog>
#include <QMouseEvent>
#include <QPushButton>
#include <QLabel>
#include <QtMath>
#include <QPainter>
#include <QMessageBox>
#include "user.h"

class NoticeDialog : public QDialog
{
    Q_OBJECT
public:
    explicit NoticeDialog(QDialog *parent = 0);
    QPushButton *closeBtn;
    QLabel *date;
    QLabel *content;
    QLabel *creatTime;
    QLabel *noticeID;
    QPushButton *deleteBtn;

protected:
    void initLayout();
    QPoint beginDrag;
    bool bPressFlag;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *);

public slots:
    void deleteNotice();
};

#endif // NOTICEDIALOG_H
