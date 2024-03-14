#ifndef STARTSCENE_H
#define STARTSCENE_H

#include <QMainWindow>
#include <QPalette>

class StartScene : public QMainWindow {
    Q_OBJECT

public:
    StartScene(QWidget *parent = nullptr);
    ~StartScene();
};
#endif// STARTSCENE_H
