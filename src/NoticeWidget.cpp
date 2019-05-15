#include "NoticeWidget.h"

NoticeWidget::NoticeWidget(QWidget *parent) : QWidget(parent)
{
    dateBtnStyleSheetID = 0;
    initLayout();
    resize(652,300);
}

void NoticeWidget::initLayout()
{

    QFont ft;
    ft.setPixelSize(16);
    ft.setFamily("冬青黑体简体中文 W3");
    ft.setBold(false);

    QPalette pa;
    pa.setColor(QPalette::WindowText,QColor(102,102,102));

    noticeIDLabel_1 = new QLabel(this);
    noticeIDLabel_1->setGeometry(112,64,1,1);

    createTimeLabel_1 = new QLabel(this);
    createTimeLabel_1->setGeometry(112,64,1,1);

    titleLabel_1 = new QLabel(this);
    titleLabel_1->setFont(ft);
    titleLabel_1->setAlignment(Qt::AlignHCenter);
    titleLabel_1->setStyleSheet("background-color:none;color:#B8B8B8;border:none;");
    titleLabel_1->setGeometry(48,0,176,24);

    ft.setPixelSize(45);
    ft.setBold(true);
    dateBtn_1=new QPushButton(this);
    dateBtn_1->setFont(ft);
    dateBtn_1->setToolTip("公告详情等");
    dateBtn_1->setStyleSheet("background-color:#6B8DFD;color:white;border:none;");
    dateBtn_1->setGeometry(48,24,176,112);
    connect(dateBtn_1, SIGNAL(clicked()),
                this, SLOT(slotDateBtn_1()));

    ft.setPixelSize(16);
    ft.setBold(false);
    text_1 = new QTextEdit(this);
    text_1->setReadOnly(true);
    text_1->setFont(ft);
    text_1->setAlignment(Qt::AlignCenter);
    text_1->setStyleSheet("QTextEdit{background-color:#FFF;color:black;border:none}"
                               "QScrollBar{background:transparent; height:10px; }");
    text_1->setGeometry(48,136,176,144);

    ft.setPixelSize(16);

    noticeIDLabel_2 = new QLabel(this);
    noticeIDLabel_2->setGeometry(112,64,1,1);

    createTimeLabel_2 = new QLabel(this);
    createTimeLabel_2->setGeometry(112,64,1,1);

    titleLabel_2 = new QLabel(this);
    titleLabel_2->setFont(ft);
    titleLabel_2->setAlignment(Qt::AlignHCenter);
    titleLabel_2->setStyleSheet("background-color:none;color:#B8B8B8;border:none;");
    titleLabel_2->setGeometry(240,0,176,24);

    ft.setPixelSize(45);
    ft.setBold(true);
    dateBtn_2 = new QPushButton(this);
    dateBtn_2->setFont(ft);
    dateBtn_2->setToolTip("公告详情等");
    dateBtn_2->setStyleSheet("background-color:#4FCFFF;color:white;border:none;");
    dateBtn_2->setGeometry(240,24,176,112);
    connect(dateBtn_2, SIGNAL(clicked()),
                this, SLOT(slotDateBtn_2()));

    ft.setPixelSize(16);
    ft.setBold(false);
    text_2=new QTextEdit(this);
    text_2->setReadOnly(true);
    text_2->setFont(ft);
    text_2->setAlignment(Qt::AlignCenter);
    text_2->setStyleSheet("QTextEdit{background-color:#FFF;color:black;border:none}"
                               "QScrollBar{background:transparent; height:10px; }");
    text_2->setGeometry(240,136,176,144);

    ft.setPixelSize(16);

    noticeIDLabel_3 = new QLabel(this);
    noticeIDLabel_3->setGeometry(112,64,1,1);

    createTimeLabel_3 = new QLabel(this);
    createTimeLabel_3->setGeometry(112,64,1,1);

    titleLabel_3 = new QLabel(this);
    titleLabel_3->setFont(ft);
    titleLabel_3->setAlignment(Qt::AlignHCenter);
    titleLabel_3->setStyleSheet("background-color:none;color:#B8B8B8;border:none;");
    titleLabel_3->setGeometry(432,0,176,24);

    ft.setPixelSize(45);
    ft.setBold(true);
    dateBtn_3 = new QPushButton(this);
    dateBtn_3->setFont(ft);
    dateBtn_3->setToolTip("公告详情等");
    dateBtn_3->setStyleSheet("background-color:#8AE5C1;color:white;border:none;");
    dateBtn_3->setGeometry(432,24,176,112);
    connect(dateBtn_3, SIGNAL(clicked()),
                this, SLOT(slotDateBtn_3()));

    ft.setPixelSize(16);
    ft.setBold(false);
    text_3=new QTextEdit(this);
    text_3->setReadOnly(true);
    text_3->setFont(ft);
    text_3->setAlignment(Qt::AlignCenter);
    text_3->setStyleSheet("QTextEdit{background-color:#FFF;color:black;border:none}"
                               "QScrollBar{background:transparent; height:10px; }");
    text_3->setGeometry(432,136,176,144);

}

