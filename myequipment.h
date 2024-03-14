#ifndef MYEQUIPMENT_H
#define MYEQUIPMENT_H

#include <QApplication>
#include <QGridLayout>
#include <QLabel>
#include <QMainWindow>
#include <QMessageBox>
#include <QPushButton>
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
