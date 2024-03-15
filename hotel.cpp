#include "hotel.h"

extern int money, maxLives, livesOfLinny;
int n = 0;

Hotel::Hotel(QWidget *parent) : QMainWindow(parent) {
    this->setFixedSize(1100, 1100);

    // 创建退出按钮

    QPushButton *quitButton = new QPushButton("离开", this);
    quitButton->setGeometry(1560, 40, 130, 60);// 设置按钮位置和大小
    quitButton->setStyleSheet("QPushButton { background-color:  #FFB6C1; color : #003C9D; }");
    connect(quitButton, &QPushButton::clicked, [=]() {
        emit returnMainScene();
    });

    // 创建进入酒店按钮
    QPushButton *enterHotelButton = new QPushButton(this);
    enterHotelButton->setText("进入酒店");
    enterHotelButton->setGeometry(705, 800, 300, 300);
    enterHotelButton->setStyleSheet("QPushButton { background-color: transparent; border: none; font-size: 20px; color: #FFFFFF; }");

    // 连接进入酒店按钮的点击事件到槽函数
    connect(enterHotelButton, &QPushButton::clicked, [=]() {
        // 弹出询问对话框
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "进入酒店", "是否要进入酒店？", QMessageBox::Yes | QMessageBox::No);
        int cost = 100 * n + 200;
        if (reply == QMessageBox::Yes) {
            if (money >= cost) {
                // 检查用户金钱是否足够购买
                money -= cost;// 扣除购买所需金钱
                int heal = maxLives * (0.5);
                QString healString = QString::number(heal);
                n++;
                QMessageBox::warning(this, "成功进入酒庄", "一夜好梦<br>您的生命值回复了" + healString);
            } else {
                // 用户金钱不足，需要检验生命值
                QMessageBox::warning(this, "提示", "由于金币不足,您被酒庄拒绝了");
                if (livesOfLinny <= 0) {
                    QMessageBox::warning(this, "提示", "林尼身负重伤,无法移动,游戏失败了");
                }
            }
        }
    });
}

void Hotel::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);// 设置抗锯齿

    // 加载图片
    QPixmap pixmap(":/hotel/1.png");

    // 绘制图片
    painter.drawPixmap(0, 0, width(), height(), pixmap);

    // 绘制完成后调用父类的 paintEvent() 函数以确保正确的绘图行为
    QWidget::paintEvent(event);
}
