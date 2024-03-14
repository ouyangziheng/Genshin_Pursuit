#include "mainscene.h"

int score;

int money;
int velocity = 6;
int atk = 1;

int maxLives = 3;
int livesOfLinny = 3;

MainScene::MainScene(QWidget *parent) : QMainWindow(parent) {
    this->setFixedSize(1800, 1100);
    // 设置背景色为纯白色
    QPalette pal = palette();
    pal.setColor(QPalette::Window, Qt::white);
    setAutoFillBackground(true);
    setPalette(pal);

    //场景选择
    {
        QPushButton *chooseSceneButton = new QPushButton(this);
        chooseSceneButton->setText("外出历险");
        chooseSceneButton->setFixedSize(500, 80);
        chooseSceneButton->move(700, 600);

        //创建选择界面
        ChooseScene *cs = new ChooseScene(this);
        connect(chooseSceneButton, &QPushButton::clicked, [=]() {
            this->hide();
            cs->show();
        });

        connect(cs, &ChooseScene::returnMainscene, [=]() {
            cs->close();
            this->show();
        });
    }

    //装备选择
    {
        QPushButton *chooseEquipmentButton = new QPushButton(this);
        chooseEquipmentButton->setText("多莉商城");
        chooseEquipmentButton->setFixedSize(500, 80);
        chooseEquipmentButton->move(700, 700);

        //创造装备界面
        myEquipment *eq = new myEquipment(this);
        connect(chooseEquipmentButton, &QPushButton::clicked, [=]() {
            this->hide();
            eq->show();
        });

        connect(eq, &myEquipment::returnMainScene, [=]() {
            eq->hide();
            this->show();
        });
    }

    //晨曦酒庄
    {
        QPushButton *supplicationButton = new QPushButton(this);
        supplicationButton->setText("晨曦酒庄");
        supplicationButton->setFixedSize(500, 80);
        supplicationButton->move(700, 800);

        Hotel *hl = new Hotel(this);
        connect(supplicationButton, &QPushButton::clicked, [=]() {
            this->hide();
            hl->show();
        });

        connect(hl, &Hotel::returnMainScene, [=]() {
            hl->hide();
            this->show();
        });
    }

    //游戏介绍
    {
        QPushButton *introButton = new QPushButton(this);
        introButton->setText("游戏介绍");
        introButton->setFixedSize(500, 80);
        introButton->move(700, 900);

        Introduction *it = new Introduction(this);
        connect(introButton, &QPushButton::clicked, [=]() {
            this->hide();
            it->show();
        });
        connect(it, &Introduction::returnMainScene, [=]() {
            it->hide();
            this->show();
        });
    }
}

MainScene::~MainScene() {
}
