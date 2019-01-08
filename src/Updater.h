#ifndef UPDATER_H
#define UPDATER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>
#include <QFile>
#include <QFileInfo>
#include <QMessageBox>
#include <QDir>
#include <QFile>
#include <QTextStream>

class TimerWindow;


class Updater : public QObject
{
    Q_OBJECT
public:
    explicit Updater(QObject *parent = 0);
    ~Updater();
    void startRequest(QUrl url);

    void setTimerWindow(TimerWindow *value);

private slots:
    void httpFinished();
    void httpReadyRead();

private:
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    QFile *file;
    QString downloadFileName;

    TimerWindow *timerWindow;

};

#endif // UPDATER_H
