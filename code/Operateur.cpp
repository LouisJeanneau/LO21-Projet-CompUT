#include <__bit_reference>
//
// Created by Ismail Kadiri on 08/12/2020.
//

#include <iostream>
#include "Operateur.h"
#include "Pile.h"

//Initialisation de la map contenant les arités de chaque opérateur


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

/*
Item Operateur::opMoins() {
    return <#initializer#>;
}

Item Operateur::opMul() {
    return <#initializer#>;
}

Item Operateur::opDivision() {
    return <#initializer#>;
}

Item Operateur::opDIV() {
    return <#initializer#>;
}

Item Operateur::opMOD() {
    return <#initializer#>;
}

Item Operateur::opNEG(Item &i) {
    return <#initializer#>;
}

// ------------------------------------------------------

//Operateurs logiques

Item Operateur::opEgal() {
    return <#initializer#>;
}

Item Operateur::opDifferent() {
    return <#initializer#>;
}

Item Operateur::opInfEgal() {
    return <#initializer#>;
}

Item Operateur::opSupEgal() {
    return <#initializer#>;
}

Item Operateur::opSup() {
    return <#initializer#>;
}

Item Operateur::opInf() {
    return <#initializer#>;
}

Item Operateur::opAND() {
    return <#initializer#>;
}

Item Operateur::opOR() {
    return <#initializer#>;
}

Item Operateur::opNOT() {
    return <#initializer#>;
}

// ------------------------------------------------------

//Operateurs de manipulation de la Pile

Item Operateur::opDUP() {
    return <#initializer#>;
}

void Operateur::opDROP() {

}

void Operateur::opSWAP() {

}

void Operateur::opCLEAR() {

}

// ------------------------------------------------------

//Operateurs conditionnels et de boucle

void Operateur::opIFT() {

}

void Operateur::opEval() {

}

*/



