//qq王
#include "scene02.h"
extern int money, score, velocity;
extern int livesOfLinny, maxLives;
extern int waveOfMonster02;

//构造函数
Scene02::Scene02(QWidget *parent) : QMainWindow(parent), killNumber(0) {
    // 初始化界面和主角角色
    protectBirth = true;
    this->setFixedSize(1800, 1100);
    linny = new MainCharacter(this);
    linny->move(900, 550);
    quantityOfqqren = 0;

    //鼠标位置赋初值
    lastMousePosition = QPoint(0, 0);
    connect(this, &Scene02::leftMouseButtonHaveClicked, [=]() {
        this->attack();
    });

    //移动定时器
    movementTimer = new QTimer(this);
    connect(movementTimer, &QTimer::timeout, this, &Scene02::movePlayer);
    movementTimer->setInterval(10);// 设置定时器间隔（毫秒）

    connect(this, &Scene02::stopMove, [=]() {
        movementTimer->stop();
    });
    connect(this, &Scene02::startMove, [=]() {
        movementTimer->start();
    });
    connect(this, &Scene02::startMove, [=]() {
        QTimer::singleShot(3000, [=]() {
            protectBirth = false;
        });
    });
}

//创造怪兽
void Scene02::createMoster() {
    this->killNumber = 0;
    this->sumQQren = waveOfMonster02 * 5 + 8 + waveOfMonster02 * waveOfMonster02 * (0.5);
    this->sumQQking = waveOfMonster02 + 1 + waveOfMonster02 * waveOfMonster02 * (0.1);
    qDebug() << sumQQking << sumQQren;
    this->quantityOfqqren = 0;
    this->quantityOfqqking = 0;

    QTimer *Birthofqqren = new QTimer(this);
    Birthofqqren->start(1000);

    QTimer *Birthofqqking = new QTimer(this);
    Birthofqqking->start(3000);

    //丘丘人行为
    connect(Birthofqqren, &QTimer::timeout, [=]() {
        if (quantityOfqqren <= sumQQren) {
            quantityOfqqren += 1;

            // 创建 qqren 对象并设置随机位置
            qqren *smallqqren = new qqren(this);
            QTimer *timer_updateThePositionOfLinny = new QTimer(this);
            qqrenObjects.push_back(smallqqren);
            smallqqren->speed = 5 + (0.5) * waveOfMonster02;
            connect(this, &Scene02::stopMove, [=]() {
                timer_updateThePositionOfLinny->stop();
            });

            connect(this, &Scene02::startMove, [=]() {
                QTimer::singleShot(2000, [&]() {
                    timer_updateThePositionOfLinny->start(50);
                });
            });

            int x = QRandomGenerator::global()->bounded(0, 1600);// 生成随机 x 坐标
            int y = QRandomGenerator::global()->bounded(0, 900); // 生成随机 y 坐标
            //确保不会1触碰就死
            while (abs(x - linny->x()) < 120 && abs(y - linny->y()) < 120) {
                x = QRandomGenerator::global()->bounded(0, 1600);
                y = QRandomGenerator::global()->bounded(0, 900);
            }

            // 更新丘丘人位置
            smallqqren->move(x, y);
            smallqqren->show();

            // 更新林尼位置
            timer_updateThePositionOfLinny->start(50);
            connect(timer_updateThePositionOfLinny, &QTimer::timeout, [=]() {
                smallqqren->updatePosition(linny->x(), linny->y());
                // 检查丘丘人和林尼之间的碰撞
                QRect qqrenRect = smallqqren->geometry();
                QRect linnyRect = linny->geometry();
                if (qqrenRect.intersects(linnyRect) && protectBirth == false) {
                    // 发生碰撞，处理逻辑
                    for (int i = 0; i < qqrenObjects.size(); i++) {
                        qqrenObjects[i]->setFixedSize(0, 0);
                    }
                    qqrenObjects.clear();
                    for (int i = 0; i < qqkingObjects.size(); i++) {
                        qqkingObjects[i]->setFixedSize(0, 0);
                    }
                    qqkingObjects.clear();

                    livesOfLinny--;
                    qDebug() << "lives" << livesOfLinny;
                    emit defeat();
                    protectBirth = true;
                }
            });
        }
    });

    //丘丘王行为
    connect(Birthofqqking, &QTimer::timeout, [=]() {
        if (quantityOfqqking <= sumQQking) {
            quantityOfqqking += 1;

            // 创建 qqKING 对象并设置随机位置
            qqking *bigqqren = new qqking(this);
            bigqqren->lives = 3 * waveOfMonster02 + 18 + waveOfMonster02 * waveOfMonster02;
            QTimer *timer_updateThePositionOfLinny = new QTimer(this);
            qqkingObjects.push_back(bigqqren);
            bigqqren->speed = 4 + 0.5 * waveOfMonster02;

            //丘丘人使用技能
            //技能间隔
            QTimer *waitTime = new QTimer(this);
            int temp = 20000 / (0.5 * waveOfMonster02 * waveOfMonster02 + 2 * waveOfMonster02 + 5);
            waitTime->start(temp);

            connect(waitTime, &QTimer::timeout, [=]() mutable {
                bigqqren->setInitialPosition(QPoint(bigqqren->x(), bigqqren->y()));
                int xTar = linny->x() - bigqqren->x();
                int yTar = linny->y() - bigqqren->y();
                xTar = bigqqren->x() + xTar * (0.8 - 1 / (3 + 2 * waveOfMonster02 + waveOfMonster02 * waveOfMonster02));
                yTar = bigqqren->y() + yTar * (0.8 - 1 / (3 + 2 * waveOfMonster02 + waveOfMonster02 * waveOfMonster02));

                bigqqren->setTargetPosition(QPoint(xTar, yTar));
                bigqqren->useSkill();
            });

            connect(this, &Scene02::stopMove, [=]() {
                timer_updateThePositionOfLinny->stop();
            });

            connect(this, &Scene02::startMove, [=]() {
                QTimer::singleShot(2000, [&]() {
                    timer_updateThePositionOfLinny->start(50);
                });
            });

            int x = QRandomGenerator::global()->bounded(0, 1600);// 生成随机 x 坐标
            int y = QRandomGenerator::global()->bounded(0, 900); // 生成随机 y 坐标

            //确保不会1触碰就死
            while (abs(x - linny->x()) < 250 && abs(y - linny->y()) < 250) {
                x = QRandomGenerator::global()->bounded(0, 1600);
                y = QRandomGenerator::global()->bounded(0, 900);
            }

            // 更新丘丘人位置
            bigqqren->move(x, y);
            bigqqren->show();

            // 更新林尼位置
            timer_updateThePositionOfLinny->start(50);
            connect(timer_updateThePositionOfLinny, &QTimer::timeout, [=]() {
                bigqqren->updatePosition(linny->x(), linny->y());
                // 检查丘丘王和林尼之间的碰撞
                QRect qqrenRect = bigqqren->geometry();
                QRect linnyRect = linny->geometry();

                if (qqrenRect.intersects(linnyRect) && protectBirth == false) {
                    // 发生碰撞，处理逻辑
                    for (int i = 0; i < qqrenObjects.size(); i++) {
                        qqrenObjects[i]->setFixedSize(0, 0);
                    }
                    qqrenObjects.clear();
                    for (int i = 0; i < qqkingObjects.size(); i++) {
                        qqkingObjects[i]->setFixedSize(0, 0);
                    }
                    qqkingObjects.clear();
                    livesOfLinny--;
                    emit defeat();
                    protectBirth = true;
                }
            });
        }
    });
}

