#ifndef WIDGET_H
#define WIDGET_H

#include <QFile>
#include <QWidget>
#include <QUdpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;

    QUdpSocket udpSocket;

    QFile *file;

private slots:
    void onStartBtnClicked();
    void onStopBtnClicked();
    void dataIn();
};
#endif // WIDGET_H
