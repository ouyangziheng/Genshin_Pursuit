#ifndef INTRODUCTION_H
#define INTRODUCTION_H

#include <QMainWindow>

namespace Ui {
class Introduction;
}

class Introduction : public QMainWindow {
    Q_OBJECT

public:
    explicit Introduction(QWidget *parent = nullptr);
    ~Introduction();

signals:
    void returnMainScene();

private:
};

#endif// INTRODUCTION_H
