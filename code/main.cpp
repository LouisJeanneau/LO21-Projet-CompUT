//
// Created by Louis on 06/12/2020.
//

#include <iostream>
#include <QApplication>
#include "Interpreteur.h"
#include "Computer.h"
#include "fenetreprincipale.h"

using namespace std;

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    fenetrePrincipale fenetre;
    fenetre.show();

    Controleur test= Controleur(Interpreteur::obtenirInterpreteur(), Pile::obtenirPile());

    Interpreteur::obtenirInterpreteur().interprete("1 1 2 10 80");
    Pile::obtenirPile().debug();
    Interpreteur::obtenirInterpreteur().interprete("+ 17 +");
    Pile::obtenirPile().debug();
    return a.exec();
}
