#ifndef TOOL_H
#define TOOL_H

#include <QString>
#include <QList>
#include <QProcess>
#include <QTextCodec>
#include "user.h"
#include <QDebug>

class Tool
{
public:
    Tool();
    static QList<QString> getLocalMac();
    static int compareStatisticBag(const StatisticBag &bag1, const StatisticBag &bag2);
};

#endif // TOOL_H
