#include "introduction.h"

#include <QtWidgets>

#include "QPushButton"
#include "ui_introduction.h"

Introduction::Introduction(QWidget *parent) : QMainWindow(parent) {
    this->setFixedSize(1800, 1100);

    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
    effect->setColor(QColor("#725D78"));// 设置轮廓颜色
    effect->setOffset(0, 0);            // 设置轮廓偏移
    effect->setBlurRadius(15);          // 设置轮廓模糊半径

    QLabel *label = new QLabel(this);
    label->setFixedSize(1000, 800);
    label->move(288, 100);

    label->setText(
        "<html>"
        "<h1 style=\"font-size:24px; color: white;\">游戏介绍</h1>"
        "<h2 style=\"font-size:18px; color: white;\">在这款游戏中，你将扮演林尼的角色，与怪物展开斗争<br>"
        "可以购买各种装备武装自己，提升主角，赢取更高分数吧</h2>"

        "<h1 style=\"font-size:24px; color: white;\">玩法介绍</h1>"
        "<h2 style=\"font-size:18px; color: white;\">你可以移动上下左右键，来操控角色，点击鼠标左键发出进攻<br>"
        "躲避怪兽攻击并尽力击杀怪兽吧！</h2>"

        "<h1 style=\"font-size:24px; color: white;\">场景介绍</h1>"
        "<h2 style=\"font-size:18px; color: white;\">外出作战:与怪物展开斗争，共三关<br>"
        "每关可以重复游玩，怪物属性随之提高</h2>"
        "<h2 style=\"font-size:18px; color: white;\">多莉商城:消耗摩拉购买武器装备<br>"
        "提升林尼属性，更好的与怪物作战，装备可以重复购买哦~</h2>"
        "<h2 style=\"font-size:18px; color: white;\">晨曦酒庄:消耗摩拉，回复生命值,<br>"
        "注:消耗摩拉数目与进入次数有关，回复值域最大生命有关</h2>"

        "<h1 style=\"font-size:24px; color: white;\">怪物介绍</h1>"

        "<h2 style=\"font-size:18px; color: white;\">丘丘人:移动速度快，生命值低</h2>"
        "<h2 style=\"font-size:18px; color: white;\">丘丘王:移动速度较慢，生命值高，可以使用冲撞的技能</h2>"
        "<h2 style=\"font-size:18px; color: white;\">深渊法师:移动速度慢，生命值较高，可瞬移，可减速角色</h2>"

        "</html>");

    // 设置背景图片
    QString imagePath = ":/background/888.jpg";// 设置背景图片路径

    {
        QPixmap backgroundImage(imagePath);// 加载背景图片
        if (!backgroundImage.isNull()) {
            backgroundImage = backgroundImage.scaled(this->size(), Qt::KeepAspectRatioByExpanding);
            // 调整图片尺寸以适应窗口大小
            QPalette palette;
            palette.setBrush(this->backgroundRole(), QBrush(backgroundImage));
            this->setPalette(palette);
        }
    }

    QPushButton *quitButton = new QPushButton("离开", this);
    quitButton->setGeometry(1530, 60, 170, 60);// 设置按钮位置和大小
    quitButton->setStyleSheet(
        "color:#74627D;"
        "background-color:#E0B4E3;"
        "font-weight:bold;"
        "text-align: center;"// 文本水平居中
        "border-radius: 20px;"
        "border-color: #74627D;"
        "font-size: 30px;"
        "border-style: solid;"
        "border-width: 5px;");

    connect(quitButton, &QPushButton::clicked, [=]() {
        emit returnMainScene();
    });
}

Introduction::~Introduction() {
}
