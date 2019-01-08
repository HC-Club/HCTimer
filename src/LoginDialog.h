#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QMouseEvent>
#include <QDebug>
#include <QMessageBox>
#include <QtMath>
#include <QPainter>
#include "DOHelper.h"
#include "UserData.h"
#include "RegistDialog.h"

class LoginDialog : public QDialog
{
    Q_OBJECT
public:
    explicit LoginDialog(QDialog *parent = 0);

    QLineEdit *accountEdit;
    QLineEdit *passwordEdit;

    QPushButton *closeBtn;
    QPushButton *loginBtn;
    QPushButton *registBtn;

    DOHelper *http;
    UserData *userData;

    void initInterface();

protected:

    QPoint beginDrag;
    bool bPressFlag;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *);


private:
    int themeColor;

public slots:
    void loginBtnClick();
    void registBtnClick();

};

#endif // LOGINDIALOG_H
