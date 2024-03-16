#include "startscene.h"

#include <QPushButton>

#include "mainscene.h"

int score;

int money;
int velocity = 6;
int atk = 10;

int maxLives = 3;
int livesOfLinny = 3;

StartScene::StartScene(QWidget *parent)
    : QMainWindow(parent) {
    // 加载图标图片
    QPixmap iconPixmap(":/array/04.png");
    // 调整图标大小
    iconPixmap = iconPixmap.scaled(QSize(64, 64), Qt::KeepAspectRatio);
    // 设置窗口图标
    this->setWindowIcon(QIcon(iconPixmap));

    this->setFixedSize(1800, 1100);

    //创建主要界面
    MainScene *mainScene = new MainScene(this);

    // 设置背景图片
    QString imagePath = ":/background/1.png";// 设置背景图片路径

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

    //开始按钮
    {
        QPushButton *startButton = new QPushButton(this);
        startButton->setFixedSize(400, 74);
        startButton->move(665, 890);
        startButton->setText("开始游戏");
        connect(startButton, &QPushButton::clicked, [=]() {
            score = 0;
            money = 0;
            velocity = 6;
            atk = 10;
            maxLives = 3;
            livesOfLinny = 3;

            this->close();
            mainScene->show();
        });
        connect(mainScene, &MainScene::theGameEnd, [=]() {
            mainScene->close();
            this->show();
        });
        startButton->setStyleSheet(
            "color:#586B8C;"
            "background-color:#E2D9D0;"
            "font-weight:bold;"
            "text-align: center;"// 文本水平居中
            "border-radius: 20px;"
            "border-width: 2px;"
            "border-color: #586B8C;"
            "font-size: 30px;"
            "border-style: solid;"
            "border-width: 5px;"// 设置边框宽度为2像素
            "border-color: #586B8C");
    }
}

StartScene::~StartScene() {
}
