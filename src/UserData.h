#ifndef USERDATA_H
#define USERDATA_H

#include <QString>
#include <QList>
#include <QDate>
#include "define.h"
#include <QDebug>

typedef struct Notice{
    QString id;
    QString date;
    QString content;
    QString createTime;
}Notice;

typedef struct AllUsers{
   QString name;
   QString timeCount;
}AllUsers;

class UserData
{
private:
    UserData();

    int timeCount;
    int userTotalTime;
    int userTodayTime;

    QString userID;
    QString userAccount;
    QString userPassWord;
    QString userName;
    QString userSex;
    QString userGrade;
    QString onlineTime;

    QDate serverDate;
    QDate startDate_own;
    QDate startDate_all;
    QDate endDate_own;
    QDate endDate_all;

    QList<AllUsers> allUsers;
    QList<AllUsers> allSpecificUsers;

    QList<Notice> notices;
    QString firstNoticeID;
    QString endNoticeID;

    int themeColor;

public:
    bool isGetUpdateVersion;
    bool isGetServerTime;
    bool isLogin;
    bool isAutoUpdate;
    QString updateVersions;
    QString downloadURL;

    int userTime[7];
    static UserData* getUserData();

    void setUserID(QString _id);
    QString getUserID();

    void setUserAccount(QString _account);
    QString getUserAccount();

    void setUserPassWord(QString _password);
    QString getUserPassword();

    void setUserName(QString _name);
    QString getUserName();

    void setUserSex(QString _sex);
    QString getUserSex();

    void setUserGrade(QString _grade);
    QString getUserGrade();

    void setTimeCount(int _timeCount);
    int getTimeCount();

    void setTotalTime(int _totalTime);
    int getTotalTime();

    void setTodayTime(int _todayTime);
    int getTodayTime();

    QDate getstartDate_own();
    QDate getEndDate_own();
    QDate getstartDate_all();
    QDate getendDate_all();


    QString getOnlineTime();

    void setServerDate(int _year,int _month,int _day);
    QDate getServerDate();

    void setAllUsers(QString _name,QString _timeCount);
    void setAllSpecificUsers(QString _name,QString _timeCount);
    QList<AllUsers> getAllUsers();
    QList<AllUsers> getAllSpecificUsers();
    void clearAllUsers();
    void clearAllSpecificUsers();

    void setUserTime(int _year,int _month,int _day,int _timeCount);

    void setNotices(QString _id,QString _date,QString _content,QString _createTime);
    QList<Notice> getNotices();
    void clearNotices();
    void setFirstNoticeID(QString _firstNoticeID);
    void setEndNoticeID(QString _endNoticeID);
    QString getFirstNoticeID();
    QString getEndNoticeID();

    void setThemeColor(int _themeColor);
    int getThemeColor();

    void initData();
//    void printData();//调试输出用户数据
};

#endif // USERDATA_H
