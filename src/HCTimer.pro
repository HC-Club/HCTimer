#-------------------------------------------------
#
# Project created by QtCreator 2016-05-01T21:42:48
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HCTimer
TEMPLATE = app


SOURCES += main.cpp\
        TimerWindow.cpp \
    DesktopWidget.cpp \
    TitleBar.cpp \
    TabBar.cpp \
    HomeWindow.cpp \
    UserData.cpp \
    Monitor.cpp \
    DOHelper.cpp \
    StatisticsWindow.cpp \
    NoticeWindow.cpp \
    InquiryWindow.cpp \
    AboutDialog.cpp \
    LoginDialog.cpp \
    UserInfoDialog.cpp \
    SettingDialog.cpp \
    RegistDialog.cpp \
    ModifyInfoDialog.cpp \
    AddNoticeDialog.cpp \
    NoticeDialog.cpp \
    NoticeWidget.cpp \
    DWSettingDialog.cpp \
    EditTaskDialog.cpp \
    SystemTrayIcon.cpp \
    InquirySpecificTimeDialog.cpp \
    Updater.cpp

HEADERS  += TimerWindow.h \
    DesktopWidget.h \
    TitleBar.h \
    TabBar.h \
    HomeWindow.h \
    UserData.h \
    Monitor.h \
    DOHelper.h \
    StatisticsWindow.h \
    NoticeWindow.h \
    InquiryWindow.h \
    AboutDialog.h \
    LoginDialog.h \
    RegistDialog.h \
    SettingDialog.h \
    UserInfoDialog.h \
    ModifyInfoDialog.h \
    AddNoticeDialog.h \
    NoticeDialog.h \
    NoticeWidget.h \
    DWSettingDialog.h \
    EditTaskDialog.h \
    define.h \
    SystemTrayIcon.h \
    InquirySpecificTimeDialog.h \
    Updater.h

RESOURCES += \
    HCTimerRS.qrc

RC_FILE = logo.rc
