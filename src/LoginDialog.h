#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QMouseEvent>
#include <QDebug>
#include <QMessageBox>
#include <QtMath>
#include <QPainter>
#include <QCheckBox>
#include "RegistDialog.h"
#include "myserver.h"
#define HCKEY "qwertyuiopasdfghjklzxcvbnm789456"
#define HCIVEC = "123456789zxcvbnm"
#define FILENAME "LOCALDATABASE.dat"

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
    QCheckBox *rememberPasswordBtn;
    QCheckBox *autoLoginBtn;

    MyServer *m_server;

    void initInterface();


    void setServer(MyServer *server);
    void setUser(const User &user);
    /**
     * @brief 保存用户数据于本地
     * @param user
     */
    void local_saveUserMessage(const User &user);
    /**
     * @brief 从本地读取出用户数据
     * @param userName
     * @return
     */
    User local_getUserMessage(const QString &userName);


protected:

    QPoint beginDrag;
    bool bPressFlag;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *event);

    void CreateLocalDatabase();
    QList<User> getAllUserMessageFromLocal();
    void SaveAllUserMessageFromLocal(const QList<User> &list);


private:
    int themeColor;

    QString enCode(const QString &str);
    QString deCode(const QString &str);

public slots:
    void loginBtnClick();
    void registBtnClick();
    void Server_LoginSuccess(const User &user);
    void Server_LoginFail(const QString &message);
    void Local_AccountTextChange(const QString&text);

signals:
    void sLogin(const User &user);

};

#endif // LOGINDIALOG_H
