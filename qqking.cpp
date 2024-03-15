#include "qqking.h"

#include <QKeyEvent>
#include <QMainWindow>
#include <QtMath>
#include <cmath>

// 构造函数
qqking::qqking(QWidget *parent) : QLabel(parent) {
    isQQkingAlive = true;
    this->setFixedSize(100, 100);
}

//设置位置
void qqking::setInitialPosition(const QPoint &position) {
    initialPosition = position;
    move(initialPosition);
}

void qqking::setTargetPosition(const QPoint &position) {
    targetPosition = position;
}

//qq王技能
void qqking::useSkill() {
    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");

    animation->setDuration(800);
    animation->setStartValue(QRect(initialPosition, size()));
    animation->setEndValue(QRect(targetPosition, size()));
    animation->setEasingCurve(QEasingCurve::OutQuad);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}

// 装饰丘丘人
void qqking::paintEvent(QPaintEvent *) {
    QPainter painterOfCharacter(this);
    QPixmap pixOfCharacter;
    pixOfCharacter.load(":/monster/qqking.png");

    // 图片放缩
    pixOfCharacter = pixOfCharacter.scaled(100, 100, Qt::KeepAspectRatio);

    // 在绘图设备上绘制缩放后的图片
    painterOfCharacter.drawPixmap(0, 0, pixOfCharacter);
}

// 在 qqking 类中添加一个函数用于更新位置
void qqking::updatePosition(int linnyX, int linnyY) {
    // 计算 qqking 和 linny 之间的距离和方向
    qreal dx = linnyX - this->x();
    qreal dy = linnyY - this->y();
    qreal distance = sqrt(dx * dx + dy * dy);// 使用 sqrt() 函数来计算距离

    // 如果 qqking 已经接近 linny，停止移动
    if (distance < 5) {
        return;
    }

    // 计算 qqking 移动的速度和方向
    qreal angle = qAtan2(dy, dx);  // 计算角度
    qreal vx = speed * qCos(angle);// 计算 x 方向速度
    qreal vy = speed * qSin(angle);// 计算 y 方向速度

    // 更新 qqking 的位置
    this->move(this->x() + vx, this->y() + vy);
}
