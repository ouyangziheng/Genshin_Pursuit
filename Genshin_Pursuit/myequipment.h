#ifndef MYEQUIPMENT_H
#define MYEQUIPMENT_H

#include <QApplication>
#include <QDebug>
#include <QGridLayout>
#include <QLabel>
#include <QMainWindow>
#include <QMessageBox>
#include <QPalette>
#include <QPushButton>
#include <QTimer>
#include <QVBoxLayout>

class myEquipment : public QMainWindow {
    Q_OBJECT
public:
    QLabel *moneyLabel;
    explicit myEquipment(QWidget *parent = nullptr);
    void handleButtonClicked();

signals:
    void returnMainScene();
};

#endif// MYEQUIPMENT_H