// 角色攻击
void Scene02::attack() {
    //创建箭矢
    QPoint pointOfCharacter(linny->x(), linny->y());
    Arrow *arr = new Arrow(pointOfCharacter, this);
    arr->show();
    arr->setTargetPosition(QPoint(lastMousePosition.x(), lastMousePosition.y()));
    connect(arr, &Arrow::checkExplosionOfArrow, [=]() {
        checkCollision(arr);
    });
}

//处理互动事件

//根据按键状态移动角色
void Scene02::movePlayer() {
    int step = 0.5 * velocity;// 移动步长  根据需要调整

    if (moveUp) {
        // 向上移动
        linny->move(linny->x(), linny->y() - step);
    }
    if (moveDown) {
        // 向下移动
        linny->move(linny->x(), linny->y() + step);
    }
    if (moveLeft) {
        // 向左移动
        linny->move(linny->x() - step, linny->y());
    }
    if (moveRight) {
        // 向右移动
        linny->move(linny->x() + step, linny->y());
    }
}

// 鼠标事件
void Scene02::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        lastMousePosition = event->pos();
        leftMouseButtonHaveClicked();
    }
}

// 按键按下事件
void Scene02::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_Up:
        moveUp = true;
        break;
    case Qt::Key_Down:
        moveDown = true;
        break;
    case Qt::Key_Left:
        moveLeft = true;
        break;
    case Qt::Key_Right:
        moveRight = true;
        break;
    default:
        QMainWindow::keyPressEvent(event);
        return;
    }

    // 启动定时器
    movementTimer->start();
}

