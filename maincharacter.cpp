#include "maincharacter.h"

//构造 绘图
MainCharacter::MainCharacter(QWidget *parent) : QLabel(parent) {
    isImage = 0;
    QTimer *timerOfLinny = new QTimer(this);
    this->setFixedSize(72, 72);

    timerOfLinny->start(600);
    connect(timerOfLinny, &QTimer::timeout, this, [=]() {
        updateImage();
    });
}

void MainCharacter::updateImage() {
    isImage++;
    // 重新绘制控件
    update();
}

void MainCharacter::paintEvent(QPaintEvent *) {
    QPainter painterOfCharacter(this);
    QPixmap pixOfCharacter;
    int t = isImage % 7 + 2;
    QString mess = QString(":/linny/%1%2.png").arg(0).arg(t);
    pixOfCharacter.load(mess);

    //图片放缩
    pixOfCharacter = pixOfCharacter.scaled(72, 72, Qt::KeepAspectRatio);

    // 在绘图设备上绘制缩放后的图片
    painterOfCharacter.drawPixmap(0, 0, pixOfCharacter);
}
