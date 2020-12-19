//
// Created by Louis on 06/12/2020.
//

#include <iostream>
#include <QApplication>
#include <QPushButton>

#include "Interpreteur.h"
#include "Computer.h"
#include "Operateur.h"
#include "Litterale.h"
#include "Pile.h"

using namespace std;

int main(int argc, char *argv[]) {
    /*
    QApplication a(argc, argv);
    QPushButton button("Hello world!", nullptr);
    button.resize(200, 100);
    button.show();

    Controleur test= Controleur(Interpreteur::obtenirInterpreteur(), Pile::obtenirPile());

    return QApplication::exec();
    */

    Litterale* ptr1;
    Litterale* ptr2;

    ptr1 = new Entier(5);
    ptr2 = new Entier(10);

    Item i1(ptr1);
    Item i2(ptr2);

    Entier& ptr3 = (Entier &)Operateur::opPlus(i1, i2);
    cout << "ptr3:" << ptr3.getEntier() << endl;

    /*Entier& ptr4 = (Entier &)Operateur::inventaireOpArite2["-"](i1, i2);
    Entier& ptr5 = (Entier &)Operateur::inventaireOpArite1["NEG"](i1);
    Entier& ptr6 = (Entier &)Operateur::inventaireOpArite1["NEG"](i2);


    cout << "ptr4:" << ptr4.getEntier() << endl;
    cout << "ptr5:" << ptr5.getEntier() << endl;
    cout << "ptr6" << ptr6.getEntier() << endl;
    */

    return 0;
}
