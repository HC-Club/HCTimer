#ifndef MYSERVER_H
#define MYSERVER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QDebug>
#include <QJsonDocument>
#include <QVariantMap>
#include "user.h"
#include "define.h"

#define APP_SERVER "http://***.***.***.***/hctimer/public/index.php/index/login/i?"
#define APP_Visiter "http://***.***.***.***/hctimer/public/index.php/index/visiter/i?"
#define APP_Index "http://***.***.***.***/hctimer/public/index.php/index/index/i?"

class MyServer:public QObject
{
    Q_OBJECT
public:
    MyServer();

    void login(const User &user);
    void userRegister(const User &user);
    void requestMac();
    void requestUpdateTimers(const User &user);
    void requestStatistic(const User &user);

    /**
     * @brief 获取版本号
     */
    void requestVersion();

public slots:
    void answer(QNetworkReply *reply);

private:
    QNetworkAccessManager *manager;
    void init();

signals:
    void sError(QString);
    void sLoginFail(QString);
    void sLogin(const User &user);
    void sUpdate(const QString &message);
    void sUpdateTimer();
    void sUpdateUser(const User &user);
    void sRegister(const QString&);
    void sMac(const QList<QString>&);
    void sVersion(const QString &version,const QString &downloadUrl);
    void sStatisticBag(const QList<StatisticBag>&bags);
};

#endif // MYSERVER_H
