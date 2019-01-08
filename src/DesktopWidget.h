#ifndef WIDGET_H
#define WIDGET_H

#include <QtCore>
#include <QtGui>
#include <QApplication>
#include <QWidget>
#include <QDesktopWidget>
#include <QPushButton>
#include <QAction>
#include <QCursor>
#include <QMenu>
#include <QTimer>
#include <QSettings>
#include <QPainter>
#include <QLabel>
#include <QFont>
#include <QMessageBox>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QSound>
#include "DWSettingDialog.h"
#include "UserData.h"
#include "DOHelper.h"
#include "Monitor.h"
#include <qdebug.h>
#include <QDir>
#include <EditTaskDialog.h>


class DesktopWidget : public QWidget
{
    Q_OBJECT
public:
    DesktopWidget(QWidget *parent = 0);

    void runCMD(QString command);

protected:
    void initInterface();
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void contextMenuEvent(QContextMenuEvent *);

private:
    QMenu *menu;
    QAction *startTomatoTime;
    QAction *editAndCheckTask;
    QAction *widgetSettings;
    QAction *close;

    QTimer *tomatoTimer;

    QPoint beginDrag;
    bool bPressFlag;

    UserData *userData;
    DOHelper *http;
    Monitor *monitor;

    QSettings *settings;

    bool isInTomatoTime;
    bool isInRestTime;
    bool isInLongRestTime;

    int countDownTime;
    int tomatoTime;
    int restTime;
    int longRestTime;
    int volume;
    bool isStartWorkSound;

    int tomatoFinishedCount;//已完成的番茄任务计数值

    int circleValue;//画倒计时圆圈周长的值

    QPushButton *updateBtn;

    QLabel *countDownTimeLabel;

    QMediaPlayer *cueMediaPlayer;
    QMediaPlayer *workSoundPlayer;
    QMediaPlaylist *playList;

private slots:
    void slotUpdateBtn();
    void slotStartTomatoTime();
    void slotEditAndCheckTask();
    void slotWidgetSettings();
    void slotClose();
    void slotTomatoTimer();
};

#endif // WIDGET_H
