//qq人的试炼
#include "scene01.h"
extern int money, score, velocity;
extern int livesOfLinny, maxLives;
extern int waveOfMonster01;

//构造函数
Scene01::Scene01(QWidget *parent) : QMainWindow(parent), killNumber(0) {
    // 设置背景色为纯白色
    QPalette pal = palette();
    pal.setColor(QPalette::Window, Qt::white);
    setAutoFillBackground(true);
    setPalette(pal);
    // 初始化界面和主角角色
    protectBirth = true;
    this->setFixedSize(1800, 1100);
    linny = new MainCharacter(this);
    linny->move(900, 550);
    quantityOfqqren = 0;
    //鼠标位置赋初值
    lastMousePosition = QPoint(0, 0);

    connect(this, &Scene01::leftMouseButtonHaveClicked, [=]() {
        this->attack();
    });
    //移动定时器
    movementTimer = new QTimer(this);
    connect(movementTimer, &QTimer::timeout, this, &Scene01::movePlayer);
    movementTimer->setInterval(10);// 设置定时器间隔（毫秒）

    connect(this, &Scene01::stopMove, [=]() {
        movementTimer->stop();
    });
    connect(this, &Scene01::startMove, [=]() {
        movementTimer->start();
    });
    connect(this, &Scene01::startMove, [=]() {
        QTimer::singleShot(3000, [=]() {
            protectBirth = false;
        });
    });
}

//创造怪兽
void Scene01::createMoster() {
    this->killNumber = 0;
    this->sumQQren = waveOfMonster01 * 10 + 5 + waveOfMonster01 * waveOfMonster01;
    qDebug() << sumQQren;

    this->quantityOfqqren = 0;
    QTimer *Birthofqqren = new QTimer(this);
    Birthofqqren->start(1000);
    //丘丘人行为
    connect(Birthofqqren, &QTimer::timeout, [=]() {
        if (quantityOfqqren < sumQQren) {
            quantityOfqqren += 1;

            // 创建 qqking 对象并设置随机位置
            qqren *smallqqren = new qqren(this);
            QTimer *timer_updateThePositionOfLinny = new QTimer(this);
            qqrenObjects.push_back(smallqqren);
            smallqqren->speed = 5 + waveOfMonster01;
            connect(this, &Scene01::stopMove, [=]() {
                timer_updateThePositionOfLinny->stop();
            });

            connect(this, &Scene01::startMove, [=]() {
                QTimer::singleShot(2000, [=]() {
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
                    livesOfLinny--;
                    emit defeat();
                    protectBirth = true;
                    // 这里可以写碰撞后的处理逻辑，比如林尼扣血等等
                }
            });
        }
    });
}

// 角色攻击
void Scene01::attack() {
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
// 根据按键状态移动角色
void Scene01::movePlayer() {
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
void Scene01::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        lastMousePosition = event->pos();
        leftMouseButtonHaveClicked();
    }
}

// 按键按下事件
void Scene01::keyPressEvent(QKeyEvent *event) {
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
void Scene01::keyReleaseEvent(QKeyEvent *event) {
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
void Scene01::checkCollision(Arrow *arr) {
    if (arr->state != 2) return;
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
            money++;
            qqrenObjects[i]->setFixedSize(0, 0);
            this->killNumber++;

            if (killNumber == sumQQren) {
                for (int i = 0; i < qqrenObjects.size(); i++) {
                    qqrenObjects[i]->setFixedSize(0, 0);
                }
                qqrenObjects.clear();
                QTimer::singleShot(3000, [=]() {
                    for (int i = 0; i < qqrenObjects.size(); i++) {
                        qqrenObjects[i]->setFixedSize(0, 0);
                    }
                    qqrenObjects.clear();
                    money += (sumQQren + 1);
                    score += (sumQQren + 1);
                    emit haveKilledAllqqren();
                });
            }
        }
    }
    if (arr->state == 3) arr->setFixedSize(0, 0);
}

void Scene01::resetKeyStates() {
    moveUp = false;
    moveDown = false;
    moveLeft = false;
    moveRight = false;
}
