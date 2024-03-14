#ifndef MAINCHARACTER_H
#define MAINCHARACTER_H

#include <QDebug>
#include <QKeyEvent>
#include <QLabel>
#include <QMainWindow>
#include <QPainter>
#include <QTimer>

class MainCharacter : public QLabel {
    Q_OBJECT
public:
    explicit MainCharacter(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);
    void updateImage();
    int isImage;

signals:
};

#endif// MAINCHARACTER_H
