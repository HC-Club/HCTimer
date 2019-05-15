/****************************************************************
**
** 文件名：
** 类信息：
** 创建者：
** 创建期日期：2016.05
** 包含类名列表：
** 版权声明：版权归 韶关学院 环创电脑工作室 所有
** 联系方式: http://www.hclab.cn
**
*******************************************************************/

#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QPalette>
#include <QPushButton>
#include <QDebug>
#include "user.h"

class TitleBar : public QWidget
{
    Q_OBJECT
public:
    explicit TitleBar(QWidget *parent = 0);
    QPushButton *avatarBtn;
    QLabel *avatarLabel;
    QImage *avatarImage;
    QLabel *nameLable;
    QPushButton *btnMinimize;
    QPushButton *btnClose;
    QPushButton *btnSettings;
    QPushButton *btnAddNotice;
    QPushButton *btnInquirySpecificTime;

    void setUser(const User &user);
    void setNoUser();

private:
    void initLayout();
};

#endif // TITLEBAR_H
