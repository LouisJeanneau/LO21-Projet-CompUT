//
// Created by Louis on 06/12/2020.
//

#include <QApplication>
#include <QPushButton>
#include "Pile.h"
#include "Operateur.h"
#include <QDebug>
#include <QMapIterator>

#include "Interpreteur.h"
#include "Computer.h"


int main(int argc, char *argv[]) {
   /* QApplication a(argc, argv);
    QPushButton button("Hello world!", nullptr);
    button.resize(200, 100);
    button.show();

    Controleur test= Controleur(Interpreteur::obtenirInterpreteur(), Pile::obtenirPile());

    return QApplication::exec();
    */

    //Pile p;
    Operateur& op1 = Operateur::operateurInstance();
    Operateur& op2 = Operateur::operateurInstance();
    std::cout << &op1 << "|" << &op2 << std::endl;
    std::cout << "size: " << Operateur::inventaireOperateur.size() << std::endl;


    QMapIterator<QString, int> i(Operateur::inventaireOperateur);
    while (i.hasNext()) {
        i.next();
        qDebug() << i.key() << ": " << i.value();
    }

    qDebug() << Operateur::inventaireOperateur["+"];

    Litterale l1(5);
    Litterale l2(10);
    Item i1(l1);
    Item i2(l2);

    Litterale l3 = Operateur::inventaireOpArite2["+"](i1,i2);

    qDebug() << l3.getNombre();


    return 0;

}
