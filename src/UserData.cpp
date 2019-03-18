#include "UserData.h"



UserData::UserData()   //构造函数是私有的
{
    initData();
}

UserData *UserData::getUserData()
{
    static UserData userData;   //局部静态变量
    return &userData;
//      UserData* UserData::p = new UserData;
//      return p;
}

void UserData::setUserID(QString _id)
{
    userID = _id;
}

QString UserData::getUserID()
{
    return userID;
}

void UserData::setUserAccount(QString _account)
{
    userAccount = _account;
}

QString UserData::getUserAccount()
{
    return userAccount;
}

void UserData::setUserPassWord(QString _password)
{
    userPassWord = _password;
}

QString UserData::getUserPassword()
{
    return userPassWord;
}

void UserData::setUserName(QString _name)
{
    userName = _name;
}

QString UserData::getUserName()
{
    return userName;
}

void UserData::setUserSex(QString _sex)
{
    userSex = _sex;
}

QString UserData::getUserSex()
{
    return userSex;
}

void UserData::setUserGrade(QString _grade)
{
    userGrade = _grade;
}

QString UserData::getUserGrade()
{
    return userGrade;
}

void UserData::setTimeCount(int _timeCount)
{
    timeCount = _timeCount;
}

int UserData::getTimeCount()
{
    return timeCount;
}

void UserData::setTotalTime(int _totalTime)
{
    userTotalTime = _totalTime;
}

int UserData::getTotalTime()
{
    return userTotalTime;
}

void UserData::setTodayTime(int _todayTime)
{
    userTodayTime = _todayTime;
}

int UserData::getTodayTime()
{
    return userTodayTime;
}

QDate UserData::getstartDate_own()
{
    return startDate_own;
}

QDate UserData::getstartDate_all()
{
    return startDate_all;
}

QDate UserData::getEndDate_own()
{
    return endDate_own;
}

QDate UserData::getendDate_all()
{
    return endDate_all;
}

QString UserData::getOnlineTime()
{
    int todayTime;
    todayTime = userTodayTime + timeCount;
    QString onlineTime;
    onlineTime = QString::number(todayTime/3600)+"小时"+
                 QString::number(todayTime%3600/60)+"分钟"+
                 QString::number(todayTime%60)+"秒";
    return onlineTime;
}

void UserData::setServerDate(int _year, int _month, int _day)
{
    serverDate = QDate(_year,_month,_day);
    startDate_own = serverDate.addDays(1-serverDate.dayOfWeek());
    endDate_own = serverDate.addDays(7-serverDate.dayOfWeek());
    startDate_all = serverDate.addDays(1-serverDate.dayOfWeek());
    endDate_all = serverDate.addDays(7-serverDate.dayOfWeek());
}

QDate UserData::getServerDate()
{
    return serverDate;
}

/**
 * @brief UserData::setAllUsers 设置所有用户的时间信息
 */
void UserData::setAllUsers(QString _name, QString _timeCount)
{
    AllUsers temp;
    temp.name = _name;
    temp.timeCount = _timeCount;
    allUsers.append(temp);
}

/**
 * @brief UserData::setAllSpecificUsers 设置所有搜索出来的特定用户的时间信息
 */
void UserData::setAllSpecificUsers(QString _name, QString _timeCount)
{
    AllUsers temp;
    temp.name = _name;
    temp.timeCount = _timeCount;
    allSpecificUsers.append(temp);
}

QList<AllUsers> UserData::getAllUsers()
{
    return allUsers;
}

QList<AllUsers> UserData::getAllSpecificUsers()
{
    return allSpecificUsers;
}

void UserData::clearAllUsers()
{
    allUsers.clear();
}

void UserData::clearAllSpecificUsers()
{
    allSpecificUsers.clear();
}

/**
 * @brief UserData::setNotices 设置公告信息
 */
void UserData::setNotices(QString _id,QString _date,QString _content,QString _createTime)
{
    Notice temp;
    temp.id = _id;
    temp.date = _date;
    temp.content = _content;
    temp.createTime = _createTime;
    notices.append(temp);
}

QList<Notice> UserData::getNotices()
{
    return notices;
}

void UserData::clearNotices()
{
    notices.clear();
}

void UserData::setFirstNoticeID(QString _firstNoticeID)
{
    firstNoticeID = _firstNoticeID;
}

void UserData::setEndNoticeID(QString _endNoticeID)
{
    endNoticeID = _endNoticeID;
}

QString UserData::getFirstNoticeID()
{
    return firstNoticeID;
}

QString UserData::getEndNoticeID()
{
    return endNoticeID;
}

/**
 * @brief UserData::setUserTime 设置用户一周7天的各个时间记录，并且设置今日在线时间
 * @parame _year为年 _month为月 _day为日 _timeCount为时间记录（秒）
 */
void UserData::setUserTime(int _year, int _month, int _day, int _timeCount)
{
    userTime[QDate(_year,_month,_day).dayOfWeek()-1]=_timeCount;
    if(QDate(_year,_month,_day).dayOfWeek()==getServerDate().dayOfWeek()){
        setTodayTime(_timeCount);
    }
}

void UserData::setThemeColor(int _themeColor)
{
    themeColor = _themeColor;
}

int UserData::getThemeColor()
{
    return themeColor;
}

void UserData::initData()
{
    isGetServerTime = false;
    isGetUpdateVersion = false;
    isLogin = false;
    isAutoUpdate = false;
    userTime[7]={0};

    userID = "";
    userAccount = "";
    userPassWord = "";
    userName = "";
    userSex = "";
    userGrade = "";
    onlineTime = "";

    timeCount = 0;
    userTotalTime = 0;
    userTodayTime = 0;
}

//void UserData::printData()
//{
//    QString AWeekTime;
//    qDebug()<<"******* 输出UserData数据 ********";
//    qDebug()<<"timeCount = "<<timeCount<<" userTotalTime = "<<userTotalTime
//           <<" userTodayTime = "<<userTodayTime<<" serverDate:"<<serverDate;
//    qDebug()<<"isLogin = "<<isLogin<<" userID = "<<userID
//           <<" userAccount = "<<userAccount<<" userPassWord = "<<userPassWord;
//    qDebug()<<"userName = "<<userName<<" userSex = "<<userSex
//           <<" userGrade = "<<userGrade<<" onlineTime = "<<onlineTime;
//    for(int i=0;i<7;i++){
//        AWeekTime += QString::number(userTime[i]);
//        AWeekTime += "  ";
//    }
//    qDebug()<<AWeekTime;
//}
