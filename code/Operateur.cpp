//
// Created by Ismail Kadiri on 08/12/2020.
//

#include "Operateur.h"
#include <cmath>

//Initialisation de la map contenant les pointeurs des fonctions associés aux opérateurs d'arité 2
QMap<QString, function<Item(Item, Item)>> Operateur::inventaireOpArite2 = {

        {"+", opPlus},
        {"-", opMoins},
        {"*", opMul},
        {"/", opDivision},
        {"DIV", opDIV},
        {"MOD", opMOD}

};

//Initialisation de la map contenant les pointeurs des fonctions associés aux opérateurs d'arité 1
QMap<QString, function<Item(Item)>> Operateur::inventaireOpArite1 = {
        {"NEG", opNEG}
};

//Initialisation de la map contenant les pointeurs des fonctions associés aux opérateurs d'arité 2
QMap<QString, std::function<Item()>> Operateur::inventaireOpArite0 = {
};


bool Operateur::typeValide(Item &i) {
    QString typeItem = i.obtenirType();
    if (typeItem != "Entier" && typeItem != "Reel" && typeItem != "Rationnel")
        return false;
    return true;
}

std::vector<double> Operateur::recupererValeur(Item &i) {

    QString typeItem = i.obtenirType();

    //On gère les valeurs dans un vector de taille 2 avec le numérateur et le dénominateur ( = 1 par défaut )
    vector<double> valeur(2);
    valeur[1] = 1;

    if (typeItem == "Entier") {
        auto &litterale1 = dynamic_cast<Entier &>(i.obtenirLitterale());
        valeur[0] = static_cast<int>(litterale1.getEntier());
    }
    else if (typeItem == "Reel") {
        auto &litterale1 = dynamic_cast<Reel &>(i.obtenirLitterale());
        valeur[0] = litterale1.getReel();
    }

    else if (typeItem == "Rationnel") {
        auto &litterale1 = dynamic_cast<Rationnel &>(i.obtenirLitterale());
        valeur[0] = litterale1.getNumerateur();
        valeur[1] = litterale1.getDenominateur();
    }
    else
        throw ComputerException("Type non valide pour l'item 1");

    return valeur;
}

Item Operateur::opPlus(Item i1, Item i2) {

    //On récupère les types des items i1 et i2
    QString typeItem1 = i1.obtenirType();
    QString typeItem2 = i2.obtenirType();

    //On vérifie que l'opération est réalisée sur des types valides
    if (!typeValide(i1) || !typeValide(i2))
        throw ComputerException("Types des opérandes non valides");

    else {

        //On récupère les valeurs stockées dans les items
        vector<double> valeurItem1(2);
        vector<double> valeurItem2(2);

        //On récupère la valeur du premier item
        valeurItem1 = recupererValeur(i1);

        //On  récupère la valeur du 2ème item
        valeurItem2 = recupererValeur(i2);

        //On réalise le calcul correspondant, on construit le type de littérale correspondant et on le retourne

        //Si une des littérales est un réel, le résultat est un réel
        if (typeItem1 == "Reel" || typeItem2 == "Reel") {

            double r1 = valeurItem1[0]/valeurItem1[1];
            double r2 = valeurItem2[0]/valeurItem2[1];

            return ConstructeurLitterale::distinguerConstruire(QString::number(r1 + r2));

        }

        //Si une des littérales est un rationnel, le résultat est un rationnel sauf si le denominateur est égal à 1
        else if (typeItem1 == "Rationnel" || typeItem2 == "Rationnel") {

            Rationnel r3(valeurItem1[0] * valeurItem2[1] + valeurItem2[0] * valeurItem1[1], valeurItem1[1] * valeurItem2[1]);
            QString resultatString = QString::number(r3.getNumerateur()) + "/" + QString::number(r3.getDenominateur());
            return ConstructeurLitterale::distinguerConstruire(resultatString);

        }

        //Si les deux littérales sont des entiers, le résultat est donc un entier
        else if (typeItem1 == "Entier" && typeItem2 == "Entier") {
            int resultat = valeurItem1[0] + valeurItem2[0];
            return ConstructeurLitterale::distinguerConstruire(QString::number(resultat));
        }

    }

}


