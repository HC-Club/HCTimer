#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QDialog>
#include <QMouseEvent>
#include <QPushButton>
#include <QLabel>
#include <QDesktopServices>
#include <QtMath>
#include <QPainter>
#include "define.h"

class AboutDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AboutDialog(QDialog *parent = 0);

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
    QLabel *applicationLogo;
    QLabel *applicationName;
    QLabel *applicationVersion;
    QLabel *applicationContacts;

public slots:
    void openHCLabWebUrl(QString url);
};

#endif // ABOUTDIALOG_H
