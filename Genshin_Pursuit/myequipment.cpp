#include "myequipment.h"

extern int money;
extern int velocity, attack, maxLives;

QVector<QString> stringName = {"猎弓", "历练的猎弓", "弹弓", "烈阳之嗣", "静谧之曲",
                               "若水", "飞雷之弦振", "最初的大魔术", "阿莫斯之弓",
                               "生之花", "死之羽", "时之沙", "空之杯", "理之冠"};

QVector<QString> stringDetail = {"攻击力 +1<br>",
                                 "攻击力 +3<br>",
                                 "攻击力 +8<br>",
                                 "攻击力 +10, 移速 +1<br>",
                                 "攻击力 +15<br>",

                                 "攻击力 +20, 最大生命 +3<br>",
                                 "攻击力 +20, 移速 +1<br>"
                                 "攻击力 +15, 移速 +3<br>"
                                 "攻击力 +30<br>",
                                 "攻击力 +24, 最大生命 +1, 移速 +1<br>",

                                 "最大生命 +7<br>",
                                 "攻击力 +10, 最大生命 +3<br>",
                                 "攻击力 +10, 最大生命 +1, 移速 +2<br>",
                                 "最大生命 +3, 移速 +2<br>",
                                 "移速 +3<br>"};

QVector<int> costs = {1, 2, 5, 10, 10, 100, 100, 100, 100, 50, 50, 50, 50, 50};
myEquipment::myEquipment(QWidget *parent) : QMainWindow(parent) {
    this->setFixedSize(1800, 1100);
    QVector<QPushButton *> recordOfButton;
    //设置基本信息
    {// 创建标题按钮
        QLabel *titleButton = new QLabel("欢迎来到多莉的商城", this);
        titleButton->setGeometry(500, 130, 800, 100);// 设置按钮位置和大小

        // 创建字体对象
        QFont titleFont("华文行楷", 30, QFont::Bold);

        // 设置按钮字体和大小
        titleButton->setFont(titleFont);

        // 设置文本居中对齐
        titleButton->setAlignment(Qt::AlignCenter);

        // 显示标题按钮
        titleButton->show();
    }

    // 创建退出按钮
    {
        QPushButton *quitButton = new QPushButton("离开", this);
        quitButton->setGeometry(1560, 40, 130, 60);// 设置按钮位置和大小
        quitButton->setStyleSheet("QPushButton { background-color: #FF6347; color: white; }");
        connect(quitButton, &QPushButton::clicked, [=]() {
            emit returnMainScene();
        });
    }

    // 可爱的多莉耶
    {
        QPushButton *pictureButton = new QPushButton(this);
        pictureButton->setGeometry(40, 65, 400, 400);

        QIcon icon(":/photos/01.png");

        // 设置图像到按钮上
        pictureButton->setIcon(icon);

        // 获取按钮的大小
        QSize buttonSize = pictureButton->size();

        // 将图像缩放到按钮大小
        QSize scaledSize(buttonSize.width() * 1.0, buttonSize.height() * 1.0);
        QPixmap pixmap = icon.pixmap(scaledSize);

        // 设置调整大小后的图像到按钮上
        pictureButton->setIcon(QIcon(pixmap));

        // 设置按钮的大小以适应图像大小
        pictureButton->setIconSize(scaledSize);

        // 设置按钮的固定大小
        pictureButton->setFixedSize(buttonSize);

        // 显示按钮
        pictureButton->show();
    }

    // 创建标签显示金币数量
    {
        QLabel *moneyLabel = new QLabel(this);
        moneyLabel->setText("金币数: " + QString::number(money));
        moneyLabel->setGeometry(65, 485, 400, 51);
        moneyLabel->setStyleSheet("QLabel { color: #B8860B; font-size:50px; font-weight: bold; }");
    }

    // 创建按钮网格
    {
        int buttonWidth = 200;
        int buttonHeight = 200;
        int horizontalSpacing = 20;
        int verticalSpacing = 20;
        int startX = 100 + (this->width() - buttonWidth * 5 - horizontalSpacing * 3) / 2;
        int startY = 300;
        for (int row = 0; row < 3; row++) {
            for (int col = 0; col < 5; col++) {
                QPushButton *button = new QPushButton(this);
                button->setProperty("equipmentIndex", row * 5 + col + 1);
                recordOfButton.push_back(button);

                int x = startX + col * (buttonWidth + horizontalSpacing);
                int y = startY + row * (buttonHeight + verticalSpacing);

                button->setGeometry(x, y, buttonWidth, buttonHeight);

                // 缩放图像
                QPixmap pixmap(QString(":/photos/%1.png").arg(row * 5 + col + 1));
                pixmap = pixmap.scaled(160, 160, Qt::KeepAspectRatio);// 将缩放后的图像重新赋值给pixmap

                // 设置调整大小后的图像到按钮上
                button->setIcon(QIcon(pixmap));

                // 设置按钮的图标大小以适应缩放后的图像大小
                button->setIconSize(pixmap.size());
            }
        }
    }

    // 在合适的地方连接所有按钮的点击事件到同一个槽函数
    for (QPushButton *button : recordOfButton) {
        connect(button, &QPushButton::clicked, this, &myEquipment::handleButtonClicked);
    }
}

