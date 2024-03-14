#include "startscene.h"

#include <QPushButton>

#include "mainscene.h"

StartScene::StartScene(QWidget *parent)
    : QMainWindow(parent) {
    this->setFixedSize(1800, 1100);

    //创建主要界面
    MainScene *mainScene = new MainScene(this);

    //开始按钮
    {
        QPushButton *startButton = new QPushButton(this);
        startButton->setFixedSize(500, 80);
        startButton->move(700, 800);
        startButton->setText("开始游戏");
        connect(startButton, &QPushButton::clicked, [=]() {
            this->close();
            mainScene->show();
        });
    }

    //退出按钮
    {
        QPushButton *exitButton = new QPushButton(this);
        exitButton->setFixedSize(500, 80);
        exitButton->move(700, 900);
        exitButton->setText("退出游戏");
        connect(exitButton, &QPushButton::clicked, [=]() {
            this->close();
        });
    }
}

StartScene::~StartScene() {
}
