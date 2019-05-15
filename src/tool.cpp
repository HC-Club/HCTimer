#include "tool.h"

Tool::Tool()
{

}






QList<QString> Tool::getLocalMac()
{
    QProcess cmd_pro;
    QString cmd_str = QString("arp -a");

    cmd_pro.start("C://Windows//system32//cmd.exe",QStringList()<<"/c"<<cmd_str);
    cmd_pro.waitForStarted();
    cmd_pro.waitForFinished();
    QByteArray bytes = cmd_pro.readAllStandardOutput();
    QTextCodec * pTextC = QTextCodec::codecForName("System");

    QString result = pTextC->toUnicode(bytes).replace(QRegExp("动态"),"----");
    result = result.replace(QRegExp("[^0-9|a-z|A-Z-]"),"");
    QString pattern("([A-Fa-f0-9]{2}-){5}[A-Fa-f0-9]{2}[-]{4}");
    QRegExp rx(pattern);
    QList<QString> macs;
    int pos = 0;
    while(pos = result.indexOf(rx,pos+1),pos>=0)
    {
        macs.append(rx.cap());
    }
    return macs;
}

int Tool::compareStatisticBag(const StatisticBag &bag1, const StatisticBag &bag2)
{
    if(bag1.top==1||bag2.top==2)
    {
        return 1;
    }

    if(bag1.top==2||bag2.top==1)
    {
        return 0;
    }

    if(bag1.timeCount.toInt()-bag2.timeCount.toInt()>0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
