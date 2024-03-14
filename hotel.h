#ifndef HOTEL_H
#define HOTEL_H

#include <QLabel>
#include <QMainWindow>
#include <QMessageBox>
#include <QObject>
#include <QPainter>
#include <QPixmap>
#include <QPropertyAnimation>
#include <QPushButton>
#include <QTimer>

class Hotel : public QMainWindow {
    Q_OBJECT
public:
    explicit Hotel(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event);
    void DefeatHotel();
signals:
    void returnMainScene();
};

#endif// HOTEL_H
