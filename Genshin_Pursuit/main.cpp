#include <QApplication>

#include "dataOfCharacter.h"
#include "maincharacter.h"
#include "startscene.h"
//linny为一个特定的按钮，linny为角色的基本信息

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    StartScene w;
    w.show();
    return a.exec();
}
