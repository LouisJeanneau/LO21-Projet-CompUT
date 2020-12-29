//
// Created by Louis on 06/12/2020.
//

#include <iostream>
#include <QApplication>
#include "Interpreteur.h"
#include "fenetreprincipale.h"

using namespace std;

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    fenetrePrincipale fenetre;
    fenetre.show();
    return a.exec();
}
