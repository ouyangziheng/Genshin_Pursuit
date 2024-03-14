#ifndef ARROW_H
#define ARROW_H

#include <QtWidgets>

class Arrow : public QLabel {
    Q_OBJECT

public:
    int state = 0;// 0: 切换图片，1: 结束，2: 删除
    Arrow(const QPoint& initialPosition, QMainWindow* parent = nullptr);
    void paintEvent(QPaintEvent*);
    void setInitialPosition(const QPoint& position);
    void setTargetPosition(const QPoint& position);
    void shootArrow();
    void updateImage();
    void endTheArrow();

    int isFirstImage;
signals:
    void checkExplosionOfArrow();

private:
    QPoint initialPosition;
    QPoint targetPosition;
};

#endif// ARROW_H