void NoticeWidget::showCurrentNotice()
{
    QList<Notice> temp;
    int length = temp.length();
    if(length-- > 0){
        noticeIDLabel_1->setText(temp.at(0).id);
        createTimeLabel_1->setText(temp.at(0).createTime);
        titleLabel_1->setText(temp.at(0).date);
        dateBtn_1->setText(temp.at(0).date.mid(8,2));
        dateBtn_1->setStyleSheet("background-color:#6B8DFD;color:white;border:none;");
        text_1->setText(temp.at(0).content);
    }
    else{
        noticeIDLabel_1->setText("");
        createTimeLabel_1->setText("");
        titleLabel_1->setText("");
        dateBtn_1->setText("");
        dateBtn_1->setStyleSheet("background-color:#6B8DFD;color:white;border:none;");
        text_1->setText("");
    }

    if(length-- > 0){
        noticeIDLabel_2->setText(temp.at(1).id);
        createTimeLabel_2->setText(temp.at(1).createTime);
        titleLabel_2->setText(temp.at(1).date);
        dateBtn_2->setText(temp.at(1).date.mid(8,2));
        dateBtn_2->setStyleSheet("background-color:#4FCFFF;color:white;border:none;");
        text_2->setText(temp.at(1).content);
    }
    else{
        noticeIDLabel_2->setText("");
        createTimeLabel_2->setText("");
        titleLabel_2->setText("");
        dateBtn_2->setText("");
        dateBtn_2->setStyleSheet("background-color:#4FCFFF;color:white;border:none;");
        text_2->setText("");
    }

    if(length-- > 0){
        noticeIDLabel_3->setText(temp.at(2).id);
        createTimeLabel_3->setText(temp.at(2).createTime);
        titleLabel_3->setText(temp.at(2).date);
        dateBtn_3->setText(temp.at(2).date.mid(8,2));
        dateBtn_3->setStyleSheet("background-color:#8AE5C1;color:white;border:none;");
        text_3->setText(temp.at(2).content);
    }
    else{
        noticeIDLabel_3->setText("");
        createTimeLabel_3->setText("");
        titleLabel_3->setText("");
        dateBtn_3->setText("");
        dateBtn_3->setStyleSheet("background-color:#8AE5C1;color:white;border:none;");
        text_3->setText("");
    }
    if(dateBtnStyleSheetID>3)
        dateBtnStyleSheetID=0;
    changeDateBtnStyleSheet(dateBtnStyleSheetID++);
}

void NoticeWidget::showNewNotice()
{
    QList<Notice> temp;
    int length = temp.length();
    if(length-- > 0){
        noticeIDLabel_1->setText(temp.at(0).id);
        createTimeLabel_1->setText(temp.at(0).createTime);
        titleLabel_1->setText(temp.at(0).date);
        dateBtn_1->setText(temp.at(0).date.mid(8,2));
        dateBtn_1->setStyleSheet("background-color:#6B8DFD;color:white;border:none;");
        text_1->setText(temp.at(0).content);
    }
    else{
        noticeIDLabel_1->setText("");
        createTimeLabel_1->setText("");
        titleLabel_1->setText("");
        dateBtn_1->setText("");
        dateBtn_1->setStyleSheet("background-color:#6B8DFD;color:white;border:none;");
        text_1->setText("");
    }

    if(length-- > 0){
        noticeIDLabel_2->setText(temp.at(1).id);
        createTimeLabel_2->setText(temp.at(1).createTime);
        titleLabel_2->setText(temp.at(1).date);
        dateBtn_2->setText(temp.at(1).date.mid(8,2));
        dateBtn_2->setStyleSheet("background-color:#4FCFFF;color:white;border:none;");
        text_2->setText(temp.at(1).content);
    }
    else{
        noticeIDLabel_2->setText("");
        createTimeLabel_2->setText("");
        titleLabel_2->setText("");
        dateBtn_2->setText("");
        dateBtn_2->setStyleSheet("background-color:#4FCFFF;color:white;border:none;");
        text_2->setText("");
    }

    if(length-- > 0){
        noticeIDLabel_3->setText(temp.at(2).id);
        createTimeLabel_3->setText(temp.at(2).createTime);
        titleLabel_3->setText(temp.at(2).date);
        dateBtn_3->setText(temp.at(2).date.mid(8,2));
        dateBtn_3->setStyleSheet("background-color:#8AE5C1;color:white;border:none;");
        text_3->setText(temp.at(2).content);
    }
    else{
        noticeIDLabel_3->setText("");
        createTimeLabel_3->setText("");
        titleLabel_3->setText("");
        dateBtn_3->setText("");
        dateBtn_3->setStyleSheet("background-color:#8AE5C1;color:white;border:none;");
        text_3->setText("");
    }
    if(dateBtnStyleSheetID>3)
        dateBtnStyleSheetID=0;
    changeDateBtnStyleSheet(dateBtnStyleSheetID++);
}

