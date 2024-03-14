#ifndef CHARACTER_H
#define CHARACTER_H

#include <QObject>
#include <QString>

class Character : public QObject {
    Q_OBJECT
private:
    int health;    // 当前生命值
    int maxHealth; // 最大生命值
    int coins;     // 金币数量

public:
    explicit Character(QObject *parent = nullptr);

    // 受到伤害的方法
    void takeDamage(int damage);

    // 恢复生命值的方法
    void heal(int amount);

    // 获得经验值的方法
    void gainExperience(int amount);

    // 升级的方法
    void levelUp();

    // 收集金币的方法
    void collectCoins(int amount);

    // 获取角色名字
    QString getName() const;

    // 获取角色生命值
    int getHealth() const;

    // 获取角色等级
    int getLevel() const;

    // 获取角色经验值
    int getExperience() const;

    // 获取角色金币数量
    int getCoins() const;

signals:
    // 角色生命值改变时发出的信号
    void healthChanged(int newHealth);

    // 角色等级改变时发出的信号
    void levelChanged(int newLevel);

    // 角色经验值改变时发出的信号
    void experienceChanged(int newExperience);

    // 角色金币数量改变时发出的信号
    void coinsChanged(int newCoins);
};

#endif// CHARACTER_H
