#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QMainWindow>
#include <QPalette>
#include <QPushButton>

#include "choosescene.h"
#include "equipment.h"
#include "hotel.h"
#include "introduction.h"
#include "maincharacter.h"
#include "myequipment.h"

class MainScene : public QMainWindow {
    Q_OBJECT
public:
    int money;
    int score;

    explicit MainScene(QWidget *parent = nullptr);
    ~MainScene();
signals:
};

#endif// MAINSCENE_H
