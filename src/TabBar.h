#ifndef TABBAR_H
#define TABBAR_H

#include <QWidget>
#include <QHBoxLayout>
#include <QPalette>
#include <QPushButton>
#include <QDebug>

class TabBar : public QWidget
{
    Q_OBJECT
public:
    explicit TabBar(QWidget *parent = 0);

    QPushButton *btnHome;
    QPushButton *btnNotice;
    QPushButton *btnStatistics;
    QPushButton *btnInquiry;
    QPushButton *btnAbout;


private:
    void initLayout();
};

#endif // TABBAR_H
