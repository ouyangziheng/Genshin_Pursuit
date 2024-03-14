#include "syfs.h"

syfs::syfs(QWidget *parent) : QWidget(parent) {
    this->setFixedSize(60, 60);
    image = 0;
    QTimer *timerOfSyfs = new QTimer(this);
    timerOfSyfs->start(600);// 每隔600毫秒更新一次图片
    connect(timerOfSyfs, &QTimer::timeout, this, [=]() {
        updateImage();
    });
}

void syfs::updateImage() {
    image++;
    // 重新绘制控件
    update();
}

void syfs::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    QPixmap pix;

    // 生成深渊法师的图片路径
    int t = image % 3 + 1;
    QString imagePath = QString(":/syfs/%1.jpeg").arg(t);
    pix.load(imagePath);

    // 图片放缩
    pix = pix.scaled(60, 60, Qt::KeepAspectRatio);

    // 在绘图设备上绘制缩放后的图片
    painter.drawPixmap(0, 0, pix);
}

void syfs::updatePosition(int linnyX, int linnyY) {
    // 计算 syfs 和 linny 之间的距离和方向
    qreal dx = linnyX - this->x();
    qreal dy = linnyY - this->y();
    qreal distance = sqrt(dx * dx + dy * dy);// 使用 sqrt() 函数来计算距离

    // 如果 syfs 已经接近 linny，停止移动
    if (distance < 5) {
        return;
    }

    // 计算 syfs 移动的速度和方向

    qreal angle = qAtan2(dy, dx);  // 计算角度
    qreal vx = speed * qCos(angle);// 计算 x 方向速度
    qreal vy = speed * qSin(angle);// 计算 y 方向速度

    // 更新 syfs 的位置
    this->move(this->x() + vx, this->y() + vy);
}
