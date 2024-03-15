#include "mainscene.h"

int score;

int money;
int velocity = 6;
int atk = 1;

int maxLives = 3;
int livesOfLinny = 3;

MainScene::MainScene(QWidget *parent) : QMainWindow(parent) {
    this->setFixedSize(1800, 1100);

    // 设置背景图片
    QString imagePath = ":/background/2.png";// 设置背景图片路径

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

    //场景选择  #846955 #E4C8A3
    {
        QPushButton *chooseSceneButton = new QPushButton(this);
        chooseSceneButton->setText("外出历险");
        chooseSceneButton->setFixedSize(400, 80);
        chooseSceneButton->move(720, 600);
        chooseSceneButton->setStyleSheet(
            "color:#846955;"
            "background-color:#E4C8A3;"
            "font-weight:bold;"
            "text-align: center;"// 文本水平居中
            "border-radius: 20px;"
            "border-width: 2px;"
            "border-color: #846955;"
            "font-size: 30px;"
            "border-style: solid;"
            "border-width: 5px;"// 设置边框宽度为2像素
            "border-color: #846955");

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
        chooseEquipmentButton->setFixedSize(400, 80);
        chooseEquipmentButton->move(720, 700);

        chooseEquipmentButton->setStyleSheet(
            "color:#846955;"
            "background-color:#E4C8A3;"
            "font-weight:bold;"
            "text-align: center;"// 文本水平居中
            "border-radius: 20px;"
            "border-width: 2px;"
            "border-color: #846955;"
            "font-size: 30px;"
            "border-style: solid;"
            "border-width: 5px;"// 设置边框宽度为2像素
            "border-color: #846955");

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
        supplicationButton->setFixedSize(400, 80);
        supplicationButton->move(720, 800);

        supplicationButton->setStyleSheet(
            "color:#846955;"
            "background-color:#E4C8A3;"
            "font-weight:bold;"
            "text-align: center;"// 文本水平居中
            "border-radius: 20px;"
            "border-width: 2px;"
            "border-color: #846955;"
            "font-size: 30px;"
            "border-style: solid;"
            "border-width: 5px;"// 设置边框宽度为2像素
            "border-color: #846955");

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
        introButton->setFixedSize(400, 80);
        introButton->move(720, 900);

        introButton->setStyleSheet(
            "color:#846955;"
            "background-color:#E4C8A3;"
            "font-weight:bold;"
            "text-align: center;"// 文本水平居中
            "border-radius: 20px;"
            "border-width: 2px;"
            "border-color: #846955;"
            "font-size: 30px;"
            "border-style: solid;"
            "border-width: 5px;"// 设置边框宽度为2像素
            "border-color: #846955");

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
