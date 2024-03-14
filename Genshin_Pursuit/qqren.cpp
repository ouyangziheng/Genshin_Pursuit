#include "qqren.h"

//构造函数
qqren::qqren(QWidget *parent) : QLabel(parent) {
    isQQrenAlive = 1;
    this->setFixedSize(50, 50);
}

//装饰丘丘人
void qqren::paintEvent(QPaintEvent *) {
    QPainter painterOfCharacter(this);
    QPixmap pixOfCharacter;
    pixOfCharacter.load(":/monster/qqren.png");

    //图片放缩
    pixOfCharacter = pixOfCharacter.scaled(50, 50, Qt::KeepAspectRatio);

    // 在绘图设备上绘制缩放后的图片
    painterOfCharacter.drawPixmap(0, 0, pixOfCharacter);

    // 在绘图设备上绘制缩放后的图片
    painterOfCharacter.drawPixmap(0, 0, pixOfCharacter);
}

// 在 qqren 类中添加一个函数用于更新位置
void qqren::updatePosition(int linnyX, int linnyY) {
    // 计算 qqren 和 linny 之间的距离和方向
    qreal dx = linnyX - this->x();
    qreal dy = linnyY - this->y();
    qreal distance = sqrt(dx * dx + dy * dy);// 使用 sqrt() 函数来计算距离

    // 如果 qqren 已经接近 linny，停止移动
    if (distance < 5) {
        return;
    }

    // 计算 qqren 移动的速度和方向

    qreal angle = qAtan2(dy, dx);  // 计算角度
    qreal vx = speed * qCos(angle);// 计算 x 方向速度
    qreal vy = speed * qSin(angle);// 计算 y 方向速度

    // 更新 qqren 的位置
    this->move(this->x() + vx, this->y() + vy);
}
