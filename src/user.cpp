#include "user.h"

User::User()
{
    themeColor = 0;
    totalCount = 0;
    todayCount = 0;

    m_autoLogin = false;
    m_rememberPassword = false;
}

QString User::getAccount() const
{
    return account;
}

void User::setAccount(const QString &value)
{
    account = value;
}

QString User::getPassword() const
{
    return password;
}

void User::setPassword(const QString &value)
{
    password = value;
}

QString User::getSex() const
{
    return sex;
}

void User::setSex(const QString &value)
{
    sex = value;
}

QString User::getTrueName() const
{
    return trueName;
}

void User::setTrueName(const QString &value)
{
    trueName = value;
}

QString User::getGrade() const
{
    return grade;
}

void User::setGrade(const QString &value)
{
    grade = value;
}

QList<TimerRecord> User::getTimerRecord() const
{
    return timerRecord;
}

void User::setTimerRecord(const QList<TimerRecord> &value)
{
    timerRecord = value;
}

QDate User::getToday() const
{
    return today;
}

void User::setToday(const QDate &value)
{
    today = value;
}

QDate User::getEnd() const
{
    return end;
}

void User::setEnd(const QDate &value)
{
    end = value;
}

QDate User::getBegin() const
{
    return begin;
}

void User::setBegin(const QDate &value)
{
    begin = value;
}

int User::getThemeColor() const
{
    return themeColor;
}

void User::setThemeColor(int value)
{
    themeColor = value;
}

int User::getTodayCount() const
{
    return todayCount;
}

void User::setTodayCount(int value)
{
    todayCount = value;
}

int User::getTotalCount() const
{
    return totalCount;
}

void User::setTotalCount(int value)
{
    totalCount = value;
}

void User::addTodayCount()
{
    todayCount++;
    totalCount++;
}

void User::setUserMessage(const User &user)
{
    setAccount(user.getAccount());
    setPassword(user.getPassword());
    setGrade(user.getGrade());
    setTrueName(user.getTrueName());
}

bool User::getAutoLogin() const
{
    return m_autoLogin;
}

void User::setAutoLogin(bool autoLogin)
{
    m_autoLogin = autoLogin;
}

bool User::getRememberPassword() const
{
    return m_rememberPassword;
}

void User::setRememberPassword(bool rememberPassword)
{
    m_rememberPassword = rememberPassword;
}
