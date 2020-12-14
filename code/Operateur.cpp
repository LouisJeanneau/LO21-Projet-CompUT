#include <__bit_reference>
//
// Created by Ismail Kadiri on 08/12/2020.
//

#include "Operateur.h"
#include "Pile.h"

//Initialisation de la map contenant les arités de chaque opérateur



QMap<QString, std::function<Litterale(Item, Item)>> Operateur::inventaireOpArite2 = {

        {"+", opPlus}
};

//test

QMap<QString, std::function<Litterale(Item)>> Operateur::inventaireOpArite1 = {
        {"NEG", opNEG}
};

QMap<QString, std::function<Litterale(Item)>> Operateur::inventaireOpArite0 = {};




QMap<QString, int> Operateur::inventaireOperateur = {

        //Operateurs numeriques
        {"+", 2},
        {"-", 2},
        {"*", 2},
        {"/", 2},
        {"DIV", 2},
        {"NEG", 1},

        //Operateurs logiques
        {"=", 2},
        {"!=", 2},
        {"=<", 2},
        {">=", 2},
        {"<", 2},
        {">", 2},
        {"AND", 2},
        {"OR", 2},
        {"NOT", 1},

        //Operateur EVAL
        {"EVAL", 0},

        //Operateur de manipulation de la pile
        {"DUP", 1},
        {"DROP", 1},
        {"SWAP", 2},
        {"CLEAR", 0}, /* arité égale au nombre d'éléments empilés */

        //Operateur conditionnels et de boucle
        {"IFT", 2}
};



Operateur::Operateur() {
    std::cout << "Creation Operateur" << std::endl;
}

Operateur::~Operateur() noexcept {
    std::cout << "Destruction Operateur" << std::endl;

}

Litterale Operateur::opPlus(Item i1, Item i2) {

    Litterale l1 = i1.obtenirLitterale();
    Litterale l2 = i2.obtenirLitterale();
    unsigned int n = l1.getNombre() + l2.getNombre();

    return Litterale(n);
}

Litterale Operateur::opNEG(Item i) {
    return Litterale(0);
}
/*
//Operateurs numériques


Item Operateur::opPlus() {

    //Récuperer l'arité
    unsigned int arite = inventaireOperateur["+"];
    // vérifier que i1 et i2 sont de types compatibles avant
    //depop arite éléments de la pile
    Item i1 = Pile::pop();
    Item i2 = Pile::pop();

    //Si i1 et i2 sont des littérales numériques
    //Sinon catch error -> push i1 && i2

    //i1+i2 = création d'une nouvelle littérale (dépend des types) + insertion dans tableau de Pile
    // push?


    return;
}

*/

