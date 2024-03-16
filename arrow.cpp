#include "arrow.h"

Arrow::Arrow(const QPoint& initialPosition, QMainWindow* parent)
    : QLabel(parent), targetPosition(0, 0) {
    setAlignment(Qt::AlignCenter);
    setFixedSize(60, 60);
    isFirstImage = 1;
    setInitialPosition(initialPosition);

    QTimer* timerOfArrow = new QTimer(this);
    timerOfArrow->start(500);

    connect(timerOfArrow, &QTimer::timeout, this, [=]() {
        updateImage();

        switch (state) {
        case 0:
            timerOfArrow->start(150);
            emit checkExplosionOfArrow();
            state = 1;
            break;

        case 1:
            timerOfArrow->start(150);
            emit checkExplosionOfArrow();
            state = 2;
            break;

        case 2:
            timerOfArrow->start(75);
            emit checkExplosionOfArrow();
            state = 3;
            this->setFixedSize(0, 0);
            break;

        case 3:
            this->deleteLater();
            break;
        }
    });
}

//更新图片
void Arrow::updateImage() {
    isFirstImage++;
    // 重新绘制控件
    update();
}

void Arrow::paintEvent(QPaintEvent* event) {
    QLabel::paintEvent(event);

    QPainter painter(this);

    // 根据当前显示的图片加载相应的 QPixmap
    QPixmap pixOfArrow;
    if (isFirstImage == 1) {
        pixOfArrow = QPixmap(":/array/01.png");
        pixOfArrow = pixOfArrow.scaled(60, 60, Qt::KeepAspectRatio);
    } else if (isFirstImage == 2) {
        pixOfArrow = QPixmap(":/array/02.png");
        pixOfArrow = pixOfArrow.scaled(60, 60, Qt::KeepAspectRatio);
    } else if (isFirstImage == 3) {
        pixOfArrow = QPixmap(":/array/03.png");
        pixOfArrow = pixOfArrow.scaled(120, 120, Qt::KeepAspectRatio);
        this->setFixedSize(120, 120);
    }
    // 在箭头位置绘制箭头图片
    painter.drawPixmap(0, 0, pixOfArrow);
}

//设置位置
void Arrow::setInitialPosition(const QPoint& position) {
    initialPosition = position;
    move(initialPosition);
}

void Arrow::setTargetPosition(const QPoint& position) {
    targetPosition = position;
    shootArrow();
}

//箭的移动动画
void Arrow::shootArrow() {
    QPropertyAnimation* animation = new QPropertyAnimation(this, "geometry");

    animation->setDuration(300);
    animation->setStartValue(QRect(initialPosition, size()));
    animation->setEndValue(QRect(targetPosition, size()));
    animation->setEasingCurve(QEasingCurve::OutQuad);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}
