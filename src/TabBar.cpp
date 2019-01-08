#include "TabBar.h"

TabBar::TabBar(QWidget *parent)
    : QWidget(parent)
{
    resize(652,64);

    //设置背景
    QPalette bgPalette;
    bgPalette.setColor(QPalette::Background, QColor(255,255,255));
    this->setPalette(bgPalette);
    this->setAutoFillBackground(true);

    initLayout();
}

/**
 * @brief TabBar::initLayout 初始化布局
 */
void TabBar::initLayout()
{
    //按钮控件
    QFont ft;
    ft.setPixelSize(16);
    ft.setFamily("冬青黑体简体中文 W3");

    btnHome = new QPushButton(this);
    btnHome->setStyleSheet(
                "QPushButton{border: none;}"
                "QPushButton:hover{background:white;color:#55C3EF; }"
                "QPushButton:pressed{background:white;color:#4682B4; }"
                );
    btnHome->setFont(ft);
    btnHome->setText("首页");
    btnHome->setFlat(true);
    btnHome->setGeometry(16,0,96,64);
    btnHome->setFocus();
    btnHome->setDefault(true);

    btnNotice = new QPushButton(this);
    btnNotice->setStyleSheet(
                "QPushButton{border: none;}"
                "QPushButton:hover{background:white;color:#55C3EF; }"
                "QPushButton:pressed{background:white;color:#4682B4; }"
                );
    btnNotice->setFont(ft);
    btnNotice->setText("公告");
    btnNotice->setFlat(true);
    btnNotice->setGeometry(112,0,96,64);
    btnNotice->setFocus();
    btnNotice->setDefault(true);

    btnStatistics = new QPushButton(this);
    btnStatistics->setStyleSheet(
                "QPushButton{border: none;}"
                "QPushButton:hover{background:white;color:#55C3EF; }"
                "QPushButton:pressed{background:white;color:#4682B4; }"
                );
    btnStatistics->setFont(ft);
    btnStatistics->setText("统计");
    btnStatistics->setFlat(true);
    btnStatistics->setGeometry(208,0,96,64);
    btnStatistics->setFocus();
    btnStatistics->setDefault(true);

    btnInquiry = new QPushButton(this);
    btnInquiry->setStyleSheet(
                "QPushButton{border: none;}"
                "QPushButton:hover{background:white;color:#55C3EF; }"
                "QPushButton:pressed{background:white;color:#4682B4; }"
                );
    btnInquiry->setFont(ft);
    btnInquiry->setText("查询");
    btnInquiry->setFlat(true);
    btnInquiry->setGeometry(304,0,96,64);
    btnInquiry->setFocus();
    btnInquiry->setDefault(true);

    btnAbout = new QPushButton(this);
    btnAbout->setFlat(true);
    btnAbout->setToolTip("关于");
    btnAbout->setStyleSheet("QPushButton{border-image: url(:images/btn_info.png);}"
                            "QPushButton:hover{border-image: url(:images/btn_info_hover.png);}"
                            "QPushButton:pressed{border-image: url(:images/btn_info.png);}");
    btnAbout->setGeometry(608,16,33,33);
    btnAbout->setFocus();
    btnAbout->setDefault(true);
}
