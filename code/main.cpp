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

    Litterale* ptr1 = new Entier(5);
    Litterale* ptr2 = new Entier(10);

    Item i1(ptr1);
    Item i2(ptr2);

    Entier& ptr3 = dynamic_cast<Entier&>(Operateur::inventaireOpArite2["+"](i1, i2));
    cout << ptr3.getEntier() << endl;

    return QApplication::exec();
}
