#include "startscene.h"

#include <QPushButton>

#include "mainscene.h"

StartScene::StartScene(QWidget *parent)
    : QMainWindow(parent) {
    this->setFixedSize(1800, 1100);

    //创建主要界面
    MainScene *mainScene = new MainScene(this);

    // 设置背景图片
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
        } else {
            qDebug() << "Error: Failed to load background image";
        }
    } else {
        qDebug() << "Error: Background image path does not exist";
    }

    //开始按钮
    {
        QPushButton *startButton = new QPushButton(this);
        startButton->setFixedSize(400, 64);
        startButton->move(670, 890);
        startButton->setText("开始游戏");
        connect(startButton, &QPushButton::clicked, [=]() {
            this->close();
            mainScene->show();
        });
    }
}

StartScene::~StartScene() {
}
