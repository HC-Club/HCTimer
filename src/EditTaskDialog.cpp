#include "EditTaskDialog.h"

EditTaskDialog::EditTaskDialog(QDialog *parent) : QDialog(parent)
{
    settings = new QSettings("settings.ini", QSettings::IniFormat);
    resize(392,342);

    bPressFlag = false;
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    //白色背景设置
    QPalette bgPalette;
    bgPalette.setColor(QPalette::Background, QColor("#FFF"));
    this->setPalette(bgPalette);
    this->setAutoFillBackground(true);
    initInterface();
}

void EditTaskDialog::initInterface()
{
    QFont ft;
    ft.setFamily("冬青黑体简体中文 W3");
    ft.setPixelSize(16);

    closeBtn = new QPushButton(this);
    closeBtn->setGeometry(350,14,25,25);
    closeBtn->setStyleSheet("QPushButton{border-image: url(:images/close_small.png);}"
                            "QPushButton:hover{border-image: url(:images/close_small_hover.png);}"
                            "QPushButton:pressed{border-image: url(:images/close_small.png);}");
    connect(closeBtn,SIGNAL(clicked()),this,SLOT(hide()));

    newTask = new QLineEdit(this);
    newTask->setAlignment(Qt::AlignVCenter);
    newTask->setFont(ft);
    newTask->setStyleSheet("QTextEdit{background-color:#FFF;color:black;}"
                           "QScrollBar{background:transparent; height:10px; }");
    newTask->setPlaceholderText(tr(" 添加新番茄（18个字符以内）"));
    newTask->setMaxLength(18);
    newTask->setGeometry(26,42,300,30);
    connect(newTask, SIGNAL(returnPressed()),
            this, SLOT(slotAddNewTask()));

    confirmBtn = new QPushButton(this);
    confirmBtn->setGeometry(336,40,32,32);
    confirmBtn->setStyleSheet("QPushButton{border-image: url(:images/confirm.png);}"
                              "QPushButton:hover{border-image: url(:images/confirm_hover.png);}"
                              "QPushButton:pressed{border-image: url(:images/confirm.png);}");
    connect(closeBtn,SIGNAL(clicked()),this,SLOT(slotAddNewTask()));

    listWidget = new QListWidget(this);
    listWidget->setFrameShape(QListWidget::NoFrame);
    listWidget->setStyleSheet(
                "QListWidget{background:transparent;}"
                "QListWidget::Item:hover{background:#F0F8FF; }"
                "QListWidget::item:selected{background:white;color:#55C3EF; }"
                "QScrollBar{background:transparent; height:10px; }"
                );
    listWidget->move(26,88);
    listWidget->setIconSize(QSize(64, 40));
    listWidget->resize(340,222);

    connect(listWidget, SIGNAL(itemDoubleClicked(QListWidgetItem *)),
            this, SLOT(slotDoubleItemClicked()));

    markFinished = new QAction(tr("标记为已完成"), this);
    connect(markFinished, SIGNAL(triggered()), this, SLOT(slotMarkFinished()));
    topTask = new QAction(tr("置顶"), this);
    connect(topTask, SIGNAL(triggered()), this, SLOT(slotTopTask()));
    deleteTask = new QAction(tr("删除"), this);
    connect(deleteTask, SIGNAL(triggered()), this, SLOT(slotDeleteTask()));

    menu=new QMenu(this);
    menu->addAction(markFinished);
    menu->addAction(topTask);
    menu->addAction(deleteTask);

    readTasksFile();
    showTasks();
}

void EditTaskDialog::slotDoubleItemClicked()
{
    QCursor cur=this->cursor();
    menu->exec(cur.pos()); //关联到鼠标位置
}

void EditTaskDialog::readTasksFile()
{
    QFile file( "tasksFile.txt" );
    if ( file.open( QIODevice::ReadOnly ) ){
        QTextStream stream( &file );
        Task tmpTask;
        while( !stream.atEnd() ) {
            if(stream.readLine() == "1")
                tmpTask.isFinished = true;
            else
                tmpTask.isFinished = false;
            tmpTask.content = stream.readLine();//不包括“/n”的一行文本
            tasks.append(tmpTask);
        }
        file.close();
    }
}

