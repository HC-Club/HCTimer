#ifndef ADDNOTICEDIALOG_H
#define ADDNOTICEDIALOG_H

#include <QDialog>
#include <QMouseEvent>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QDate>
#include <QMessageBox>
#include <QtMath>
#include <QPainter>

class AddNoticeDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AddNoticeDialog(QDialog *parent = 0);

protected:
    void initLayout();
    QPoint beginDrag;
    bool bPressFlag;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *);

private:
    QPushButton *closeBtn;
    QLineEdit *year;
    QLineEdit *month;
    QLineEdit *day;
    QTextEdit *content;
    QPushButton *finishBtn;

    int themeColor;

public slots:
    void slotFinishBtn();
};

#endif // ADDNOTICEDIALOG_H
