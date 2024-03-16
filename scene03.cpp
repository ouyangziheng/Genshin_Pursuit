//qq王
#include "scene03.h"
extern int money, score, velocity, atk;
extern int livesOfLinny, maxLives;
extern int waveOfMonster03;

//构造函数
Scene03::Scene03(QWidget *parent) : QMainWindow(parent) {
    // 设置背景图片
    QString imagePath = ":/background/789.png";// 设置背景图片路径

    // 检查图片是否存在
    if (QFile::exists(imagePath)) {
        QPixmap backgroundImage(imagePath);// 加载背景图片
        if (!backgroundImage.isNull()) {
            backgroundImage = backgroundImage.scaled(this->size(), Qt::KeepAspectRatioByExpanding);// 调整图片尺寸以适应窗口大小
            QPalette palette;
            palette.setBrush(this->backgroundRole(), QBrush(backgroundImage));
            this->setPalette(palette);
        }
    }
    // 初始化界面和主角角色
    protectBirth = true;
    this->setFixedSize(1800, 1100);
    linny = new MainCharacter(this);
    linny->move(900, 550);
    quantityOfqqren = 0;

    //鼠标位置赋初值
    lastMousePosition = QPoint(0, 0);
    connect(this, &Scene03::leftMouseButtonHaveClicked, [=]() {
        this->attack();
    });

    //移动定时器
    movementTimer = new QTimer(this);
    connect(movementTimer, &QTimer::timeout, this, &Scene03::movePlayer);
    movementTimer->setInterval(10);// 设置定时器间隔（毫秒）

    connect(this, &Scene03::stopMove, [=]() {
        movementTimer->stop();
    });
    connect(this, &Scene03::startMove, [=]() {
        movementTimer->start();
    });
    connect(this, &Scene03::startMove, [=]() {
        QTimer::singleShot(3000, [=]() {
            protectBirth = false;
        });
    });
}

