#include "introduction.h"

#include "QPushButton"
#include "ui_introduction.h"

Introduction::Introduction(QWidget *parent) : QMainWindow(parent),
                                              ui(new Ui::Introduction) {
    ui->setupUi(this);

    QPushButton *quitButton = new QPushButton("离开", this);
    quitButton->setGeometry(600, 10, 50, 30);// 设置按钮位置和大小
    quitButton->setStyleSheet("QPushButton { background-color: #FF6347; color: white; }");
    connect(quitButton, &QPushButton::clicked, [=]() {
        emit returnMainScene();
    });
}

Introduction::~Introduction() {
    delete ui;
}
