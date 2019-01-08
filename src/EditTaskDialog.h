#ifndef EDITTASKDIALOG_H
#define EDITTASKDIALOG_H


#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QMouseEvent>
#include <QSettings>
#include <QPainter>
#include <QtMath>
#include <QFont>
#include <QMessageBox>
#include <QDebug>

#include <QMenu>
#include <QAction>
#include <QLineEdit>
#include <QListWidget>
#include <QListWidgetItem>
#include <QList>
#include <QContextMenuEvent>
#include <QMenu>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

typedef struct Task{
    bool isFinished;
    QString content;
}Task;

class EditTaskDialog : public QDialog
{
    Q_OBJECT
public:
    explicit EditTaskDialog(QDialog *parent = 0);

protected:
    void initInterface();
    void showTasks();
    void readTasksFile();
    void writeTasksFile();
    void writeAppendTasksToFile(Task task);

    QPoint beginDrag;
    bool bPressFlag;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void paintEvent(QPaintEvent *);

private:
    QPushButton *closeBtn;
    QPushButton *confirmBtn;

    QMenu *menu;
    QAction *markFinished;
    QAction *topTask;
    QAction *deleteTask;

    QLineEdit *newTask;

    QListWidget* listWidget;
    QListWidgetItem* listItem;

    QSettings *settings;
    QList<Task> tasks;


public slots:
    void slotDoubleItemClicked();//双击击列表项出现菜单
    void slotAddNewTask();
    void slotMarkFinished();
    void slotTopTask();
    void slotDeleteTask();
};

#endif // EDITTASKDIALOG_H
