#include "equipment.h"

#include "ui_equipment.h"

Equipment::Equipment(QMainWindow *parent) : QMainWindow(parent),
                                            ui(new Ui::Equipment) {
    ui->setupUi(this);
    connect(ui->returnButton, &QPushButton::clicked, [=]() {
        emit returnButtonClicked();
    });

    QPixmap pixmap(":/path_to_your_image/image.png");

    // 设置按钮图标
    this->PushButton_03.setIcon(QIcon(pixmap));

    //    // 调整图标大小以适应按钮
    //    button.setIconSize(pixmap.rect().size());
}

Equipment::~Equipment() {
    delete ui;
}
