#include "SystemTrayIcon.h"

SystemTrayIcon::SystemTrayIcon(QSystemTrayIcon *)
{

}

SystemTrayIcon *SystemTrayIcon::getInstance()
{
    static SystemTrayIcon systemTrayIcon;
    return &systemTrayIcon;
}
