#include "DOHelper.h"

DOHelper *DOHelper::getDOHelper()
{
    static DOHelper doHelper;   //局部静态变量
    return &doHelper;
}

void DOHelper::getUpdateVersionsRequst()
{
    QNetworkRequest request;
    QString requestUrl;
    requestUrl="User/getVersions";
    request.setUrl(QUrl(BASIC_URL+requestUrl));
    netWorkerAction = GetUpdateVersionsAction;
    netWorker->get(request);
}

void DOHelper::getServerDateRequst()
{
    QNetworkRequest request;
    QString requestUrl;
    requestUrl="Times/getServerTime?type=date";
    request.setUrl(QUrl(BASIC_URL+requestUrl));
    netWorkerAction=GetServerDateAction;
    netWorker->get(request);
}


//加密函数-------------------修改位置

uint DOHelper::encrypt(uint data){
    data ^= dataKey1;
    data -= firstMove;
    data ^= dataKey2;
    data += secondMove;
    return data;
}

void DOHelper::addRecordRequst(QString userId,QString timesDate)
{
    QNetworkRequest request;
    QString requestUrl;
    requestUrl=requestUrl+"Times/addRecord?"+"user_id="+userId+"&times_date="+timesDate;
    request.setUrl(QUrl(BASIC_URL+requestUrl));
    netWorkerAction=AddRecordAction;
    netWorker->get(request);
}


void DOHelper::updateRecordRequst(QString userId, QString timesDate, uint timesCount)
{
    QNetworkRequest request;
    QString requestUrl;
//-----------修改位置-----------
    uint e_timesCount;
    e_timesCount = encrypt(timesCount);
    requestUrl=requestUrl+"Times/updateRecord?"+"user_id="+userId+"&times_date="
              +timesDate+"&times_count="+QString::number(e_timesCount)
              +"&versions="+VERSION_STR;
    request.setUrl(QUrl(BASIC_URL+requestUrl));
    netWorkerAction=UpdateRecordAction;
    netWorker->get(request);
}

void DOHelper::getUserTimesRequst(QString userId,QString startDate,QString endDate)
{
    QNetworkRequest request;
    QString requestUrl;
    requestUrl=requestUrl+"Times/getUserTimes?"+"user_id="+userId+"&start_date="+startDate+"&end_date="+endDate;
    request.setUrl(QUrl(BASIC_URL+requestUrl));
    netWorkerAction=GetUserTimesAction;
    netWorker->get(request);
}

void DOHelper::getAllUserTimesRequst(QString startDate,QString endDate)
{
    QNetworkRequest request;
    QString requestUrl;
    requestUrl=requestUrl+"Times/getUserTimes?"+"start_date="+startDate+"&end_date="+endDate;
    request.setUrl(QUrl(BASIC_URL+requestUrl));
    netWorkerAction = GetAllUserTimesAction;
    netWorker->get(request);
}

void DOHelper::getAllSpecificUserTimesRequst(QString startDate,QString endDate)
{
    QNetworkRequest request;
    QString requestUrl;
    requestUrl=requestUrl+"Times/getUserTimes?"+"start_date="+startDate+"&end_date="+endDate;
    request.setUrl(QUrl(BASIC_URL+requestUrl));
    netWorkerAction = GetAllSpecificUserTimesAction;
    netWorker->get(request);
}

void DOHelper::regRequst(QString account,QString userName,QString userPassword,QString sex,QString grade)
{
    QNetworkRequest request;
    QString requestUrl;
    requestUrl=requestUrl+"User/reg?"+"account="+account+"&user_name="+userName
            +"&user_password="+userPassword+"&sex="+sex+"&grade="+grade;
    request.setUrl(QUrl(BASIC_URL+requestUrl));
    netWorkerAction=RegAction;
    netWorker->get(request);
}

void DOHelper::loginRequst(QString account,QString userPassword)
{
    QNetworkRequest request;
    QString requestUrl;
    requestUrl=requestUrl+"User/login?"+"account="+account+"&user_password="+userPassword;
    request.setUrl(QUrl(BASIC_URL+requestUrl));
    netWorkerAction=LoginAction;
    netWorker->get(request);
}

void DOHelper::getUserInfoRequst(QString userId)
{
    QNetworkRequest request;
    QString requestUrl;
    requestUrl=requestUrl+"User/getUserInfo?"+"user_id="+userId;
    request.setUrl(QUrl(BASIC_URL+requestUrl));
    netWorkerAction=GetUserInfoAction;
    netWorker->get(request);
}

