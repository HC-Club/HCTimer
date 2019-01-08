#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#define REG_RUN "HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run"

#include <QDialog>
#include <QApplication>
#include <QLabel>
#include <QMouseEvent>
#include <QPushButton>
#include <QCheckBox>
#include <QSettings>
#include <QPainter>
#include <QtMath>
#include <QFont>
#include <QMessageBox>
#include <QDebug>

class SettingDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SettingDialog(QDialog *parent = 0);

protected:
    void initLayout();    
    void setAutoBoot(bool _isAutoBoot);
    void setColorBtnGeometry(int _themeColor);

    QPoint beginDrag;
    bool bPressFlag;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *);

private:
    QPushButton *closeBtn;
    QLabel *settingTitle;
    QCheckBox *autoBoot;
    QCheckBox *startDesktopWidget;
    QLabel *themeTitle;
    QPushButton *blueBtn;
    QPushButton *greenBtn;
    QPushButton *orangeBtn;
    QPushButton *redBtn;
    bool isChangeSettings;
    bool isAutoBoot;
    bool isStartDesktopWidget;
    QSettings *settings;
    int themeColor;

public slots:
    void slotAutoBoot(bool b);
    void slotStartDesktopWidget(bool b);
    void slotBlueBtn();
    void slotGreenBtn();
    void slotOrangeBtn();
    void slotRedBtn();
    void slotCloseBtn();
};

#endif // SETTINGDIALOG_H
