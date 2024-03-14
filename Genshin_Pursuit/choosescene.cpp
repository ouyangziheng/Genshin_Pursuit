#include "choosescene.h"

extern int livesOfLinny;

int waveOfMonster01 = 0;
int waveOfMonster02 = 0;
int waveOfMonster03 = 0;

bool isShow = false;
int times = 0;

//胜利场景
void ChooseScene::victoryScene01() {
    // 获取窗口的中心位置
    int centerX = width() / 2;
    int centerY = height() / 2;

    // 创建一个QLabel，并设置图片
    QLabel *label = new QLabel(this);
    QPixmap originalPixmap(":/animation/victory.png");
    QPixmap pixmap = originalPixmap.scaled(originalPixmap.size() / 2, Qt::KeepAspectRatio);
    label->setPixmap(pixmap);
    label->setGeometry(centerX - pixmap.width() / 2, -pixmap.height(), pixmap.width(), pixmap.height());

    // 创建一个胜利动画，让label对象从顶部跳跃到中心位置
    QPropertyAnimation *victoryAnimation = new QPropertyAnimation(label, "geometry", this);
    victoryAnimation->setDuration(1000);
    victoryAnimation->setStartValue(QRect(centerX - pixmap.width() / 2, -pixmap.height(), pixmap.width(), pixmap.height()));
    victoryAnimation->setEndValue(QRect(centerX - pixmap.width() / 2, centerY - pixmap.height() / 2, pixmap.width(), pixmap.height()));

    // 添加弹跳效果
    victoryAnimation->setEasingCurve(QEasingCurve::OutBounce);

    // 创建一个停留动画，在动画结束后停留2秒钟
    QPropertyAnimation *stayAnimation = new QPropertyAnimation(label, "geometry", this);
    stayAnimation->setDuration(2000);
    stayAnimation->setStartValue(victoryAnimation->endValue());
    stayAnimation->setEndValue(victoryAnimation->endValue());

    // 连接停留动画的finished()信号到槽函数，用于在动画完成后删除相关对象
    connect(stayAnimation, &QPropertyAnimation::finished, label, &QObject::deleteLater);
    connect(stayAnimation, &QPropertyAnimation::finished, stayAnimation, &QObject::deleteLater);

    // 启动动画，先执行下降动画，然后执行停留动画
    connect(victoryAnimation, &QPropertyAnimation::finished, [=]() {
        stayAnimation->start();
    });
    victoryAnimation->start();
}

void ChooseScene::showDecisionDialog() {
    // 创建消息框并设置提示信息
    QMessageBox *decisionBox = new QMessageBox;
    decisionBox->setIcon(QMessageBox::Warning);
    decisionBox->setText("Linny 失去了生命！");

    // 添加返回按钮
    QPushButton *returnButton = decisionBox->addButton("返回", QMessageBox::AcceptRole);

    // 连接返回按钮的点击信号到槽函数
    connect(returnButton, &QPushButton::clicked, [=]() {
        QMessageBox::warning(this, "提示", "回到酒庄休息可以恢复生命");
        // 处理返回按钮点击事件，例如返回到上一个场景
        returnMainscene();
    });

    // 显示消息框
    decisionBox->show();
}