void DOHelper::updateUserInfoRequst(QString userId,QString account,QString userName,QString userPassword,QString sex,QString grade)
{
    QNetworkRequest request;
    QString requestUrl;
    requestUrl=requestUrl+"User/updateUserInfo?"+"user_id="+userId+"&account="+account+"&user_name="+userName
            +"&user_password="+userPassword+"&sex="+sex+"&grade="+grade;
    request.setUrl(QUrl(BASIC_URL+requestUrl));
    netWorkerAction=UpdateUserInfoAction;
    netWorker->get(request);

}

void DOHelper::addNoticeRequst(QString date,QString content)
{
    QNetworkRequest request;
    QString requestUrl;
    requestUrl=requestUrl+"Notice/addNotice?"+"date="+date+"&content="+content;
    request.setUrl(QUrl(BASIC_URL+requestUrl));
    netWorkerAction=AddNoticeAction;
    netWorker->get(request);
}

void DOHelper::getNoticeRequst()
{
    QNetworkRequest request;
    QString requestUrl;
    requestUrl="Notice/getNotice";
    request.setUrl(QUrl(BASIC_URL+requestUrl));
    netWorkerAction=GetNoticeAction;
    netWorker->get(request);
}

void DOHelper::refreshGetNoticeRequst(QString refreshMethod,QString id)
{
    QNetworkRequest request;
    QString requestUrl;
    requestUrl=requestUrl+"Notice/getNotice?"+"refresh_method="+refreshMethod+"&id="+id;
    request.setUrl(QUrl(BASIC_URL+requestUrl));
    netWorkerAction=RefreshGetNoticeAction;
    netWorker->get(request);
}

void DOHelper::delNoticeRequst(QString id)
{
    QNetworkRequest request;
    QString requestUrl;
    requestUrl=requestUrl+"Notice/delNotice?"+"id="+id;
    request.setUrl(QUrl(BASIC_URL+requestUrl));
    netWorkerAction=DelNoticeAction;
    netWorker->get(request);
}

DOHelper::DOHelper(QObject *)
{
    userData = UserData::getUserData();
    trayIcon = SystemTrayIcon::getInstance();
    netWorker=new QNetworkAccessManager(this);
    settings = new QSettings("settings.ini", QSettings::IniFormat);
    connect(netWorker,SIGNAL(finished(QNetworkReply*)),this,SLOT(replyfinished(QNetworkReply*)));
}


/**********网络请求完毕后的响应函数*************/

