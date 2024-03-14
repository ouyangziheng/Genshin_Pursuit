#ifndef SYFS_H
#define SYFS_H

#include <QKeyEvent>
#include <QMainWindow>
#include <QPainter>
#include <QTimer>
#include <QWidget>
#include <QtMath>
#include <cmath>

class syfs : public QWidget {
    Q_OBJECT
public:
    int image;
    int lives = 5;
    qreal speed = 2;// 移动速度
    void updateImage();
    void paintEvent(QPaintEvent *);
    void updatePosition(int linnyX, int linnyY);
    explicit syfs(QWidget *parent = nullptr);
    void skill();
signals:
};

#endif// SYFS_H
