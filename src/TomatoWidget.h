#ifndef TOMATOWIDGET_H
#define TOMATOWIDGET_H

#include <QWidget>
#include <QAction>
#include <QCursor>
#include <QMenu>
#include <QContextMenuEvent>
#include "UserData.h"

class TomatoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TomatoWidget(QWidget *parent = 0);

protected:
    void initInterface();
    void paintEvent(QPaintEvent *event);
    void contextMenuEvent(QContextMenuEvent *);

private:
    int themeColor;
    UserData *userData;

    QMenu *menu;
    QAction *startTomatoTime;
    QAction *addTask;
    QAction *editAndCheckTask;
    QAction *settings;
    QAction *close;

public slots:
    void slotStartTomatoTime();
    void slotAddTask();
    void slotEditAndCheckTask();
    void slotSettings();
};

#endif // TOMATOWIDGET_H
