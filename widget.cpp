#include "widget.h"
#include "./ui_widget.h"

#include <QString>
#include <QTime>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    // 界面
    ui->ipLineEdit->setText("192.168.1.171");
    ui->portLineEdit->setText("10001");

    // 信号与槽
    connect(ui->startBtn, &QPushButton::clicked, this, &Widget::onStartBtnClicked);
    connect(ui->stopBtn, &QPushButton::clicked, this, &Widget::onStopBtnClicked);

    connect(&udpSocket, &QUdpSocket::readyRead, this, &Widget::dataIn);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::onStartBtnClicked()
{
    QString ip = ui->ipLineEdit->text();
    int port = ui->portLineEdit->text().toInt();

    udpSocket.bind(QHostAddress(ip), port);

    file = new QFile(QTime::currentTime().toString("HHmmss"));
    file->open(QIODevice::WriteOnly);
}

void Widget::onStopBtnClicked()
{
    file->close();
    delete file;
}

void Widget::dataIn()
{
    QByteArray bytes;

    while (udpSocket.hasPendingDatagrams()) {
        bytes.resize(udpSocket.pendingDatagramSize());
        udpSocket.readDatagram(bytes.data(), bytes.size());
        file->write(bytes.data(), bytes.size());
        ui->statusLabel->setText(QString::number(bytes.size()));
    }
}