void DOHelper::replyfinished(QNetworkReply *reply)
{
    QByteArray byteArray;
    QString applicationVersion = QString("HC Timer V")+VERSION_STR;

    byteArray=reply->readAll();

    if(byteArray.isNull()){
        trayIcon->showMessage(applicationVersion,tr("无法连接服务器"),
                                          QSystemTrayIcon::Information, 200);
        return;
    }

    QJsonDocument jsonDoc;
    QJsonParseError error ;

    jsonDoc = QJsonDocument::fromJson(byteArray, &error);

    if (true/*error.error == QJsonParseError::NoError*/)//注释掉的原因是与某些网络类库起冲突,且解决电脑断网时计时器崩溃的问题
    {
        if (jsonDoc.isObject()||jsonDoc.isEmpty())
        {
            QVariantMap result = jsonDoc.toVariant().toMap();
            int code=result["code"].toInt();

            switch(netWorkerAction)
            {
                /*****获取服务器计时器更新版本响应****/
               case GetUpdateVersionsAction:
                    if(code==0)
                    {
                        if(!result["versions"].toString().isEmpty())
                            userData->updateVersions = result["versions"].toString();
                        if(!result["downloadURL"].toString().isEmpty())
                            userData->downloadURL = QString("http://"+result["downloadURL"].toString());
                        if(!userData->updateVersions.isNull())
                            userData->isGetUpdateVersion = true;
                        qDebug()<<"版本:"<<userData->updateVersions;
                        qDebug()<<"下载链接:"<<userData->downloadURL;
                        QFile file( "downloadURL.txt" );
                        //QIODevice::Truncate 以重写的方式打开，再写入新的数据
                        if ( file.open( QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text ) ) {
                            QTextStream stream( &file );
                            stream << userData->downloadURL<<"\n";
                            file.close();
                        }

                    }
                    else{
                        //
                    }
                    break;
                /*****获取服务器日期响应****/
                case GetServerDateAction:
                    if(code==0)
                    {
                        if(!result["time"].toString().isEmpty())
                            userData->setServerDate(result["time"].toString().mid(0,4).toInt(),
                                                    result["time"].toString().mid(5,2).toInt(),
                                                    result["time"].toString().mid(8,2).toInt());
                        if(userData->getServerDate().isValid())
                            userData->isGetServerTime = true;
                        if(!userData->getUserAccount().isEmpty() && !userData->getUserPassword().isEmpty())
                            loginRequst(userData->getUserAccount(),userData->getUserPassword());
                    }
                    else{
                        //
                    }
                    break;
                /*****添加用户的时间记录响应****/
                case AddRecordAction:
                    if(code==0){
                        if(!userData->getUserID().isEmpty() && !userData->getServerDate().isNull()
                                 && userData->getTimeCount() > 0 )
                            updateRecordRequst(userData->getUserID(),userData->getServerDate().toString(Qt::ISODate),
                                               userData->getTodayTime()+userData->getTimeCount());
                    }
                    else if(code==1){
                        trayIcon->showMessage(applicationVersion,tr("用户不存在"),
                                                          QSystemTrayIcon::Information, 200);
                    }
                    else if(code==2){
                        trayIcon->showMessage(applicationVersion,tr("用户当天记录已存在"),
                                                          QSystemTrayIcon::Information, 200);
                    }
                    else{
                        trayIcon->showMessage(applicationVersion,tr("异常错误"),
                                                          QSystemTrayIcon::Information, 200);
                    }
                    break;
                /*****更新用户的时间记录响应****/
                case UpdateRecordAction:
                    if(code==0)
                    {
                        if(!userData->isAutoUpdate){
                            trayIcon->showMessage(applicationVersion,tr("更新成功"),
                                                                 QSystemTrayIcon::Information, 200);
                        }
                    }
                    else if(code==1){
                        trayIcon->showMessage(applicationVersion,tr("用户不存在"),
                                                          QSystemTrayIcon::Information, 200);
                    }
                    else if(code==2){
                        if(!userData->getUserID().isEmpty() && !userData->getServerDate().isNull())
                            addRecordRequst(userData->getUserID(),userData->getServerDate().toString(Qt::ISODate));
                    }
                    else if(code==3){
                        trayIcon->showMessage(applicationVersion,tr("版本太低，请更新"),
                                                          QSystemTrayIcon::Information, 200);
                    }
                    else{
                        trayIcon->showMessage(applicationVersion,tr("异常错误"),
                                                          QSystemTrayIcon::Information, 200);
                    }
                    break;
                /*****查询用户时间响应****/
                case GetUserTimesAction:
                    if(code==0)
                    {
                        QList<QVariant> nestedMapArray =result["times"].toList();
                        int totaltime = 0;
                        for(int i=0;i<nestedMapArray.length();i++){
                            QVariantMap map=nestedMapArray[i].toMap();
                            QString times_date = map["times_date"].toString();
                            int times_count = map["times_count"].toString().toInt();
                            totaltime += times_count;
                            userData->setUserTime(times_date.mid(0,4).toInt(),
                                                  times_date.mid(5,2).toInt(),
                                                  times_date.mid(8,2).toInt(),times_count);
                        }
                        userData->setTotalTime(totaltime);
                        getUserInfoRequst(userData->getUserID());
                    }
                    else if(code==1){
                        trayIcon->showMessage(applicationVersion,tr("用户不存在"),
                                                          QSystemTrayIcon::Information, 200);
                    }
                    else{
                        trayIcon->showMessage(applicationVersion,tr("异常错误"),
                                                          QSystemTrayIcon::Information, 200);
                    }
                    break;
                /*****查询所有用户时间响应****/
                case GetAllUserTimesAction:
                    if(code==0)
                    {
                        QList<QVariant> nestedMapArray =result["times"].toList();
                        for(int i=0;i<nestedMapArray.length();i++){
                            QVariantMap map=nestedMapArray[i].toMap();
                            QString userName = map["user_name"].toString();
                            QString userTime = map["times_count"].toString();
                            userData->setAllUsers(userName,userTime);
                        }
                    }
                    else if(code==1){
                        trayIcon->showMessage(applicationVersion,tr("用户不存在"),
                                                          QSystemTrayIcon::Information, 200);
                    }
                    else{
                        trayIcon->showMessage(applicationVersion,tr("异常错误"),
                                                          QSystemTrayIcon::Information, 200);
                    }
                    break;
                    /*****查询所有特定用户时间响应****/
                    case GetAllSpecificUserTimesAction:
                        if(code==0)
                        {
                            QList<QVariant> nestedMapArray =result["times"].toList();
                            for(int i=0;i<nestedMapArray.length();i++){
                                QVariantMap map=nestedMapArray[i].toMap();
                                QString userName = map["user_name"].toString();
                                QString userTime = map["times_count"].toString();
                                userData->setAllSpecificUsers(userName,userTime);
                            }
                        }
                        else if(code==1){
                            trayIcon->showMessage(applicationVersion,tr("用户不存在"),
                                                              QSystemTrayIcon::Information, 200);
                        }
                        else{
                            trayIcon->showMessage(applicationVersion,tr("异常错误"),
                                                              QSystemTrayIcon::Information, 200);
                        }
                        break;
                /*****注册响应****/
                case RegAction:
                    if(code==0)
                    {
                        trayIcon->showMessage(applicationVersion,tr("注册成功"),
                                                          QSystemTrayIcon::Information, 200);
                        if(!userData->getUserAccount().isEmpty())
                            settings->setValue("UserData/account",userData->getUserAccount());
                        if(!userData->getUserPassword().isEmpty())
                            settings->setValue("UserData/password",userData->getUserPassword());
                    }
                    else if(code==1)
                        trayIcon->showMessage(applicationVersion,tr("用户已存在"),
                                                          QSystemTrayIcon::Information, 200);
                    else{
                        trayIcon->showMessage(applicationVersion,tr("异常错误"),
                                                          QSystemTrayIcon::Information, 200);
                    }
                    break;
                /*****登录响应****/
                case LoginAction:
                    if(code==0){
                        if(!result["user_id"].toString().isEmpty())
                            userData->setUserID(result["user_id"].toString());
                        if(!userData->getUserID().isEmpty() && !userData->getstartDate_own().isNull()
                                 && !userData->getEndDate_own().isNull())
                        {
                            getUserTimesRequst(userData->getUserID(),userData->getstartDate_own().toString(Qt::ISODate),
                                               userData->getEndDate_own().toString(Qt::ISODate));
                            userData->isLogin = true;
                        }
                        if(!userData->getUserID().isEmpty())
                            settings->setValue("UserData/id",userData->getUserID());
                        if(!userData->getUserAccount().isEmpty())
                            settings->setValue("UserData/account",userData->getUserAccount());
                        if(!userData->getUserPassword().isEmpty())
                            settings->setValue("UserData/password",userData->getUserPassword());
                    }
                    else if(code==1){
                        trayIcon->showMessage(applicationVersion,tr("用户不存在"),
                                                          QSystemTrayIcon::Information, 200);
                    }
                    else if(code==2){
                        trayIcon->showMessage(applicationVersion,tr("密码错误"),
                                                          QSystemTrayIcon::Information, 200);
                    }
                    else{
                        trayIcon->showMessage(applicationVersion,tr("异常错误"),
                                                          QSystemTrayIcon::Information, 200);
                    }
                    break;
                /*****获取用户信息响应****/
                case GetUserInfoAction:
                    if(code==0)
                    {
                        QVariantMap nestedMap = result["info"].toMap();
                        if(!nestedMap["account"].toString().isEmpty())
                            userData->setUserAccount(nestedMap["account"].toString());
                        if(!nestedMap["user_name"].toString().isEmpty())
                            userData->setUserName(nestedMap["user_name"].toString());
                        if(!nestedMap["user_password"].toString().isEmpty())
                            userData->setUserPassWord(nestedMap["user_password"].toString());
                        if(!nestedMap["sex"].toString().isEmpty())
                            userData->setUserSex(nestedMap["sex"].toString());
                        if(!nestedMap["grade"].toString().isEmpty())
                            userData->setUserGrade(nestedMap["grade"].toString());
                        if(!userData->getUserName().isEmpty())
                            settings->setValue("UserData/name",userData->getUserName());
                        if(!userData->getUserAccount().isEmpty())
                            settings->setValue("UserData/account",userData->getUserAccount());
                        if(!userData->getUserSex().isEmpty())
                            settings->setValue("UserData/sex",userData->getUserSex());
                        if(!userData->getUserGrade().isEmpty())
                            settings->setValue("UserData/grade",userData->getUserGrade());
                    }
                    else if(code==1){
                        trayIcon->showMessage(applicationVersion,tr("用户不存在"),
                                                          QSystemTrayIcon::Information, 200);
                    }
                    else{
                        trayIcon->showMessage(applicationVersion,tr("异常错误"),
                                                          QSystemTrayIcon::Information, 200);
                    }
                    break;
                /*****修改用户信息响应****/
                case UpdateUserInfoAction:
                    if(code==0)
                        trayIcon->showMessage(applicationVersion,tr("修改成功"),
                                                          QSystemTrayIcon::Information, 200);
                    else if(code==1){
                        trayIcon->showMessage(applicationVersion,tr("用户不存在"),
                                                          QSystemTrayIcon::Information, 200);
                    }
                    else{
                        trayIcon->showMessage(applicationVersion,tr("异常错误"),
                                                          QSystemTrayIcon::Information, 200);
                    }
                    break;
                /*****发布公告响应****/
                case AddNoticeAction:
                    if(code==0)
                    {
                        trayIcon->showMessage(applicationVersion,tr("发表成功"),
                                                          QSystemTrayIcon::Information, 200);
                    }
                    else if(code==1){
                        trayIcon->showMessage(applicationVersion,tr("请务必填写完整"),
                                                          QSystemTrayIcon::Information, 200);
                    }
                    else{
                        trayIcon->showMessage(applicationVersion,tr("异常错误"),
                                                          QSystemTrayIcon::Information, 200);
                    }
                    break;
                /*****获取公告响应****/
                case GetNoticeAction:
                    if(code==0)
                    {
                        QList<QVariant> nestedMapArray =result["list"].toList();
                        for(int i=0;i<nestedMapArray.length();i++){
                            QVariantMap map=nestedMapArray[i].toMap();
                            QString notice_id = map["notice_id"].toString();
                            QString notice_date = map["notice_date"].toString();
                            QString notice_content = map["notice_content"].toString();
                            QString notice_createtime = map["notice_createtime"].toString();
                            if(i==0)
                            {
                                userData->setFirstNoticeID(notice_id);
                            }
                            if(i==nestedMapArray.length()-1)
                            {
                                userData->setEndNoticeID(notice_id);
                            }
                            userData->setNotices(notice_id,notice_date,notice_content,notice_createtime);
                        }
                    }
                    else{
                        trayIcon->showMessage(applicationVersion,tr("异常错误"),
                                                          QSystemTrayIcon::Information, 200);
                    }
                    break;
                /*****刷新模式下获取公告响应****/
                case RefreshGetNoticeAction:
                    if(code==0)
                    {
                        QList<QVariant> nestedMapArray =result["list"].toList();
                        if(nestedMapArray.length()<=0)
                        {
                            QMessageBox::about(NULL,"提示","公告为空！");
                            break;
                        }
                        for(int i=0;i<nestedMapArray.length();i++){
                            QVariantMap map=nestedMapArray[i].toMap();
                            QString notice_id = map["notice_id"].toString();
                            QString notice_date = map["notice_date"].toString();
                            QString notice_content = map["notice_content"].toString();
                            QString notice_createtime = map["notice_createtime"].toString();
                            if(i==0)
                            {
                                userData->setFirstNoticeID(notice_id);
                            }
                            if(i==nestedMapArray.length()-1)
                            {
                                userData->setEndNoticeID(notice_id);
                            }
                            userData->setNotices(notice_id,notice_date,notice_content,notice_createtime);
                        }
                    }
                    else{
                        trayIcon->showMessage(applicationVersion,tr("异常错误"),
                                                          QSystemTrayIcon::Information, 200);
                    }
                    break;
                /*****删除公告响应****/
                case DelNoticeAction:
                    if(code==0){
                        trayIcon->showMessage(applicationVersion,tr("删除公告成功"),
                                                          QSystemTrayIcon::Information, 200);
                    }
                    else{
                        trayIcon->showMessage(applicationVersion,tr("异常出错，删除公告失败"),
                                                          QSystemTrayIcon::Information, 200);
                    }
                    break;
            }
        }
    }
    else{
        qFatal(error.errorString().toUtf8().constData());
    }
    reply->deleteLater();
}

