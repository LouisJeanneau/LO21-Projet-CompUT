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

    //TEST PARTIE LOUIS
    QString test("2 3 + 4 * Salut 'WESH' [Ceci est un programme + + SWAG] 1 9 157 /");
    Interpreteur testinter;
    testinter.interprete(test);
    //
    return QApplication::exec();
}