Item Operateur::opMoins(Item i1, Item i2) {

    //On récupère les types des items i1 et i2
    QString typeItem1 = i1.obtenirType();
    QString typeItem2 = i2.obtenirType();

    //On vérifie que l'opération est réalisée sur des types valides
    if (!typeValide(i1) || !typeValide(i2))
        throw ComputerException("Types des opérandes non valides");

    else {

        //On récupère les valeurs stockées dans les items
        vector<double> valeurItem1(2);
        vector<double> valeurItem2(2);

        //On récupère la valeur du premier item
        valeurItem1 = recupererValeur(i1);

        //On  récupère la valeur du 2ème item
        valeurItem2 = recupererValeur(i2);

        //On réalise le calcul correspondant, on construit le type de littérale correspondant et on le retourne

        //Si une des littérales est un réel, le résultat est un réel
        if (typeItem1 == "Reel" || typeItem2 == "Reel") {

            double r1 = valeurItem1[0]/valeurItem1[1];
            double r2 = valeurItem2[0]/valeurItem2[1];

            return ConstructeurLitterale::distinguerConstruire(QString::number(r1 - r2));

        }

            //Si une des littérales est un rationnel, le résultat est un rationnel sauf si le denominateur est égal à 1
        else if (typeItem1 == "Rationnel" || typeItem2 == "Rationnel") {

            Rationnel r3(valeurItem1[0] * valeurItem2[1] - valeurItem2[0] * valeurItem1[1], valeurItem1[1] * valeurItem2[1]);
            QString resultatString = QString::number(r3.getNumerateur()) + "/" + QString::number(r3.getDenominateur());
            return ConstructeurLitterale::distinguerConstruire(resultatString);

        }

            //Si les deux littérales sont des entiers, le résultat est donc un entier
        else if (typeItem1 == "Entier" && typeItem2 == "Entier") {
            int resultat = valeurItem1[0] - valeurItem2[0];
            return ConstructeurLitterale::distinguerConstruire(QString::number(resultat));
        }

    }

}

Item Operateur::opMul(Item i1, Item i2) {

    //On récupère les types des items i1 et i2
    QString typeItem1 = i1.obtenirType();
    QString typeItem2 = i2.obtenirType();

    //On vérifie que l'opération est réalisée sur des types valides
    if (!typeValide(i1) || !typeValide(i2))
        throw ComputerException("Types des opérandes non valides");

    else {

        //On récupère les valeurs stockées dans les items
        vector<double> valeurItem1(2);
        vector<double> valeurItem2(2);

        //On récupère la valeur du premier item
        valeurItem1 = recupererValeur(i1);

        //On  récupère la valeur du 2ème item
        valeurItem2 = recupererValeur(i2);

        //On réalise le calcul correspondant, on construit le type de littérale correspondant et on le retourne

        //Si une des littérales est un réel, le résultat est un réel
        if (typeItem1 == "Reel" || typeItem2 == "Reel") {

            double r1 = valeurItem1[0]/valeurItem1[1];
            double r2 = valeurItem2[0]/valeurItem2[1];

            return ConstructeurLitterale::distinguerConstruire(QString::number(r1 * r2));

        }

        //Si une des littérales est un rationnel, le résultat est un rationnel sauf si le denominateur est égal à 1
        else if (typeItem1 == "Rationnel" || typeItem2 == "Rationnel") {

            Rationnel r3(valeurItem1[0] * valeurItem2[0], valeurItem1[1] * valeurItem2[1]);
            QString resultatString = QString::number(r3.getNumerateur()) + "/" + QString::number(r3.getDenominateur());
            return ConstructeurLitterale::distinguerConstruire(resultatString);

        }

        //Si les deux littérales sont des entiers, le résultat est donc un entier
        else if (typeItem1 == "Entier" && typeItem2 == "Entier") {
            int resultat = valeurItem1[0] * valeurItem2[0];
            return ConstructeurLitterale::distinguerConstruire(QString::number(resultat));
        }

    }
}

Item Operateur::opDivision(Item i1, Item i2) {

    //On récupère les types des items i1 et i2
    QString typeItem1 = i1.obtenirType();
    QString typeItem2 = i2.obtenirType();

    //On vérifie que l'opération est réalisée sur des types valides
    if (!typeValide(i1) || !typeValide(i2))
        throw ComputerException("Types des opérandes non valides");

    else {

        //On récupère les valeurs stockées dans les items
        vector<double> valeurItem1(2);
        vector<double> valeurItem2(2);

        //On récupère la valeur du premier item
        valeurItem1 = recupererValeur(i1);

        //On  récupère la valeur du 2ème item
        valeurItem2 = recupererValeur(i2);

        //On interdit les divisions par zéro
        if (valeurItem1[0] == 0 || valeurItem2[0] == 0)
            throw ComputerException("Division par zéro");

        //On réalise le calcul correspondant, on construit le type de littérale correspondant et on le retourne

        //Si une des littérales est un réel, le résultat est un réel
        if (typeItem1 == "Reel" || typeItem2 == "Reel") {

            double r1 = valeurItem1[0]/valeurItem1[1];
            double r2 = valeurItem2[0]/valeurItem2[1];

            return ConstructeurLitterale::distinguerConstruire(QString::number(r1/r2));

        }

        //Si une des littérales est un rationnel, le résultat est un rationnel sauf si le denominateur est égal à 1
        else if (typeItem1 == "Rationnel" || typeItem2 == "Rationnel") {

            Rationnel r3(valeurItem1[0] * valeurItem2[1], valeurItem1[1] * valeurItem2[0]);
            QString resultatString = QString::number(r3.getNumerateur()) + "/" + QString::number(r3.getDenominateur());
            return ConstructeurLitterale::distinguerConstruire(resultatString);

        }

        //Si les deux littérales sont des entiers, le résultat est donc un entier sauf si le reste n'est pas nul
        else if (typeItem1 == "Entier" && typeItem2 == "Entier") {

            int i1 = valeurItem1[0];
            int i2 = valeurItem2[0];

            if (i1%i2 != 0) {
                Rationnel r(valeurItem1[0], valeurItem2[0]);
                QString resultatString = QString::number(r.getNumerateur()) + "/" + QString::number(r.getDenominateur());
                return ConstructeurLitterale::distinguerConstruire(resultatString);
            }

            else
                return ConstructeurLitterale::distinguerConstruire(QString::number(i1/i2));
        }

    }
}

