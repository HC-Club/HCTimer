#ifndef USER_H
#define USER_H

#include <QString>
#include <QDate>

struct TimerRecord
{
    QDate date;
    int count;
};

struct StatisticBag{
   QString name;
   QString timeCount;
   int top;
};

struct Notice{
    QString id;
    QString date;
    QString content;
    QString createTime;
};


class User
{
public:
    User();

    QString getAccount() const;
    void setAccount(const QString &value);

    QString getPassword() const;
    void setPassword(const QString &value);

    QString getSex() const;
    void setSex(const QString &value);

    QString getTrueName() const;
    void setTrueName(const QString &value);

    QString getGrade() const;
    void setGrade(const QString &value);

    QList<TimerRecord> getTimerRecord() const;
    void setTimerRecord(const QList<TimerRecord> &value);


    QDate getToday() const;
    void setToday(const QDate &value);

    QDate getEnd() const;
    void setEnd(const QDate &value);

    QDate getBegin() const;
    void setBegin(const QDate &value);

    int getThemeColor() const;
    void setThemeColor(int value);

    int getTodayCount() const;
    void setTodayCount(int value);

    int getTotalCount() const;
    void setTotalCount(int value);

    void addTodayCount();

    void setUserMessage(const User &user);



    bool getAutoLogin() const;
    void setAutoLogin(bool autoLogin);

    bool getRememberPassword() const;
    void setRememberPassword(bool rememberPassword);

private:
    QString account;
    QString password;
    QString sex;
    QString trueName;
    QString grade;

    int themeColor;


    QList<TimerRecord> timerRecord;
    QDate begin;
    QDate end;
    QDate today;

    int totalCount;
    int todayCount;

    bool m_autoLogin;
    bool m_rememberPassword;
};

#endif // USER_H