void NoticeWidget::showOldNotice()
{
    QList<Notice> temp;
    int length = temp.length();
    if(length-- > 0){
        noticeIDLabel_1->setText(temp.at(0).id);
        createTimeLabel_1->setText(temp.at(0).createTime);
        titleLabel_1->setText(temp.at(0).date);
        dateBtn_1->setText(temp.at(0).date.mid(8,2));
        dateBtn_1->setStyleSheet("background-color:#6B8DFD;color:white;border:none;");
        text_1->setText(temp.at(0).content);
    }
    else{
        noticeIDLabel_1->setText("");
        createTimeLabel_1->setText("");
        titleLabel_1->setText("");
        dateBtn_1->setText("");
        dateBtn_1->setStyleSheet("background-color:#6B8DFD;color:white;border:none;");
        text_1->setText("");
    }

    if(length-- > 0){
        noticeIDLabel_2->setText(temp.at(1).id);
        createTimeLabel_2->setText(temp.at(1).createTime);
        titleLabel_2->setText(temp.at(1).date);
        dateBtn_2->setText(temp.at(1).date.mid(8,2));
        dateBtn_2->setStyleSheet("background-color:#4FCFFF;color:white;border:none;");
        text_2->setText(temp.at(1).content);
    }
    else{
        noticeIDLabel_2->setText("");
        createTimeLabel_2->setText("");
        titleLabel_2->setText("");
        dateBtn_2->setText("");
        dateBtn_2->setStyleSheet("background-color:#4FCFFF;color:white;border:none;");
        text_2->setText("");
    }

    if(length-- > 0){
        noticeIDLabel_3->setText(temp.at(2).id);
        createTimeLabel_3->setText(temp.at(2).createTime);
        titleLabel_3->setText(temp.at(2).date);
        dateBtn_3->setText(temp.at(2).date.mid(8,2));
        dateBtn_3->setStyleSheet("background-color:#8AE5C1;color:white;border:none;");
        text_3->setText(temp.at(2).content);
    }
    else{
        noticeIDLabel_3->setText("");
        createTimeLabel_3->setText("");
        titleLabel_3->setText("");
        dateBtn_3->setText("");
        dateBtn_3->setStyleSheet("background-color:#8AE5C1;color:white;border:none;");
        text_3->setText("");
    }
    if(dateBtnStyleSheetID>3)
        dateBtnStyleSheetID=0;
    changeDateBtnStyleSheet(dateBtnStyleSheetID++);
}

void NoticeWidget::changeDateBtnStyleSheet(int i)
{
    switch(i)
    {
        case 0:
            dateBtn_1->setStyleSheet("background-color:#6B8DFD;color:white;border:none;");
            dateBtn_2->setStyleSheet("background-color:#4FCFFF;color:white;border:none;");
            dateBtn_3->setStyleSheet("background-color:#8AE5C1;color:white;border:none;");
            break;

        case 1:
            dateBtn_1->setStyleSheet("background-color:#BB75FE;color:white;border:none;");
            dateBtn_2->setStyleSheet("background-color:#F7AA60;color:white;border:none;");
            dateBtn_3->setStyleSheet("background-color:#EEFF92;color:white;border:none;");
            break;

        case 2:
            dateBtn_1->setStyleSheet("background-color:#F67377;color:white;border:none;");
            dateBtn_2->setStyleSheet("background-color:#FFB6C1;color:white;border:none;");
            dateBtn_3->setStyleSheet("background-color:#FFDAB9;color:white;border:none;");
            break;
    }
}

void NoticeWidget::slotDateBtn_1()
{
    NoticeDialog noticeDialog;
    if(!titleLabel_1->text().isEmpty())
        noticeDialog.date->setText(titleLabel_1->text());
    if(!text_1->toPlainText().isEmpty())
        noticeDialog.content->setText(text_1->toPlainText());
    if(!createTimeLabel_1->text().isEmpty())
        noticeDialog.creatTime->setText(createTimeLabel_1->text());
    if(!noticeIDLabel_1->text().isEmpty())
        noticeDialog.noticeID->setText(noticeIDLabel_1->text());
    noticeDialog.exec();
}

void NoticeWidget::slotDateBtn_2()
{
    NoticeDialog noticeDialog;
    if(!titleLabel_2->text().isEmpty())
        noticeDialog.date->setText(titleLabel_2->text());
    if(!text_2->toPlainText().isEmpty())
        noticeDialog.content->setText(text_2->toPlainText());
    if(!createTimeLabel_2->text().isEmpty())
        noticeDialog.creatTime->setText(createTimeLabel_2->text());
    if(!noticeIDLabel_2->text().isEmpty())
        noticeDialog.noticeID->setText(noticeIDLabel_2->text());
    noticeDialog.exec();
}

void NoticeWidget::slotDateBtn_3()
{
    NoticeDialog noticeDialog;
    if(!titleLabel_3->text().isEmpty())
        noticeDialog.date->setText(titleLabel_3->text());
    if(!text_3->toPlainText().isEmpty())
        noticeDialog.content->setText(text_3->toPlainText());
    if(!createTimeLabel_3->text().isEmpty())
        noticeDialog.creatTime->setText(createTimeLabel_3->text());
    if(!noticeIDLabel_3->text().isEmpty())
        noticeDialog.noticeID->setText(noticeIDLabel_3->text());
    noticeDialog.exec();
}
