#include "myequipment.h"

extern int money;
extern int velocity, atk, maxLives;

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
    qDebug() << money;
    this->setFixedSize(1800, 1100);
    // 设置背景图片
    QString imagePath = ":/background/4.jpg";// 设置背景图片路径

    // 检查图片是否存在
    {
        QPixmap backgroundImage(imagePath);// 加载背景图片
        if (!backgroundImage.isNull()) {
            backgroundImage = backgroundImage.scaled(this->size(), Qt::KeepAspectRatioByExpanding);// 调整图片尺寸以适应窗口大小
            QPalette palette;
            palette.setBrush(this->backgroundRole(), QBrush(backgroundImage));
            this->setPalette(palette);
        }
    }
    QVector<QPushButton *> recordOfButton;
    //设置基本信息
    {// 创建标题按钮
        QLabel *titleButton = new QLabel("欢迎来到多莉的商城", this);
        titleButton->setGeometry(380, 95, 800, 100);// 设置按钮位置和大小

        // 创建字体对象
        QFont titleFont("华文行楷", 40, QFont::Bold);

        // 设置按钮字体和大小
        titleButton->setFont(titleFont);

        // 设置文本居中对齐
        titleButton->setAlignment(Qt::AlignCenter);

        // 设置文本颜色
        titleButton->setStyleSheet("color:#446351;");

        // 显示标题按钮
        titleButton->show();
    }

    // 创建退出按钮
    {
        QPushButton *quitButton = new QPushButton("离开", this);
        quitButton->setGeometry(1460, 80, 150, 80);// 设置按钮位置和大小
        quitButton->setStyleSheet(
            "color:#425449;"
            "background-color:#EFF1DB;"
            "font-weight:bold;"
            "text-align: center;"// 文本水平居中
            "border-radius: 20px;"
            "border-width: 5px;"
            "border-color: #425449;"
            "font-size: 30px;"
            "border-style: solid;");

        connect(quitButton, &QPushButton::clicked, [=]() {
            emit returnMainScene();
        });
    }

    {// 可爱的多莉耶
        QLabel *pictureLabel = new QLabel(this);
        pictureLabel->setGeometry(1200, 25, 200, 200);// 设置 QLabel 的位置和大小

        // 加载图像
        QPixmap pixmap(":/photos/77.png");

        // 缩放图像以适应 QLabel
        QPixmap scaledPixmap = pixmap.scaled(QSize(200, 200), Qt::KeepAspectRatio);

        // 设置图像到 QLabel 上
        pictureLabel->setPixmap(scaledPixmap);

        // 显示 QLabel
        pictureLabel->show();
    }

    // 创建标签显示金币数量
    {
        QLabel *moneyLabel = new QLabel(this);
        QTimer *updateLabel = new QTimer(this);
        updateLabel->start(1000);
        connect(updateLabel, &QTimer::timeout, [=]() {
            moneyLabel->setText("金币数: " + QString::number(money));
        });

        moneyLabel->setGeometry(65, 255, 400, 51);
        moneyLabel->setStyleSheet("QLabel { color: #827B58; font-size:58px; font-weight: bold; }");
    }

    // 创建按钮网格
    {
        int buttonWidth = 200;
        int buttonHeight = 200;
        int horizontalSpacing = 20;
        int verticalSpacing = 20;
        int startX = -100 + (this->width() - buttonWidth * 5 - horizontalSpacing * 3) / 2;
        int startY = 350;
        for (int row = 0; row < 3; row++) {
            for (int col = 0; col < 5; col++) {
                QPushButton *button = new QPushButton(this);
                button->setProperty("equipmentIndex", row * 5 + col + 1);
                //#86A8A0  #EFF1DB
                button->setStyleSheet(
                    "color:#86A8A0;"
                    "background-color:#EFF1DB;"
                    "font-weight:bold;"
                    "text-align: center;"// 文本水平居中
                    "border-radius: 20px;"
                    "border-width: 8px;"
                    "border-color: #86A8A0;"
                    "font-size: 30px;"
                    "border-style: solid;");
                recordOfButton.push_back(button);

                int x = startX + col * (buttonWidth + horizontalSpacing);
                int y = startY + row * (buttonHeight + verticalSpacing);

                button->setGeometry(x, y, buttonWidth, buttonHeight);

                // 缩放图像
                QPixmap pixmap(QString(":/photos/%1.png").arg(row * 5 + col + 1));
                pixmap = pixmap.scaled(165, 165, Qt::KeepAspectRatio);// 将缩放后的图像重新赋值给pixmap

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

                switch (equipmentIndex) {
                case 1:// 猎弓
                    atk += 1;
                    break;
                case 2:// 历练的猎弓
                    atk += 3;
                    break;
                case 3:// 弹弓
                    atk += 8;
                    break;
                case 4:// 烈阳之嗣
                    atk += 10;
                    velocity += 1;
                    break;
                case 5:// 静谧之曲
                    atk += 15;
                    break;
                case 6:// 若水
                    atk += 20;
                    maxLives += 3;
                    break;
                case 7:// 飞雷之弦振
                    atk += 20;
                    velocity += 1;
                    break;
                case 8:// 最初的大魔术
                    atk += 15;
                    velocity += 3;
                    break;
                case 9:// 阿莫斯之弓
                    atk += 30;
                    break;
                case 10:// 生之花
                    maxLives += 7;
                    break;
                case 11:// 死之羽
                    atk += 10;
                    maxLives += 3;
                    break;
                case 12:// 时之沙
                    atk += 10;
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
