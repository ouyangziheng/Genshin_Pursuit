#ifndef SCENE02_H
#define SCENE02_H

#include <QCursor>
#include <QDebug>
#include <QKeyEvent>
#include <QMainWindow>
#include <QMouseEvent>
#include <QPalette>
#include <QRandomGenerator>
#include <QSignalMapper>
#include <QThread>
#include <QTimer>
#include <QVector>
#include <QWidget>
#include <QtWidgets>

#include "arrow.h"
#include "choosescene.h"
#include "maincharacter.h"
#include "qqking.h"
#include "qqren.h"

class Scene02 : public QMainWindow {
    Q_OBJECT
public:
    //变量
    bool protectBirth;
    int killNumber;
    int sumQQren;
    int sumQQking;
    int quantityOfqqren;
    int quantityOfqqking;
    QTimer *movementTimer;

    //函数
    Scene02(QWidget *parent = nullptr);

    MainCharacter *linny;
    QPushButton *nextButton;
    QVector<qqren *> qqrenObjects;
    QVector<qqking *> qqkingObjects;

    void mousePressEvent(QMouseEvent *event) override;
    void attack();
    void movePlayer();
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void checkCollision(Arrow *arr);
    void createMoster();
    void checkLives();
    void defeatScene();
    void resetKeyStates();

signals:
    void leftMouseButtonHaveClicked();
    void enableAttack();
    void returnChooseScene();
    //成功辣
    void haveKilledAllqqren();
    //林尼被沙拉
    void defeat();
    //控制移动
    void startMove();
    void stopMove();

private:
    QTimer *attackTimer;
    //鼠标位置
    QPoint lastMousePosition;
    //移动记录
    bool moveUp = false;
    bool moveDown = false;
    bool moveLeft = false;
    bool moveRight = false;
};

#endif// SCENE02_H
