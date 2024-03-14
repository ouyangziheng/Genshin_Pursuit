#ifndef CHOOSESCENE_H
#define CHOOSESCENE_H

#include <QMainWindow>
#include <QObject>
#include <QPushButton>

#include "scene01.h"
#include "scene02.h"
#include "scene03.h"

class ChooseScene : public QMainWindow {
    Q_OBJECT
public:
    explicit ChooseScene(QWidget *parent = nullptr);
    void victoryScene01();
    void showDecisionDialog();

signals:
    void Game01Start();
    void returnMainscene();
    void goHotel();
};

#endif// CHOOSESCENE_H
