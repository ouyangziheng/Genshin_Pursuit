#ifndef QQREN_H
#define QQREN_H

#include <QKeyEvent>
#include <QLabel>
#include <QMainWindow>
#include <QPainter>
#include <QRandomGenerator>
#include <QtMath>
#include <cmath>

class qqren : public QLabel {
    Q_OBJECT
public:
    bool kindOfqq = true;
    qreal speed = 5;// 移动速度
    bool lives;
    explicit qqren(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);
    void updatePosition(int linnyX, int linnyY);
signals:
};

#endif// QQREN_H
