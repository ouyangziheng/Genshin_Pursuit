#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include <QMainWindow>

namespace Ui {
class Equipment;
}

class Equipment : public QMainWindow {
    Q_OBJECT

public:
    explicit Equipment(QMainWindow *parent = nullptr);
    ~Equipment();

signals:
    void returnButtonClicked();

private:
    Ui::Equipment *ui;
};

#endif// EQUIPMENT_H