void EditTaskDialog::writeTasksFile()
{
    QFile file( "tasksFile.txt" );
    //QIODevice::Truncate 以重写的方式打开，在写入新的数
    if ( file.open( QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text ) ) {
        QTextStream stream( &file );
        for ( int i=0; i<tasks.length(); i++ ){
            stream << tasks.at(i).isFinished<<"\n";
            stream <<tasks.at(i).content<<"\n";
        }
        file.close();
    }
}

void EditTaskDialog::writeAppendTasksToFile(Task task)
{
    QFile file( "tasksFile.txt" );
    //QIODevice::Append 以追加的方式打开，新增加的内容将被追加到文件末尾
    if ( file.open( QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text ) ) {
        QTextStream stream( &file );
        stream << task.isFinished<<"\n";
        stream <<task.content<<"\n";
        file.close();
    }
}

void EditTaskDialog::showTasks()
{
    QFont ft;
    ft.setFamily("冬青黑体简体中文 W3");
    ft.setPixelSize(16);

    listWidget->clear();

    for(int i=0; i<tasks.length(); i++){
        QString radioPath;
        if(tasks.at(i).isFinished)
            radioPath = ":/images/btn_radio_active.png";
        else
            radioPath = ":/images/btn_radio.png";
        QListWidgetItem *isFinishedItem = new QListWidgetItem();
        isFinishedItem->setSizeHint(QSize(340,32));
        isFinishedItem->setIcon(QIcon(radioPath));
        isFinishedItem->setText(QString(" ")+tasks.at(i).content);
        isFinishedItem->setFont(ft);
        isFinishedItem->setBackground(QColor(244,244,244));

        listWidget->addItem(isFinishedItem);
    }
}

void EditTaskDialog::slotAddNewTask()
{
    if(!newTask->text().isEmpty()){
        Task tmpTask;
        tmpTask.isFinished = false;
        tmpTask.content = newTask->text();
        tasks.append(tmpTask);
        writeAppendTasksToFile(tmpTask);
        showTasks();
    }
}

void EditTaskDialog::slotMarkFinished()
{
    int row = listWidget->currentRow();
    if(row<0 && row>=tasks.length())
        return;
    Task tmp;
    tmp.isFinished = true;
    tmp.content = tasks.at(row).content;
    tasks.replace(row,tmp);
    writeTasksFile();
    showTasks();
}

void EditTaskDialog::slotTopTask()
{
    int row = listWidget->currentRow();
    if(row<0 && row>=tasks.length())
        return;
    tasks.insert(0,tasks.at(row));
    tasks.removeAt(row);
    writeTasksFile();
    showTasks();
}

void EditTaskDialog::slotDeleteTask()
{
    int row = listWidget->currentRow();
    if(row<0 && row>=tasks.length())
        return;
    listWidget->takeItem(row);
    tasks.removeAt(row);
    writeTasksFile();
}

/**
 * @brief EditTaskDialog::keyPressEvent 重写键盘事件，使之按Enter键窗口不关闭
 */
void EditTaskDialog::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
        case Qt::Key_Enter:
            return;
        default:
            QDialog::keyPressEvent(event);
    }
}

void EditTaskDialog::mousePressEvent(QMouseEvent *event)
{
    bPressFlag = true;
    beginDrag = event->pos();
    QWidget::mousePressEvent(event);
}

void EditTaskDialog::mouseMoveEvent(QMouseEvent *event)
{
    if (bPressFlag) {
        QPoint relaPos(QCursor::pos() - beginDrag);
        move(relaPos);
    }
    QWidget::mouseMoveEvent(event);
}

void EditTaskDialog::mouseReleaseEvent(QMouseEvent *event)
{
    bPressFlag = false;
    QWidget::mouseReleaseEvent(event);
}

void EditTaskDialog::paintEvent(QPaintEvent *)
{
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);
    path.addRect(10, 10, this->width()-20, this->height()-20);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.fillPath(path, QBrush(Qt::white));

    QColor color(200, 200, 200, 50);

    //在透明背景的外部10px矩形框绘制由半透明浅黑色渐变至白色的阴影
    for(int i=0; i<10; i++)
    {
        QPainterPath path;
        path.setFillRule(Qt::WindingFill);
        path.addRect(10-i, 10-i, this->width()-(10-i)*2, this->height()-(10-i)*2);
        color.setAlpha(150 - qSqrt(i)*50);
        painter.setPen(color);
        painter.drawPath(path);
    }
}
