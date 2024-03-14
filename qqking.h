#ifndef QQKING_H
#define QQKING_H

#include <QLabel>
#include <QPainter>
#include <QtWidgets>

class qqking : public QLabel {
    Q_OBJECT
public:
    int lives = 5;
    qreal speed = 5;// 移动速度

    bool isQQkingAlive;
    explicit qqking(QWidget* parent = nullptr);
    void paintEvent(QPaintEvent*);
    void updatePosition(int linnyX, int linnyY);
    void useSkill();
    void setInitialPosition(const QPoint& position);
    void setTargetPosition(const QPoint& position);

private:
    QPoint initialPosition;
    QPoint targetPosition;

signals:
};

#endif// QQKING_H
