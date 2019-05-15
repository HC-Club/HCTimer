#include "myserver.h"

MyServer::MyServer()
{
    init();
}

void MyServer::login(const User &user)
{
    QNetworkRequest request;

    QString var;
    var += "account="+user.getAccount()+"&password="+user.getPassword()+"&method=status&version="+QString(VERSION_STR);
    var = APP_SERVER + var;
    request.setUrl(QUrl(var));
    qDebug()<<var;
    manager->get(request);

}

void MyServer::userRegister(const User &user)
{
    QNetworkRequest request;

    QString var;
    var += "account="+user.getAccount()+"&password="+user.getPassword()+
            "&trueName="+user.getTrueName()+
            "&grade="+user.getGrade()+
            "&sex="+user.getSex()+
            "&method=register";
    var = APP_Visiter + var;
    request.setUrl(QUrl(var));
    qDebug()<<var;
    manager->get(request);
}

void MyServer::requestMac()
{
    QNetworkRequest request;

    QString var;
    var += "method=getStudioMac";
    var = APP_Index + var;
    request.setUrl(QUrl(var));
    qDebug()<<var;
    manager->get(request);
}

void MyServer::requestUpdateTimers(const User &user)
{
    QNetworkRequest request;

    QString var;
    var += "account="+user.getAccount()+"&password="+user.getPassword()+"&count="+QString::number(user.getTodayCount())
            +"&method=updateTimer";
    var = APP_SERVER + var;
    request.setUrl(QUrl(var));
    qDebug()<<var;
    manager->get(request);
}

void MyServer::requestStatistic(const User &user)
{
    QNetworkRequest request;

    QString var;
    var += "account="+user.getAccount()+"&password="+user.getPassword()+"&method=statistic";
    var = APP_SERVER + var;
    request.setUrl(QUrl(var));
    qDebug()<<var;
    manager->get(request);
}

void MyServer::requestVersion()
{
    QNetworkRequest request;

    QString var;
    var += "method=version";
    var = APP_Visiter + var;
    request.setUrl(QUrl(var));
    manager->get(request);
}

void MyServer::answer(QNetworkReply *reply)
{
    QByteArray byteArray;
    byteArray = reply->readAll();
    if(byteArray.isEmpty())
    {
        emit sError("请检查网络");
        reply->deleteLater();
        return;
    }
    else
    {
        QJsonDocument jsonDoc;
        jsonDoc = QJsonDocument::fromJson(byteArray);

        if(jsonDoc.isNull()) return;
        QVariantMap result = jsonDoc.toVariant().toMap();
        QString method = result["method"].toString();

        if(result["status"].toString()=="400")
        {
            emit sLoginFail(result["message"].toString());
            reply->deleteLater();
            return;
        }

        if(method=="version")
        {
            emit sVersion(result["version"].toString(),result["downloadUrl"].toString());
        }
        else if(method=="status")
        {
            QVariantMap map = result["user"].toMap();

            qDebug()<<map["account"].toString();

            User user;

            user.setAccount(map["account"].toString());
            user.setTrueName(map["user_name"].toString());
            user.setPassword(map["user_password"].toString());
            user.setSex(map["sex"].toString());
            user.setGrade(map["grade"].toString());

            QVariantMap dateMap = map["dates"].toMap();

            user.setBegin(QDate::fromString(dateMap["begin"].toString(),"yyyy-MM-dd"));
            user.setEnd(QDate::fromString(dateMap["end"].toString(),"yyyy-MM-dd"));
            user.setToday(QDate::fromString(dateMap["today"].toString(),"yyyy-MM-dd"));

            user.setTotalCount(map["total"].toInt());
            user.setTodayCount(map["today"].toInt());

            QVariantList timerList = map["times"].toList();
            QList<TimerRecord> recordList;
            TimerRecord re;
            for(QVariant t:timerList)
            {
                QVariantMap map = t.toMap();
                re.date = QDate::fromString(map["times_date"].toString(),"yyyy-MM-dd");
                re.count = map["times_count"].toInt();
                recordList.append(re);
            }

            user.setTimerRecord(recordList);


            emit sLogin(user);
        }
        else if(method=="getStudioMac")
        {
            QVariantList list = result["macs"].toList();
            QList<QString>macs;
            for(QVariant t:list)
            {
                macs.append(t.toString());
            }
            sMac(macs);
        }
        else if(method=="updateTimer")
        {
            emit sUpdateTimer();
        }
        else if(method=="statistic")
        {
            QVariantList lists = result["lists"].toList();

            QList<StatisticBag>bags;
            StatisticBag bag;
            for(QVariant t:lists)
            {
                QVariantMap tMap = t.toMap();

                bag.name = tMap["user_name"].toString();
                bag.timeCount = tMap["user_count"].toString();
                bag.top = tMap["top"].toInt();
                bags.append(bag);
            }
            emit sStatisticBag(bags);
        }
        else if(method=="register")
        {
            if(result["status"].toString()=="401")
            {
                sError(result["message"].toString());
            }
            else
            {
                sRegister(result["message"].toString());
            }
        }

    }
    reply->deleteLater();
}

void MyServer::init()
{
    manager = new QNetworkAccessManager(this);

    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(answer(QNetworkReply*)));
}