// 按键释放事件
void Scene02::keyReleaseEvent(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_Up:
        moveUp = false;
        break;
    case Qt::Key_Down:
        moveDown = false;
        break;
    case Qt::Key_Left:
        moveLeft = false;
        break;
    case Qt::Key_Right:
        moveRight = false;
        break;
    default:
        QMainWindow::keyReleaseEvent(event);
        return;
    }

    // 如果所有方向键都释放了，停止定时器
    if (!moveUp && !moveDown && !moveLeft && !moveRight) {
        movementTimer->stop();
    }
}

//检查碰撞
void Scene02::checkCollision(Arrow *arr) {
    // 获取箭的位置和大小
    int arrowX = arr->x();
    int arrowY = arr->y();
    int arrowWidth = arr->width();
    int arrowHeight = arr->height();

    // 构造箭的边界框
    QRect arrowRect(arrowX, arrowY, arrowWidth, arrowHeight);

    // 存储需要删除的丘丘人对象的指针
    QVector<qqren *> qqrenToDelete;

    // 遍历所有丘丘人
    for (int i = 0; i < qqrenObjects.size(); i++) {
        // 获取丘丘人的边界框
        QRect qqrenRect = (qqrenObjects[i])->geometry();

        // 检查丘丘人和箭的边界框是否相交
        if (qqrenRect.intersects(arrowRect)) {
            // 发生碰撞，将丘丘人对象的指针添加到需要删除的容器中
            qqrenObjects[i]->hide();
            qqrenObjects[i]->setFixedSize(0, 0);
            this->killNumber++;
            if (killNumber == sumQQren + sumQQking) {
                QTimer::singleShot(3500, [=]() {
                    for (int i = 0; i < qqrenObjects.size(); i++) {
                        qqrenObjects[i]->setFixedSize(0, 0);
                    }
                    qqrenObjects.clear();
                    for (int i = 0; i < qqkingObjects.size(); i++) {
                        qqkingObjects[i]->setFixedSize(0, 0);
                    }
                    qqkingObjects.clear();
                    emit haveKilledAllqqren();
                    money += (sumQQking + 1) * 5;
                    score += (sumQQking + 1) * 5;
                });
            }
        }
    }
    // 存储需要删除的丘丘王对象的指针
    QVector<qqking *> qqkingToDelete;

    // 遍历所有丘丘王
    for (int i = 0; i < qqkingObjects.size(); i++) {
        // 获取丘丘王的边界框
        QRect qqkingRect = (qqkingObjects[i])->geometry();

        // 检查丘丘王和箭的边界框是否相交
        if (qqkingRect.intersects(arrowRect)) {
            // 发生碰撞，将丘丘王对象的指针添加到需要更改的容器中
            if (qqkingObjects[i]->lives <= 0) {
                qqkingObjects[i]->hide();
                qqkingObjects[i]->setFixedSize(0, 0);
                this->killNumber++;

                if (killNumber == sumQQren + sumQQking) {
                    for (int i = 0; i < qqrenObjects.size(); i++) {
                        qqrenObjects[i]->setFixedSize(0, 0);
                    }
                    qqrenObjects.clear();
                    for (int i = 0; i < qqkingObjects.size(); i++) {
                        qqkingObjects[i]->setFixedSize(0, 0);
                    }
                    qqkingObjects.clear();
                    QTimer::singleShot(3500, [=]() {
                        emit haveKilledAllqqren();
                        money += (sumQQking * 5 + 1);
                        score += (sumQQking * 5 + 1);
                    });
                }
            } else {
                qqkingObjects[i]->lives -= 1;
                qDebug() << qqkingObjects[i]->lives;
            }
        }
    }
    if (arr->state == 3) arr->setFixedSize(0, 0);
}

void Scene02::resetKeyStates() {
    moveUp = false;
    moveDown = false;
    moveLeft = false;
    moveRight = false;
}
