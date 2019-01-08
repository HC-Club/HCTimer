#include "Updater.h"
#include "TimerWindow.h"

Updater::Updater(QObject *parent) : QObject(parent)
{
    manager = new QNetworkAccessManager(this);
}

Updater::~Updater()
{

    if(QFile::exists(downloadFileName))//如果文件已经存在，那么删除
    {
        file->flush();
        file->close();
        reply->deleteLater();
        reply = NULL;
        delete file;
        file = NULL;
//        QFile::remove(downloadFileName);//注意：若文件正在使用中则无法正常删除
    }

}

void Updater::startRequest(QUrl url)
{
    QFileInfo info(url.path());
    downloadFileName = info.fileName();

    file = new QFile(downloadFileName);
    if(!file->open(QIODevice::ReadWrite))
    {
        qDebug() << "file open error";
        delete file;
        file = NULL;
        return;
    }

    reply = manager->get(QNetworkRequest(url));

    connect(reply, SIGNAL(readyRead()), this, SLOT(httpReadyRead()));

    connect(reply, SIGNAL(finished()), this, SLOT(httpFinished()));
}

void Updater::httpReadyRead()
{
    if (file)
        file->write(reply->readAll());
}

void Updater::setTimerWindow(TimerWindow *value)
{
    timerWindow = value;
}


void Updater::httpFinished()
{
    QMessageBox::StandardButton rb = QMessageBox::question(NULL, "提示", "环创计时器有新版本，安装包已提前为您下载完成，是否要安装更新?",
                                                              QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
    if(rb == QMessageBox::Yes){
        file->flush();
        file->close();

        QString currentDir = QDir::currentPath();//当前程序运行路径
        QString downloadFilePath = currentDir+"/"+downloadFileName;//存放下载文件的路径

        timerWindow->runCMD(downloadFilePath);
        timerWindow->slotCloseApplication();
    }
}