void myEquipment::handleButtonClicked() {
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());// 获取发送信号的按钮
    if (clickedButton) {
        // 获取装备信息，假设装备信息存储在按钮的文本中
        int equipmentIndex = clickedButton->property("equipmentIndex").toInt();
        QString temp = stringName[equipmentIndex - 1];
        int cost = 10 * costs[equipmentIndex - 1];

        // 创建消息框并设置装备增益信息
        QMessageBox *messageBox = new QMessageBox(this);
        messageBox->setFixedSize(800, 500);
        messageBox->setWindowTitle("装备增益信息");
        messageBox->setText("您点击了：" + temp + "<br>这件装备的价格是" + QString::number(cost) + "金币");

        temp = stringDetail[equipmentIndex - 1];

        // 设置消息框的文本内容
        messageBox->setInformativeText("这里是装备的详细信息:<br>" + temp);
        // 显示消息框
        messageBox->exec();
        // 询问用户是否购买
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "购买确认", "是否购买该装备？", QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            if (money >= cost) {
                // 检查用户金钱是否足够购买
                money -= cost;// 扣除购买所需金钱
                moneyLabel->setText("金币数: " + QString::number(money));

                switch (equipmentIndex) {
                case 1:// 猎弓
                    attack += 1;
                    break;
                case 2:// 历练的猎弓
                    attack += 3;
                    break;
                case 3:// 弹弓
                    attack += 8;
                    break;
                case 4:// 烈阳之嗣
                    attack += 10;
                    velocity += 1;
                    break;
                case 5:// 静谧之曲
                    attack += 15;
                    break;
                case 6:// 若水
                    attack += 20;
                    maxLives += 3;
                    break;
                case 7:// 飞雷之弦振
                    attack += 20;
                    velocity += 1;
                    break;
                case 8:// 最初的大魔术
                    attack += 15;
                    velocity += 3;
                    break;
                case 9:// 阿莫斯之弓
                    attack += 30;
                    break;
                case 10:// 生之花
                    maxLives += 7;
                    break;
                case 11:// 死之羽
                    attack += 10;
                    maxLives += 3;
                    break;
                case 12:// 时之沙
                    attack += 10;
                    maxLives += 1;
                    velocity += 2;
                    break;
                case 13:// 空之杯
                    maxLives += 3;
                    velocity += 2;
                    break;
                case 14:// 理之冠
                    velocity += 3;
                    break;
                default:
                    // 处理未知的装备索引
                    break;
                }
                // 更新用户界面显示的属性信息，例如更新金钱显示
            } else {
                // 用户金钱不足，给出提示
                QMessageBox::warning(this, "购买失败", "金币不足，努力打怪获取金币");
            }
        } else {
            // 用户选择不购买
        }
    }
}
