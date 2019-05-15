#include "Monitor.h"

static int inactiveTime = 0;//记录鼠标键盘不活动时间

#if WINDOWS_VERSION
//    HHOOK keyHook = NULL;
//    HHOOK mouseHook = NULL;

//LRESULT CALLBACK keyProc(int ,WPARAM ,LPARAM )
//{
//    inactiveTime = 0;//键盘事件正在发生，将监测时间置0
//    return 0;//返回0表示将接受到的键盘信息返回，返回1表示将接收的键盘信息截住
//}

//LRESULT CALLBACK mouseProc(int ,WPARAM ,LPARAM )
//{
//    inactiveTime =0;//鼠标事件正在发生，将监测时间置0
//    return 0;//返回0表示将接受到的鼠标信息返回，返回1表示将接收的鼠标信息截住
//}

//void unHook()
//{
//    UnhookWindowsHookEx(keyHook);
//    UnhookWindowsHookEx(mouseHook);
//}

//void setHook()
//{
//    keyHook =SetWindowsHookEx( WH_KEYBOARD_LL,keyProc,GetModuleHandle(NULL),0);//底层键盘钩子
//    mouseHook =SetWindowsHookEx( WH_MOUSE_LL,mouseProc,GetModuleHandle(NULL),0);//底层鼠标钩子
//}

#elif LINUX_VERSION

#elif MAC_VERSION

#endif
/**
 * @brief Monitor::isCanUpdate 判断当前是否可以更新时间
 * @return true or false
 */
bool Monitor::isCanUpdate()
{
    if(isUserOnline()){
        if(inactiveTime<LIMIT_TIME){
            return true;
        }
        else{
            return false;
        }
    }
    else{
        return false;
    }
}

Monitor *Monitor::getMonitor()
{
    static Monitor monitor;

    return &monitor;
//    Monitor* Monitor::p = new Monitor;
//    return p;
}

Monitor::Monitor(QObject *)
{
#if WINDOWS_VERSION
//    setHook();//新建钩子
#elif LINUX_VERSION

#elif MAC_VERSION

#endif
    isLabRouterMAC = true;

    timer = new QTimer(this);//此定时器用来监测键盘鼠标是否超过LIMIT_TIME(30分钟)不活动
    connect(timer,SIGNAL(timeout()),this,SLOT(upDateTime()));
    timer->start(1000);//每秒更新一次
}

Monitor::~Monitor()
{
#if WINDOWS_VERSION
//    unHook();//删除钩子
#elif LINUX_VERSION

#elif MAC_VERSION

#endif
}
/**
 * @brief Monitor::isUserOnline 判断用户是否在线
 * @return true or false
 */
bool Monitor::isUserOnline()
{
    QString IP;
    QHostInfo info=QHostInfo::fromName(QHostInfo::localHostName());
    foreach(QHostAddress address, info.addresses()){
        if(address.protocol() == QAbstractSocket::IPv4Protocol){
            IP=address.toString();
//            qDebug()<<IP<<endl;
            if (IP.startsWith( MONITOR_IP_PREIX ) || IP.startsWith(MONITOR_IP_PREXI2)){
             return true;
             }
        }
    }
     return false;
}


bool Monitor::isLabRouter()
{

#if WINDOWS_VERSION
    #define EXECDOSCMD "arp -a" //命令

    SECURITY_ATTRIBUTES sa;
    HANDLE hRead,hWrite;

    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.lpSecurityDescriptor = NULL;
    sa.bInheritHandle = TRUE;
    if (!CreatePipe(&hRead,&hWrite,&sa,0))
    {
        return false;
    }
    char command[1024]; //长达1K的命令行，够用了吧
    strcpy(command,"Cmd.exe /C ");

    strcat(command,EXECDOSCMD);
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    si.cb = sizeof(STARTUPINFO);
    GetStartupInfo(&si);
    si.hStdError = hWrite; //把创建进程的标准错误输出重定向到管道输入
    si.hStdOutput = hWrite; //把创建进程的标准输出重定向到管道输入
    si.wShowWindow = SW_HIDE;
    si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
    //关键步骤，CreateProcess函数参数意义请查阅MSDN
    QString str(command);

    if (!CreateProcess(NULL, (LPWSTR)str.utf16(),NULL,NULL,TRUE,0,NULL,NULL,&si,&pi))
    {
        CloseHandle(hWrite);
        CloseHandle(hRead);
        return false;
    }
    CloseHandle(hWrite);


    char buffer[4096] = {0}; //用4K的空间来存储输出的内容，只要不是显示文件内容，一般情况下是够用了。
    DWORD bytesRead;
    QString strArp;
    while (true)
    {
        if (!ReadFile(hRead,buffer,4095,&bytesRead,NULL))
           break;
        //buffer中就是执行的结果，可以保存到文本，也可以直接输出
        QString strTemp(buffer);
        strArp = strTemp;
    }
    const int routerNumber = 4;
    QString ip[routerNumber];
    ip[0] = "30-fc-68-43-bc-00";      //hc-gray
    ip[1] = "fc-d7-33-52-d4-46";      //hc-blue
    ip[2] = "e4-d3-32-45-2c-14";      //hc-black
    ip[3] = "8c-ab-8e-33-72-91";      //hc-2.4g

    for(int k = 0;k < routerNumber;k++){
        int i = 0,j = 0;
        while(i < strArp.length() && j < ip[k].length()){
            if(strArp[i] == ip[k][j]){
                i++;
                j++;
            }
            else{
                i++;
                j = 0;
            }
            if(j == ip[k].length()){
                CloseHandle(hRead);
                isLabRouterMAC = true;
                return true;
            }
        }
    }
    strArp.clear();
    CloseHandle(hRead);
    isLabRouterMAC = false;
    return false;
#elif LINUX_VERSION
    return true;
#endif
}

/**
 * @brief Monitor::upDateTime 判断是否在检测范围内并操作用户在线时间
 * @return none
 */
void Monitor::upDateTime()
{
#if WINDOWS_VERSION

#elif LINUX_VERSION
    if(isUserOnline() && isLabRouterMAC){
        inactiveTime = 0;
        if(inactiveTime>LIMIT_TIME){
            return;
        }
        else{
            userData->setTimeCount(userData->getTimeCount()+1);
        }
    }
#elif MAC_VERSION

#endif
}
