#ifndef MODIFYINFODIALOG_H
#define MODIFYINFODIALOG_H


#include <QDialog>
#include <QLabel>
#include <QMouseEvent>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QListView>
#include <QDebug>
#include "DOHelper.h"
#include "UserData.h"
#include <QDialog>
#include <QLineEdit>
#include <QMouseEvent>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QListView>
#include <QDebug>
#include <QMessageBox>
#include <QtMath>
#include <QPainter>
#include "DOHelper.h"
#include "UserData.h"

class ModifyInfoDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ModifyInfoDialog(QDialog *parent = 0);

    QLabel *titileLable;
    QLabel *hintLabel;

    QPushButton *closeBtn;
    QPushButton *confirmBtn;

    QLineEdit *accountEdit;
    QLineEdit *userNameEdit;
    QLineEdit *oldPwdEdit;
    QLineEdit *gradeEdit;
    QLineEdit *newPwdEdit;
    QComboBox *sexComboBox;

protected:
    QPoint beginDrag;
    bool bPressFlag;
    void initLayout();
    DOHelper *http;
    UserData *userData;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *);

private:
    int themeColor;

public slots:
    void soltConfirmBtn();
};

#endif // MODIFYINFODIALOG_H
