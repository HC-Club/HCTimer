#include "TimerWindow.h"
#include <QApplication>
#include "define.h"
#include "Monitor.h"

#if WINDOWS_VERSION   //for win

#include <windows.h>
bool isOnlyApplication()
{
    //  创建互斥量
    HANDLE m_hMutex  =  CreateMutex(NULL, FALSE,  L"fortest_abc123" );
    //  检查错误代码
    if  (GetLastError()  ==  ERROR_ALREADY_EXISTS)  {
      //  如果已有互斥量存在则释放句柄并复位互斥量
     CloseHandle(m_hMutex);
     m_hMutex  =  NULL;
      //  程序退出
      return  false;
    }
    else
        return true;
}
#elif LINUX_VERSION   //for linux

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
bool isOnlyApplication()
{
    const char filename[]  = "/tmp/lockfile";
    int fd = open (filename, O_WRONLY | O_CREAT , 0644);
    int flock = lockf(fd, F_TLOCK, 0 );
    if (fd == -1) {
            perror("open lockfile/n");
            return false;
    }
    //给文件加锁
    if (flock == -1) {
            perror("lock file error/n");
            return false;
    }
    //程序退出后，文件自动解锁
    return true;
}
#endif

int main(int argc, char *argv[])
{
    //设置注册表(全局)
    QCoreApplication::setOrganizationName("HCLab");
    QCoreApplication::setOrganizationDomain("hclab.cn");
    QCoreApplication::setApplicationName("HCTimer");

    QApplication a(argc, argv);
    //检查程序是否 已经启动过
    if(isOnlyApplication()==false)
        return 0;
    TimerWindow w;
    w.show();

    return a.exec();
}

