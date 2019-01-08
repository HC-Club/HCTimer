#ifndef SYSTEMTRAYICON_H
#define SYSTEMTRAYICON_H

#include <QSystemTrayIcon>

class SystemTrayIcon : public QSystemTrayIcon
{
    Q_OBJECT
public:
    static SystemTrayIcon* getInstance();

private:
    explicit SystemTrayIcon(QSystemTrayIcon *parent = 0);

};

#endif // SYSTEMTRAYICON_H
