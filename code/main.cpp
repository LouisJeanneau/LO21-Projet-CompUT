//
// Created by Louis on 06/12/2020.
//

#include <iostream>
#include <QApplication>
#include <QPushButton>

#include "Interpreteur.h"
#include "Computer.h"

using namespace std;

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QPushButton button("Hello world!", nullptr);
    button.resize(200, 100);
    button.show();

    Controleur test= Controleur(Interpreteur::obtenirInterpreteur(), Pile::obtenirPile());

    Interpreteur::obtenirInterpreteur().interprete("1 1 2 10 80");
    Pile::obtenirPile().debug();
    Interpreteur::obtenirInterpreteur().interprete("+ 17 +");
    Pile::obtenirPile().debug();
}
