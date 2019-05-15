#ifndef REGISTDIALOG_H
#define REGISTDIALOG_H

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
#include "myserver.h"

class RegistDialog : public QDialog
{
    Q_OBJECT
public:
    explicit RegistDialog(QDialog *parent = 0);

    QLabel *titileLable;
    QLabel *hintLabel;

    QPushButton *closeBtn;
    QPushButton *confirmBtn;

    QLineEdit *accountEdit;
    QLineEdit *userNameEdit;
    QLineEdit *pwdEdit;
    QLineEdit *gradeEdit;
    QLineEdit *confirmPwdEdit;
    QComboBox *sexComboBox;
    /**
     * @brief 设置服务类
     * @param server
     */
    void setServer(MyServer *server);
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
    MyServer *m_server;

public slots:
    void soltConfirmBtn();
    void Server_RegisterFail(const QString &message);
    void Server_RegisterSuccess(const QString &message);
};

#endif // REGISTDIALOG_H
