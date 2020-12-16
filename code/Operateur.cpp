//
// Created by Ismail Kadiri on 08/12/2020.
//

#include "Operateur.h"
#include "Pile.h"

//Initialisation de la map contenant les pointeurs des fonctions associés aux opérateurs d'arité 2
QMap<QString, function<Litterale&(Item, Item)>> Operateur::inventaireOpArite2 = {

        {"+", opPlus},
        {"-", opMoins},
        {"=", opEgal}

};

//Initialisation de la map contenant les pointeurs des fonctions associés aux opérateurs d'arité 1
QMap<QString, function<Litterale&(Item)>> Operateur::inventaireOpArite1 = {

        {"NEG", opNEG}
};

//Initialisation de la map contenant les pointeurs des fonctions associés aux opérateurs d'arité 2
QMap<QString, std::function<Litterale&()>> Operateur::inventaireOpArite0 = {
};

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

Litterale& Operateur::opPlus(Item i1, Item i2) {
    //récupérer les types de i1 i2
    string typeItem1 = i1.obtenirType();
    string typeItem2 = i2.obtenirType();
    //tester les types
    //récupérer les valeurs stockées

    auto& l1 = dynamic_cast<Entier &>(i1.obtenirLitterale());
    auto& l2 = dynamic_cast<Entier &>(i2.obtenirLitterale());
    int n1 = l1.getEntier();
    cout << "Operateur addition" << endl;
    cout << "Premier entier :" << n1 << endl;
    int n2 = l2.getEntier();
    cout << "Deuxieme entier :" << n2 << endl;
    //construire le nouvel littérale
    Litterale* ptr;
    ptr = new Entier(n1+n2);
    Pile::obtenirPile().pop();
    Pile::obtenirPile().pop();
    return *ptr;


}

Litterale &Operateur::opMoins(Item i1, Item i2) {
    //récupérer les types de i1 i2
    string typeItem1 = i1.obtenirType();
    string typeItem2 = i2.obtenirType();
    //tester les types
    //récupérer les valeurs stockées

    auto& l1 = dynamic_cast<Entier &>(i1.obtenirLitterale());
    auto& l2 = dynamic_cast<Entier &>(i2.obtenirLitterale());
    int n1 = l1.getEntier();
    cout << n1 << endl;
    int n2 = l2.getEntier();
    cout << n2 << endl;
    //construire le nouvel littérale
    Litterale* ptr;
    ptr = new Entier(n1-n2);
    return *ptr;

}

Litterale& Operateur::opNEG(Item i) {
    string typeItem1 = i.obtenirType();
    //tester les types
    //récupérer les valeurs stockées

    auto& l = dynamic_cast<Entier &>(i.obtenirLitterale());
    int n = l.getEntier();
    cout << n << endl;

    //construire le nouvel littérale
    Litterale* ptr;
    ptr = new Entier(-n);
    return *ptr;
}

Litterale &Operateur::opEgal(Item i1, Item i2) {
    //récupérer les types de i1 i2
    string typeItem1 = i1.obtenirType();
    string typeItem2 = i2.obtenirType();
    //tester les types
    //récupérer les valeurs stockées

    auto& l1 = dynamic_cast<Entier &>(i1.obtenirLitterale());
    auto& l2 = dynamic_cast<Entier &>(i2.obtenirLitterale());
    int n1 = l1.getEntier();
    cout << n1 << endl;
    int n2 = l2.getEntier();
    cout << n2 << endl;
    //construire le nouvel littérale
    Litterale* ptr;
    if (n1==n2)
        ptr = new Entier(1);
    else
        ptr = new Entier(0);

    return *ptr;
}


