#ifndef DOHELPER_H
#define DOHELPER_H

#define BASIC_URL "http://***.***.***.***/timer/Handler/"

#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QJsonDocument>
#include <QByteArray>
#include <QString>
#include <QUrl>
#include <QList>
#include <QDataStream>
#include "UserData.h"
#include <QDebug>
#include <QSettings>
#include <QMessageBox>
#include "SystemTrayIcon.h"
#include "define.h"
#include <QFile>
#include <QTextStream>

class DOHelper : public QObject
{
    Q_OBJECT
public:
    static DOHelper* getDOHelper();

    void getUpdateVersionsRequst();
    void getServerDateRequst();
    void addRecordRequst(QString userId,QString timesDate);
    void updateRecordRequst(QString userId, QString timesDate, uint timesCount);    //改了这里 2017-10-26，int -> uint
    void getUserTimesRequst(QString userId,QString startDate,QString endDate);
    void getAllUserTimesRequst(QString startDate,QString endDate);
    void getAllSpecificUserTimesRequst(QString startDate,QString endDate);
    void regRequst(QString account,QString userName,QString userPassword,
                   QString sex,QString grade);
    void loginRequst(QString account,QString userPassword);
    void getUserInfoRequst(QString userId);
    void updateUserInfoRequst(QString userId,QString account,QString userName,
                              QString userPassword,QString sex,QString grade);
    void addNoticeRequst(QString date,QString content);
    void getNoticeRequst();
    void refreshGetNoticeRequst(QString refreshMethod,QString id);
    void delNoticeRequst(QString id);
    QSettings *settings;
    SystemTrayIcon *trayIcon = NULL;

private:
    enum NetWorkerAction{GetUpdateVersionsAction,GetServerDateAction,AddRecordAction,
                         UpdateRecordAction,GetUserTimesAction,GetAllUserTimesAction,GetAllSpecificUserTimesAction,
                         RegAction,LoginAction,GetUserInfoAction,UpdateUserInfoAction,
                         AddNoticeAction,GetNoticeAction,RefreshGetNoticeAction,DelNoticeAction};

    NetWorkerAction netWorkerAction;
    QNetworkAccessManager *netWorker;
    explicit DOHelper(QObject *parent = 0);
    UserData *userData;

    uint encrypt(uint data);        //对当前的计时加密

    static const uint firstMove = 0x123456;
    static const uint secondMove =  0x987654;
    static const uint dataKey1= 0x312a9b72;
    static const uint dataKey2= 0x1a2b3c4d;

signals:
    void netState(bool);

public slots:
    void replyfinished(QNetworkReply*);
};

#endif // DOHELPER_H
