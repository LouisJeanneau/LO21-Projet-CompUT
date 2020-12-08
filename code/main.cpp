//
// Created by Louis on 06/12/2020.
//

#include <iostream>
#include <QApplication>
#include <QPushButton>

#include "Interpreteur.h"

using namespace std;

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QPushButton button("Hello world!", nullptr);
    button.resize(200, 100);
    button.show();

    return QApplication::exec();
}
