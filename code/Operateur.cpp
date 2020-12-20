//
// Created by Ismail Kadiri on 08/12/2020.
//

#include "Operateur.h"

//Initialisation de la map contenant les pointeurs des fonctions associés aux opérateurs d'arité 2
QMap<QString, function<Item(Item, Item)>> Operateur::inventaireOpArite2 = {

        {"+", opPlus},
        {"-", opMoins},
        {"=", opEgal}

};

//Initialisation de la map contenant les pointeurs des fonctions associés aux opérateurs d'arité 1
QMap<QString, function<Item(Item)>> Operateur::inventaireOpArite1 = {

        {"NEG", opNEG}
};

//Initialisation de la map contenant les pointeurs des fonctions associés aux opérateurs d'arité 2
QMap<QString, std::function<Item()>> Operateur::inventaireOpArite0 = {
};

Item Operateur::opPlus(Item i1, Item i2) {

    //On récupère les types des items i1 et i2
    QString typeItem1 = i1.obtenirType();
    QString typeItem2 = i2.obtenirType();

    std::cout << "type1 :" << typeItem1.toStdString() << std::endl;
    std::cout << "type2 :" << typeItem2.toStdString() << std::endl;

    //On vérifie que l'opération est réalisée sur des types valides
    if ( (typeItem1 != "Entier" && typeItem1 != "Reel" && typeItem1 != "Rationnel") && (typeItem2 != "Entier" && typeItem2 != "Reel" && typeItem2 != "Rationnel") )
        //throw ComputerException("Types des opérandes non valides pour l'opération");
        return Item(nullptr, "la d");
    else {

        //On récupère les valeurs stockées dans les items
        double valeur1;
        double valeur2;
        int num1=0, den1=0;
        int num2=0, den2=0;

        //On récupère la valeur du premier item
        if (typeItem1 == "Entier") {
            auto &litterale1 = dynamic_cast<Entier &>(i1.obtenirLitterale());
            valeur1 = static_cast<int>(litterale1.getEntier());
            num1 = valeur1;
            den1 = 1;
        }
        else if (typeItem1 == "Reel") {
            auto &litterale1 = dynamic_cast<Reel &>(i1.obtenirLitterale());
            valeur1 = litterale1.getReel();
        }

        else if (typeItem1 == "Rationnel") {
            auto &litterale1 = dynamic_cast<Rationnel &>(i1.obtenirLitterale());
            num1 = litterale1.getNumerateur();
            den1 = litterale1.getDenominateur();
        }
        else
            //throw ComputerException("Type non valide pour l'item 1");
            return Item(nullptr, "la merde");

        //On  récupère la valeur du 2ème item
        if (typeItem2 == "Entier") {
            auto &litterale2 = dynamic_cast<Entier &>(i2.obtenirLitterale());
            valeur2 = static_cast<int>(litterale2.getEntier());
            num2 = valeur2;
            den2 = 1;
        }
        else if (typeItem2 == "Reel") {
            auto &litterale2 = dynamic_cast<Reel &>(i2.obtenirLitterale());
            valeur2 = litterale2.getReel();
        }
        else if (typeItem2 == "Rationnel") {
            auto &litterale2 = dynamic_cast<Rationnel &>(i2.obtenirLitterale());
            num2 = litterale2.getNumerateur();
            den2 = litterale2.getDenominateur();
        }
        else
            //throw ComputerException("Type non valide pour l'item 2");
            return Item(nullptr, "la sauce");

        //On réalise le calcul correspondant, on construit le type de littérale correspondant et on le retourne

        //Si une des littérales est un réel, le résultat est un réel
        if (typeItem1 == "Reel" || typeItem2 == "Reel") {
            double resultat = valeur1 + valeur2;
            return ConstructeurLitterale::distinguerConstruire(QString::number(resultat));
        }

        //Si une des littérales est un rationnel, le résultat est un rationnel sauf si le denominateur est égal à 1
        else if (typeItem1 == "Rationnel" || typeItem2 == "Rationnel") {

            Rationnel r3(num1 * den2 + num2 * den1, den1 * den2);
            QString resultatString = QString::number(r3.getNumerateur()) + "/" + QString::number(r3.getDenominateur());
            return ConstructeurLitterale::distinguerConstruire(resultatString);

        }

        //Si les deux littérales sont des entiers, le résultat est donc un entier
        else if (typeItem1 == "Entier" && typeItem2 == "Entier") {
            int resultat = valeur1 + valeur2;
            return ConstructeurLitterale::distinguerConstruire(QString::number(resultat));
        }

    }

}


Item Operateur::opMoins(Item i1, Item i2) {
    //récupérer les types de i1 i2
    QString typeItem1 = i1.obtenirType();
    QString typeItem2 = i2.obtenirType();
    //tester les types
    //récupérer les valeurs stockées

    auto& l1 = dynamic_cast<Entier &>(i1.obtenirLitterale());
    auto& l2 = dynamic_cast<Entier &>(i2.obtenirLitterale());
    int n1 = l1.getEntier();
    cout << n1 << endl;
    int n2 = l2.getEntier();
    cout << n2 << endl;
    //construire le nouvel littérale

    auto resultat = n1 - n2;
    return ConstructeurLitterale::distinguerConstruire(QString::number(resultat));

}

Item Operateur::opNEG(Item i) {
    QString typeItem1 = i.obtenirType();
    //tester les types
    //récupérer les valeurs stockées

    auto& l = dynamic_cast<Entier &>(i.obtenirLitterale());
    int n = l.getEntier();
    cout << n << endl;

    //construire le nouvel littérale
    auto resultat = -n;
    return ConstructeurLitterale::distinguerConstruire(QString::number(resultat));
}

Item Operateur::opEgal(Item i1, Item i2) {
    //récupérer les types de i1 i2
    QString typeItem1 = i1.obtenirType();
    QString typeItem2 = i2.obtenirType();
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
    if (n1==n2){
        Item resultat = ConstructeurLitterale::distinguerConstruire(QString::number(1));
        return resultat;
    }
    else{
        Item resultat = ConstructeurLitterale::distinguerConstruire(QString::number(0));
        return resultat;
    }


}


