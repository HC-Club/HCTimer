#ifndef USERINFODIALOG_H
#define USERINFODIALOG_H

#include <QDialog>
#include <QLabel>
#include <QImage>
#include <QMouseEvent>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QListView>
#include <QPainter>
#include <QtMath>
#include "ModifyInfoDialog.h"
#include <QDebug>
#include <QFileDialog>
#include <QSettings>

class UserInfoDialog : public QDialog
{
    Q_OBJECT
public:
    explicit UserInfoDialog(QDialog *parent = 0);
    QPushButton *avatarBtn;
    QLabel *avatarLabel;
    QImage *avatarImage;
    QLabel *titileLable;
    QLabel *hintLabel;

    QPushButton *closeBtn;
    QPushButton *logoutBtn;
    QPushButton *modifyInfoBtn;

    QLabel *accountLabel;
    QLabel *userNameLabel;
    QLabel *gradeLabel;
    QLabel *sexLabel;
    QLabel *studyDirectionLabel;
    void setUserInfo();

protected:

    QPoint beginDrag;
    bool bPressFlag;
    void initLayout();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *);

private:
    int themeColor;

public slots:
    void soltLogoutBtn();
    void soltModifyInfoBtn();
    void changeAvatar();
};

#endif // USERINFODIALOG_H