//创造怪兽
void Scene03::createMoster() {
    this->killNumber = 0;
    this->sumQQren = waveOfMonster03 * 4 + 6 + waveOfMonster03 * waveOfMonster03 * (0.3);
    this->sumQQking = 0.8 * waveOfMonster03 + 2 + waveOfMonster03 * waveOfMonster03 * (0.08);

    this->sumsyfs = 1 + waveOfMonster03 * +(0.05) * waveOfMonster03 * waveOfMonster03;

    this->quantityOfqqren = 0;
    this->quantityOfqqking = 0;
    this->quantityOfsyfs = 0;

    QTimer *Birthofqqren = new QTimer(this);
    Birthofqqren->start(1000);

    QTimer *Birthofqqking = new QTimer(this);
    Birthofqqking->start(3000);

    QTimer *Birthofsyfs = new QTimer(this);
    Birthofsyfs->start(5000);

    //丘丘人行为
    connect(Birthofqqren, &QTimer::timeout, [=]() {
        if (quantityOfqqren < sumQQren) {
            quantityOfqqren += 1;

            // 创建 qqren 对象并设置随机位置
            qqren *smallqqren = new qqren(this);
            int randomInt = QRandomGenerator::global()->bounded(101);
            randomInt = randomInt % 2;
            smallqqren->kindOfqq = randomInt;
            if (randomInt == 0)
                smallqqren->lives = 5 + 3 * waveOfMonster03;
            QTimer *timer_updateThePositionOfLinny = new QTimer(this);
            qqrenObjects.push_back(smallqqren);
            smallqqren->speed = 5 + (0.5) * waveOfMonster03;
            connect(this, &Scene03::stopMove, [=]() {
                timer_updateThePositionOfLinny->stop();
            });

            connect(this, &Scene03::startMove, [=]() {
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
                    for (int i = 0; i < syfsObjects.size(); i++) {
                        syfsObjects[i]->setFixedSize(0, 0);
                    }
                    syfsObjects.clear();

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
        qDebug() << "king";
        if (quantityOfqqking < sumQQking) {
            quantityOfqqking += 1;

            // 创建 qqKING 对象并设置随机位置
            qqking *bigqqren = new qqking(this);
            bigqqren->lives = 10 * (3 * waveOfMonster03 + 18 + waveOfMonster03 * waveOfMonster03);
            QTimer *timer_updateThePositionOfLinny = new QTimer(this);
            qqkingObjects.push_back(bigqqren);
            bigqqren->speed = 4 + 0.5 * waveOfMonster03;

            //技能间隔
            QTimer *waitTime = new QTimer(this);
            int temp = 20000 / (0.5 * waveOfMonster03 * waveOfMonster03 + 2 * waveOfMonster03 + 5);
            waitTime->start(temp);

            connect(waitTime, &QTimer::timeout, [=]() mutable {
                bigqqren->setInitialPosition(QPoint(bigqqren->x(), bigqqren->y()));
                int xTar = linny->x() - bigqqren->x();
                int yTar = linny->y() - bigqqren->y();
                xTar = bigqqren->x() + xTar * (0.8 - 1 / (3 + 2 * waveOfMonster03 + waveOfMonster03 * waveOfMonster03));
                yTar = bigqqren->y() + yTar * (0.8 - 1 / (3 + 2 * waveOfMonster03 + waveOfMonster03 * waveOfMonster03));

                bigqqren->setTargetPosition(QPoint(xTar, yTar));
                bigqqren->useSkill();
            });

            connect(this, &Scene03::stopMove, [=]() {
                timer_updateThePositionOfLinny->stop();
            });

            connect(this, &Scene03::startMove, [=]() {
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
                    for (int i = 0; i < syfsObjects.size(); i++) {
                        syfsObjects[i]->setFixedSize(0, 0);
                    }
                    syfsObjects.clear();
                    qqkingObjects.clear();
                    livesOfLinny--;
                    emit defeat();
                    protectBirth = true;
                }
            });
        }
    });

    //深渊法师行为
    connect(Birthofsyfs, &QTimer::timeout, [=]() {
        if (quantityOfsyfs < sumsyfs) {
            quantityOfsyfs += 1;

            // 创建 syfs 对象并设置随机位置
            syfs *fs = new syfs(this);
            fs->lives = 10 * (2 * waveOfMonster03 + 10 + waveOfMonster03 * waveOfMonster03);
            QTimer *timer_updateThePositionOfLinny = new QTimer(this);
            syfsObjects.push_back(fs);

            //技能间隔
            QTimer *waitTime = new QTimer(this);
            int temp = 20000 / (0.5 * waveOfMonster03 * waveOfMonster03 + 2 * waveOfMonster03 + 5);
            waitTime->start(temp);

            connect(waitTime, &QTimer::timeout, [=]() mutable {
                int x = QRandomGenerator::global()->bounded(0, 1600);// 生成随机 x 坐标
                int y = QRandomGenerator::global()->bounded(0, 900); // 生成随机 y 坐标

                //确保不会1触碰就死
                while (abs(x - linny->x()) < 250 && abs(y - linny->y()) < 250) {
                    x = QRandomGenerator::global()->bounded(0, 1600);
                    y = QRandomGenerator::global()->bounded(0, 900);
                }
                fs->move(x, y);

                //减速逻辑
            });
            QTimer *slowSkill = new QTimer(this);
            slowSkill->start(3000);
            connect(slowSkill, &QTimer::timeout, [=]() {
                if (fs->lives > 0) {
                    velocity = velocity - 2;
                    QTimer::singleShot(1000, [=]() mutable {
                        velocity = velocity + 2;
                    });
                }
            });

            connect(this, &Scene03::stopMove, [=]() {
                timer_updateThePositionOfLinny->stop();
            });

            connect(this, &Scene03::startMove, [=]() {
                QTimer::singleShot(2000, [=]() {
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

            fs->move(x, y);
            fs->show();

            // 更新林尼位置
            timer_updateThePositionOfLinny->start(50);
            connect(timer_updateThePositionOfLinny, &QTimer::timeout, [=]() {
                fs->updatePosition(linny->x(), linny->y());

                QRect qqrenRect = fs->geometry();
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
                    for (int i = 0; i < syfsObjects.size(); i++) {
                        syfsObjects[i]->setFixedSize(0, 0);
                    }
                    syfsObjects.clear();

                    livesOfLinny--;
                    emit defeat();
                    protectBirth = true;
                }
            });
        }
    });
}

// 角色攻击
void Scene03::attack() {
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
void Scene03::movePlayer() {
    int step = 0.5 * velocity;// 移动步长，根据需要调整

    if (moveUp && linny->y() - step >= 0) {
        // 向上移动，确保不超出上边界
        linny->move(linny->x(), linny->y() - step);
    }
    if (moveDown && linny->y() + linny->height() + step <= this->height()) {
        // 向下移动，确保不超出下边界
        linny->move(linny->x(), linny->y() + step);
    }
    if (moveLeft && linny->x() - step >= 0) {
        // 向左移动，确保不超出左边界
        linny->move(linny->x() - step, linny->y());
    }
    if (moveRight && linny->x() + linny->width() + step <= this->width()) {
        // 向右移动，确保不超出右边界
        linny->move(linny->x() + step, linny->y());
    }
}

// 鼠标事件
void Scene03::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        lastMousePosition = event->pos();
        leftMouseButtonHaveClicked();
    }
}

// 按键按下事件
void Scene03::keyPressEvent(QKeyEvent *event) {
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
void Scene03::keyReleaseEvent(QKeyEvent *event) {
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
void Scene03::checkCollision(Arrow *arr) {
    // 获取箭的位置和大小
    int arrowX = arr->x();
    int arrowY = arr->y();
    int arrowWidth = arr->width();
    int arrowHeight = arr->height();

    // 构造箭的边界框
    QRect arrowRect(arrowX, arrowY, arrowWidth, arrowHeight);

    // 存储需要删除的丘丘人对象的指针
    QVector<qqren *> qqrenToDelete;

    for (int i = 0; i < qqrenObjects.size(); i++) {
        // 获取丘丘人的边界框
        QRect qqrenRect = (qqrenObjects[i])->geometry();

        // 检查丘丘人和箭的边界框是否相交
        if (qqrenRect.intersects(arrowRect)) {
            // 发生碰撞，将丘丘人对象的指针添加到需要删除的容器中
            if (qqrenObjects[i]->lives - atk <= 0) {
                qqrenObjects[i]->hide();
                qqrenObjects[i]->setFixedSize(0, 0);
                this->killNumber++;
                money++;
                if (killNumber == sumQQren + sumQQking + sumsyfs) {
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
                        money += (sumQQking + 1) * 5 + sumQQren + 1;
                        score += (sumQQking + 1) * 5 + sumQQren + 1;
                    });
                }
            } else {
                qqrenObjects[i]->lives -= atk;
            }
        }
    }
    // 遍历所有丘丘王
    for (int i = 0; i < qqkingObjects.size(); i++) {
        // 获取丘丘王的边界框
        QRect qqkingRect = (qqkingObjects[i])->geometry();

        // 检查丘丘王和箭的边界框是否相交
        if (qqkingRect.intersects(arrowRect)) {
            // 发生碰撞，将丘丘王对象的指针添加到需要更改的容器中
            if (qqkingObjects[i]->lives - atk <= 0) {
                qqkingObjects[i]->hide();
                qqkingObjects[i]->setFixedSize(0, 0);
                this->killNumber++;
                money += 5;

                if (killNumber == sumQQren + sumQQking + sumsyfs) {
                    qqrenObjects.clear();

                    qqkingObjects.clear();

                    syfsObjects.clear();

                    QTimer::singleShot(3500, [=]() {
                        money += (sumsyfs + 1) * 20 + (sumQQking + 1) * 5 + sumQQren + 1;
                        score += (sumsyfs + 1) * 20 + (sumQQking + 1) * 5 + sumQQren + 1;
                        emit haveKilledAllqqren();
                    });
                }
            } else {
                qqkingObjects[i]->lives -= atk;
            }
        }
    }

    // 遍历所有深渊法师
    for (int i = 0; i < syfsObjects.size(); i++) {
        // 边界框
        QRect syfsRect = (syfsObjects[i])->geometry();

        // 检查丘丘王和箭的边界框是否相交
        if (syfsRect.intersects(arrowRect)) {
            // 发生碰撞，将丘丘王对象的指针添加到需要更改的容器中
            if (syfsObjects[i]->lives - atk <= 0) {
                syfsObjects[i]->hide();
                syfsObjects[i]->setFixedSize(0, 0);
                this->killNumber++;
                money += 20;
                if (killNumber == sumQQren + sumQQking + sumsyfs) {
                    qqrenObjects.clear();
                    qqkingObjects.clear();
                    syfsObjects.clear();
                    QTimer::singleShot(3500, [=]() {
                        money += (sumsyfs + 1) * 20 + (sumQQking + 1) * 5 + sumQQren + 1;
                        score += (sumsyfs + 1) * 20 + (sumQQking + 1) * 5 + sumQQren + 1;
                        emit haveKilledAllqqren();
                    });
                }
            } else {
                syfsObjects[i]->lives -= atk;
            }
        }
    }
}

void Scene03::resetKeyStates() {
    moveUp = false;
    moveDown = false;
    moveLeft = false;
    moveRight = false;
}
