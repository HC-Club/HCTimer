#ifndef DWSETTINGDIALOG_H
#define DWSETTINGDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QMouseEvent>
#include <QSettings>
#include <QPainter>
#include <QtMath>
#include <QFont>
#include <QMessageBox>
#include <QSlider>
#include <QCheckBox>
#include <QDebug>

class DWSettingDialog : public QDialog
{
    Q_OBJECT
public:
    explicit DWSettingDialog(QDialog *parent = 0);

protected:
    void initInterface();

    QPoint beginDrag;
    bool bPressFlag;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *);

private:
    QPushButton *closeBtn;

    QLabel *tomatoTimeLabel;
    QLabel *restTimeLabel;
    QLabel *longRestTimeLabel;
    QLabel *volumeLabel;

    QSlider *tomatoTimeSlider;
    QSlider *restTimeSlider;
    QSlider *longRestTimeSlider;
    QSlider *volumeSlider;

    QLabel *tomatoValueLabel;
    QLabel *restValueLabel;
    QLabel *longRestValueLabel;
    QLabel *volumeValueLabel;

    QLabel *soundEffectTitle;

    QCheckBox *startWorkSound;

    QSettings *settings;

    int tomatoTime;
    int restTime;
    int longRestTime;
    int volume;
    bool isStartWorkSound;

    bool isChangeSettings;

public slots:
    void slotCloseBtn();
    void slotSetTomatoTime(int value);
    void slotSetRestTime(int value);
    void slotSetLongRestTime(int value);
    void slotSetVolume(int value);
    void slotStartWorkSound(bool b);
};

#endif // DWSETTINGDIALOG_H