//选择关卡
ChooseScene::ChooseScene(QWidget *parent) : QMainWindow(parent) {
    // 设置背景色为纯白色
    QPalette pal = palette();
    pal.setColor(QPalette::Window, Qt::white);
    setAutoFillBackground(true);
    setPalette(pal);
    this->setFixedSize(1800, 1100);

    // 场景1
    {
        QPushButton *scene1Button = new QPushButton(this);
        scene1Button->setText("丘丘人的反击");
        scene1Button->setFixedSize(500, 80);
        scene1Button->move(700, 600);

        //连接场景1

        Scene01 *s1 = new Scene01(this);

        connect(scene1Button, &QPushButton::clicked, [=]() {
            if (livesOfLinny <= 0) {
                QMessageBox::warning(this, "提示", "林尼身负重伤，会酒庄休息片刻再来吧");
                returnMainscene();

            } else {
                isShow = false;
                s1->linny->move(900, 550);
                s1->createMoster();
                this->hide();
                s1->show();
                s1->startMove();

                connect(s1, &Scene01::haveKilledAllqqren, [=]() {
                    s1->protectBirth = 1;
                    victoryScene01();
                    s1->resetKeyStates();
                    waveOfMonster01++;
                    s1->stopMove();
                    s1->linny->move(900, 550);
                    s1->close();
                    this->show();
                });

                connect(s1, &Scene01::defeat, [=]() {
                    s1->protectBirth = true;
                    s1->resetKeyStates();
                    s1->stopMove();
                    s1->linny->move(1900, 1800);
                    s1->close();
                    this->show();
                    if (isShow == false) {
                        isShow = true;
                        showDecisionDialog();
                    }
                });
            }
        });
    }

    // 场景2
    {
        QPushButton *scene2Button = new QPushButton(this);
        scene2Button->setText("丘丘王的复仇");
        scene2Button->setFixedSize(500, 80);
        scene2Button->move(700, 700);

        //连接场景1
        Scene02 *s2 = new Scene02(this);

        connect(scene2Button, &QPushButton::clicked, [=]() {
            if (livesOfLinny <= 0) {
                QMessageBox::warning(this, "提示", "林尼身负重伤，会酒庄休息片刻再来吧");
                returnMainscene();
                goHotel();
            } else {
                isShow = false;
                s2->linny->move(900, 550);
                s2->createMoster();
                this->hide();
                s2->show();
                s2->startMove();

                connect(s2, &Scene02::haveKilledAllqqren, [=]() {
                    s2->protectBirth = 1;
                    victoryScene01();
                    waveOfMonster02++;
                    s2->resetKeyStates();
                    s2->stopMove();
                    s2->linny->move(900, 550);
                    s2->close();
                    this->show();
                });

                connect(s2, &Scene02::defeat, [=]() {
                    s2->protectBirth = true;
                    s2->stopMove();
                    s2->movementTimer->stop();
                    s2->resetKeyStates();
                    s2->linny->move(1900, 1800);
                    s2->close();
                    this->show();
                    if (isShow == false) {
                        isShow = true;
                        showDecisionDialog();
                    }
                });
            }
        });
    }

    // 场景3
    {
        QPushButton *scene3Button = new QPushButton(this);
        scene3Button->setText("深渊的注视");
        scene3Button->setFixedSize(500, 80);
        scene3Button->move(700, 800);

        //连接场景
        Scene03 *s3 = new Scene03(this);
        connect(scene3Button, &QPushButton::clicked, [=]() {
            if (livesOfLinny <= 0) {
                QMessageBox::warning(this, "提示", "林尼身负重伤，会酒庄休息片刻再来吧");
                returnMainscene();
            } else {
                isShow = false;
                s3->linny->move(900, 550);
                s3->createMoster();
                this->hide();
                s3->show();
                s3->startMove();

                connect(s3, &Scene03::haveKilledAllqqren, [=]() {
                    s3->protectBirth = 1;
                    victoryScene01();
                    waveOfMonster03++;
                    s3->resetKeyStates();
                    s3->stopMove();
                    s3->linny->move(900, 550);
                    s3->close();
                    this->show();
                });

                connect(s3, &Scene03::defeat, [=]() {
                    s3->protectBirth = true;
                    s3->stopMove();
                    s3->linny->move(1900, 1800);
                    s3->resetKeyStates();
                    s3->close();
                    this->show();
                    if (isShow == false) {
                        isShow = true;
                        showDecisionDialog();
                    }
                });
            }
        });
    }

    // 返回
    {
        QPushButton *exitButton = new QPushButton(this);
        exitButton->setText("返回");
        exitButton->setFixedSize(500, 80);
        exitButton->move(700, 900);
        connect(exitButton, &QPushButton::clicked, [=]() {
            emit returnMainscene();
        });
    }
}