Item Operateur::opDIV(Item i1, Item i2) {

    //On récupère les types des items i1 et i2
    QString typeItem1 = i1.obtenirType();
    QString typeItem2 = i2.obtenirType();

    //On vérifie que l'opération est réalisée sur des types valides
    if (!typeValide(i1) || !typeValide(i2))
        throw ComputerException("Types des opérandes non valides");

    else {

        //On récupère les valeurs stockées dans les items
        vector<double> valeurItem1(2);
        vector<double> valeurItem2(2);

        //On récupère la valeur du premier item
        valeurItem1 = recupererValeur(i1);

        //On  récupère la valeur du 2ème item
        valeurItem2 = recupererValeur(i2);

        //On interdit les divisons par zéro
        if (valeurItem1[0] == 0 || valeurItem2[0] == 0)
            throw ComputerException("Division par zéro");

        //On réalise le calcul correspondant, on construit le type de littérale correspondant et on le retourne

        double r1 = valeurItem1[0]/valeurItem1[1];
        double r2 = valeurItem2[0]/valeurItem2[1];
        int quotient = r1/r2;

        return ConstructeurLitterale::distinguerConstruire(QString::number(quotient));

    }
}

Item Operateur::opMOD(Item i1, Item i2) {

    //On récupère les types des items i1 et i2
    QString typeItem1 = i1.obtenirType();
    QString typeItem2 = i2.obtenirType();

    //On vérifie que l'opération est réalisée sur des types valides
    if (!typeValide(i1) || !typeValide(i2))
        throw ComputerException("Types des opérandes non valides");

    else {

        //On récupère les valeurs stockées dans les items
        vector<double> valeurItem1(2);
        vector<double> valeurItem2(2);

        //On récupère la valeur du premier item
        valeurItem1 = recupererValeur(i1);

        //On  récupère la valeur du 2ème item
        valeurItem2 = recupererValeur(i2);

        //On interdit les divisons par zéro
        if (valeurItem1[0] == 0 || valeurItem2[0] == 0)
            throw ComputerException("Division par zéro");

        //On réalise le calcul correspondant, on construit le type de littérale correspondant et on le retourne

        double r1 = valeurItem1[0]/valeurItem1[1];
        double r2 = valeurItem2[0]/valeurItem2[1];

        //L'opérateur mod retourne un modulo toujours compris entre 0 (inclus) et le diviseur y (exclu) et qui a le même signe que le diviseur y
        double modulo = r1-(r2*floor(r1/r2));
        std::cout << modulo << "modulo" << std::endl;

        return ConstructeurLitterale::distinguerConstruire(QString::number(modulo));

    }
}

Item Operateur::opNEG(Item i) {

    //On récupère le type de l'item
    QString typeItem = i.obtenirType();

    //On vérifie que l'opération est réalisée sur un type valide
    if (!typeValide(i))
        throw ComputerException("Types des opérandes non valides");

    else {

        //On récupère la valeur stockée dans l'item
        vector<double> valeurItem(2);
        valeurItem = recupererValeur(i);

        //On réalise le calcul correspondant, on construit le type de littérale correspondant et on le retourne

        //Si la littérale est un réel ou un entier
        if (typeItem == "Reel" || typeItem == "Entier")
            return ConstructeurLitterale::distinguerConstruire(QString::number(-valeurItem[0]));

        //Si une des littérales est un rationnel, le résultat est un rationnel sauf si le denominateur est égal à 1
        else if (typeItem == "Rationnel") {

            Rationnel r3(-valeurItem[0], valeurItem[1]);
            QString resultatString = QString::number(r3.getNumerateur()) + "/" + QString::number(r3.getDenominateur());
            return ConstructeurLitterale::distinguerConstruire(resultatString);

        }

    }
}


