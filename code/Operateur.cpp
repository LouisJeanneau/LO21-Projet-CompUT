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
        {"MOD", opMOD},
        {"=", opEgal},
        {"!=", opDifferent},
        {">=", opSupEgal},
        {">", opSup},
        {"<=", opInfEgal},
        {"<", opInf},
        {"AND", opAND},
        {"OR", opOR}

};

//Initialisation de la map contenant les pointeurs des fonctions associés aux opérateurs d'arité 1
QMap<QString, function<Item(Item)>> Operateur::inventaireOpArite1 = {
        {"NEG", opNEG},
        {"NOT", opNOT}
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
        valeur[0] = static_cast<int>(litterale1.obtenirEntier());
    }
    else if (typeItem == "Reel") {
        auto &litterale1 = dynamic_cast<Reel &>(i.obtenirLitterale());
        valeur[0] = litterale1.obtenirReel();
    }

    else if (typeItem == "Rationnel") {
        auto &litterale1 = dynamic_cast<Rationnel &>(i.obtenirLitterale());
        valeur[0] = litterale1.obtenirNumerateur();
        valeur[1] = litterale1.obtenirDenominateur();
    }
    else
        throw ComputerException("Type non valide pour l'item 1");

    return valeur;
}

Item Operateur::opPlus(Item i1, Item i2) {

    //On récupére les types des items i1 et i2
    QString typeItem1 = i1.obtenirType();
    QString typeItem2 = i2.obtenirType();

    //On vérifie que l'opération est réalisée sur des types valides
    if (!typeValide(i1) || !typeValide(i2))
        throw ComputerException("Types des opérandes non valides");

    else {

        //On récupére les valeurs stockées dans les items
        vector<double> valeurItem1(2);
        vector<double> valeurItem2(2);

        //On récupére la valeur du premier item
        valeurItem1 = recupererValeur(i1);

        //On  récupére la valeur du 2ème item
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
            QString resultatString = QString::number(r3.obtenirNumerateur()) + "/" + QString::number(r3.obtenirDenominateur());
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

    //On récupére les types des items i1 et i2
    QString typeItem1 = i1.obtenirType();
    QString typeItem2 = i2.obtenirType();

    //On vérifie que l'opération est réalisée sur des types valides
    if (!typeValide(i1) || !typeValide(i2))
        throw ComputerException("Types des opérandes non valides");

    else {

        //On récupére les valeurs stockées dans les items
        vector<double> valeurItem1(2);
        vector<double> valeurItem2(2);

        //On récupére la valeur du premier item
        valeurItem1 = recupererValeur(i1);

        //On  récupére la valeur du 2ème item
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
            QString resultatString = QString::number(r3.obtenirNumerateur()) + "/" + QString::number(r3.obtenirDenominateur());
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

    //On récupére les types des items i1 et i2
    QString typeItem1 = i1.obtenirType();
    QString typeItem2 = i2.obtenirType();

    //On vérifie que l'opération est réalisée sur des types valides
    if (!typeValide(i1) || !typeValide(i2))
        throw ComputerException("Types des opérandes non valides");

    else {

        //On récupére les valeurs stockées dans les items
        vector<double> valeurItem1(2);
        vector<double> valeurItem2(2);

        //On récupére la valeur du premier item
        valeurItem1 = recupererValeur(i1);

        //On  récupére la valeur du 2ème item
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
            QString resultatString = QString::number(r3.obtenirNumerateur()) + "/" + QString::number(r3.obtenirDenominateur());
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

    //On récupére les types des items i1 et i2
    QString typeItem1 = i1.obtenirType();
    QString typeItem2 = i2.obtenirType();

    //On vérifie que l'opération est réalisée sur des types valides
    if (!typeValide(i1) || !typeValide(i2))
        throw ComputerException("Types des opérandes non valides");

    else {

        //On récupére les valeurs stockées dans les items
        vector<double> valeurItem1(2);
        vector<double> valeurItem2(2);

        //On récupére la valeur du premier item
        valeurItem1 = recupererValeur(i1);

        //On  récupére la valeur du 2ème item
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
            QString resultatString = QString::number(r3.obtenirNumerateur()) + "/" + QString::number(r3.obtenirDenominateur());
            return ConstructeurLitterale::distinguerConstruire(resultatString);

        }

        //Si les deux littérales sont des entiers, le résultat est donc un entier sauf si le reste n'est pas nul
        else if (typeItem1 == "Entier" && typeItem2 == "Entier") {

            int i1 = valeurItem1[0];
            int i2 = valeurItem2[0];

            //Si le reste est nul, on retourne un entier, sinon on retourne un rationnel
            if (i1%i2 != 0) {
                Rationnel r(valeurItem1[0], valeurItem2[0]);
                QString resultatString = QString::number(r.obtenirNumerateur()) + "/" + QString::number(r.obtenirDenominateur());
                return ConstructeurLitterale::distinguerConstruire(resultatString);
            }

            else
                return ConstructeurLitterale::distinguerConstruire(QString::number(i1/i2));
        }

    }
}

Item Operateur::opDIV(Item i1, Item i2) {

    //On récupére les types des items i1 et i2
    QString typeItem1 = i1.obtenirType();
    QString typeItem2 = i2.obtenirType();

    //On vérifie que l'opération est réalisée sur des types valides
    if (!typeValide(i1) || !typeValide(i2))
        throw ComputerException("Types des opérandes non valides");

    else {

        //On récupére les valeurs stockées dans les items
        vector<double> valeurItem1(2);
        vector<double> valeurItem2(2);

        //On récupére la valeur du premier item
        valeurItem1 = recupererValeur(i1);

        //On  récupére la valeur du 2ème item
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

    //On récupére les types des items i1 et i2
    QString typeItem1 = i1.obtenirType();
    QString typeItem2 = i2.obtenirType();

    //On vérifie que l'opération est réalisée sur des types valides
    if (!typeValide(i1) || !typeValide(i2))
        throw ComputerException("Types des opérandes non valides");

    else {

        //On récupére les valeurs stockées dans les items
        vector<double> valeurItem1(2);
        vector<double> valeurItem2(2);

        //On récupére la valeur du premier item
        valeurItem1 = recupererValeur(i1);

        //On  récupére la valeur du 2ème item
        valeurItem2 = recupererValeur(i2);

        //On interdit les divisons par zéro
        if (valeurItem1[0] == 0 || valeurItem2[0] == 0)
            throw ComputerException("Division par zéro");

        //On traite les entiers, réels et rationnels comme des réels

        double r1 = valeurItem1[0]/valeurItem1[1];
        double r2 = valeurItem2[0]/valeurItem2[1];

        //L'opérateur mod retourne un modulo toujours compris entre 0 (inclus) et le diviseur y (exclu) et qui a le même signe que le diviseur y
        double modulo = r1-(r2*floor(r1/r2));
        std::cout << modulo << "modulo" << std::endl;

        return ConstructeurLitterale::distinguerConstruire(QString::number(modulo));

    }
}

Item Operateur::opNEG(Item i) {

    //On récupére le type de l'item
    QString typeItem = i.obtenirType();

    //On vérifie que l'opération est réalisée sur un type valide
    if (!typeValide(i))
        throw ComputerException("Types des opérandes non valides");

    else {

        //On récupére la valeur stockée dans l'item
        vector<double> valeurItem(2);
        valeurItem = recupererValeur(i);

        //On réalise le calcul correspondant, on construit le type de littérale correspondant et on le retourne

        //Si la littérale est xun réel ou un entier
        if (typeItem == "Reel" || typeItem == "Entier")
            return ConstructeurLitterale::distinguerConstruire(QString::number(-valeurItem[0]));

        //Si une des littérales est un rationnel, le résultat est un rationnel sauf si le denominateur est égal à 1
        else if (typeItem == "Rationnel") {

            Rationnel r3(-valeurItem[0], valeurItem[1]);
            QString resultatString = QString::number(r3.obtenirNumerateur()) + "/" + QString::number(r3.obtenirDenominateur());
            return ConstructeurLitterale::distinguerConstruire(resultatString);

        }

    }
}

Item Operateur::opEgal(Item i1, Item i2) {

    //On récupére les types des items i1 et i2
    QString typeItem1 = i1.obtenirType();
    QString typeItem2 = i2.obtenirType();

    //On vérifie que l'opération est réalisée sur des types valides
    if (!typeValide(i1) || !typeValide(i2))
        throw ComputerException("Types des opérandes non valides");

    else {

        //On récupére les valeurs stockées dans les items
        vector<double> valeurItem1(2);
        vector<double> valeurItem2(2);

        //On récupére la valeur du premier item
        valeurItem1 = recupererValeur(i1);

        //On  récupére la valeur du 2ème item
        valeurItem2 = recupererValeur(i2);

        //On traite les entiers, réels et rationnels comme des réels

        double r1 = valeurItem1[0]/valeurItem1[1];
        double r2 = valeurItem2[0]/valeurItem2[1];

        //Si l'opération d'égalité est vérifiée on renvoit la littérale 1 sinon la littérale 0

        if (r1 == r2)
            return ConstructeurLitterale::distinguerConstruire(QString::number(1));
        else
            return ConstructeurLitterale::distinguerConstruire(QString::number(0));

    }
}

Item Operateur::opDifferent(Item i1, Item i2) {
    //On récupére les types des items i1 et i2
    QString typeItem1 = i1.obtenirType();
    QString typeItem2 = i2.obtenirType();

    //On vérifie que l'opération est réalisée sur des types valides
    if (!typeValide(i1) || !typeValide(i2))
        throw ComputerException("Types des opérandes non valides");

    else {

        //On récupére les valeurs stockées dans les items
        vector<double> valeurItem1(2);
        vector<double> valeurItem2(2);

        //On récupére la valeur du premier item
        valeurItem1 = recupererValeur(i1);

        //On  récupére la valeur du 2ème item
        valeurItem2 = recupererValeur(i2);

        //On traite les entiers, réels et rationnels comme des réels

        double r1 = valeurItem1[0]/valeurItem1[1];
        double r2 = valeurItem2[0]/valeurItem2[1];

        //Si l'opération de différence est vérifiée on renvoit la littérale 1 sinon la littérale 0

        if (r1 != r2)
            return ConstructeurLitterale::distinguerConstruire(QString::number(1));
        else
            return ConstructeurLitterale::distinguerConstruire(QString::number(0));

    }
}

Item Operateur::opInfEgal(Item i1, Item i2) {

    //On récupére les types des items i1 et i2
    QString typeItem1 = i1.obtenirType();
    QString typeItem2 = i2.obtenirType();

    //On vérifie que l'opération est réalisée sur des types valides
    if (!typeValide(i1) || !typeValide(i2))
        throw ComputerException("Types des opérandes non valides");

    else {

        //On récupére les valeurs stockées dans les items
        vector<double> valeurItem1(2);
        vector<double> valeurItem2(2);

        //On récupére la valeur du premier item
        valeurItem1 = recupererValeur(i1);

        //On  récupére la valeur du 2ème item
        valeurItem2 = recupererValeur(i2);

        //On traite les entiers, réels et rationnels comme des réels

        double r1 = valeurItem1[0]/valeurItem1[1];
        double r2 = valeurItem2[0]/valeurItem2[1];

        //Si l'opération inférieure ou égale est vérifiée on renvoit la littérale 1 sinon la littérale 0

        if (r1 <= r2)
            return ConstructeurLitterale::distinguerConstruire(QString::number(1));
        else
            return ConstructeurLitterale::distinguerConstruire(QString::number(0));

    }
}

Item Operateur::opSupEgal(Item i1, Item i2) {

    //On récupére les types des items i1 et i2
    QString typeItem1 = i1.obtenirType();
    QString typeItem2 = i2.obtenirType();

    //On vérifie que l'opération est réalisée sur des types valides
    if (!typeValide(i1) || !typeValide(i2))
        throw ComputerException("Types des opérandes non valides");

    else {

        //On récupére les valeurs stockées dans les items
        vector<double> valeurItem1(2);
        vector<double> valeurItem2(2);

        //On récupére la valeur du premier item
        valeurItem1 = recupererValeur(i1);

        //On  récupére la valeur du 2ème item
        valeurItem2 = recupererValeur(i2);

        //On traite les entiers, réels et rationnels comme des réels

        double r1 = valeurItem1[0]/valeurItem1[1];
        double r2 = valeurItem2[0]/valeurItem2[1];

        //Si l'opération supérieur ou égale est vérifiée on renvoit la littérale 1 sinon la littérale 0

        if (r1 >= r2)
            return ConstructeurLitterale::distinguerConstruire(QString::number(1));
        else
            return ConstructeurLitterale::distinguerConstruire(QString::number(0));

    }
}

Item Operateur::opSup(Item i1, Item i2) {
    //On récupére les types des items i1 et i2
    QString typeItem1 = i1.obtenirType();
    QString typeItem2 = i2.obtenirType();

    //On vérifie que l'opération est réalisée sur des types valides
    if (!typeValide(i1) || !typeValide(i2))
        throw ComputerException("Types des opérandes non valides");

    else {

        //On récupére les valeurs stockées dans les items
        vector<double> valeurItem1(2);
        vector<double> valeurItem2(2);

        //On récupére la valeur du premier item
        valeurItem1 = recupererValeur(i1);

        //On  récupére la valeur du 2ème item
        valeurItem2 = recupererValeur(i2);

        //On traite les entiers, réels et rationnels comme des réels

        double r1 = valeurItem1[0]/valeurItem1[1];
        double r2 = valeurItem2[0]/valeurItem2[1];

        //Si l'opération supérieure est vérifiée on renvoit la littérale 1 sinon la littérale 0

        if (r1 > r2)
            return ConstructeurLitterale::distinguerConstruire(QString::number(1));
        else
            return ConstructeurLitterale::distinguerConstruire(QString::number(0));

    }
}

Item Operateur::opInf(Item i1, Item i2) {
    //On récupére les types des items i1 et i2
    QString typeItem1 = i1.obtenirType();
    QString typeItem2 = i2.obtenirType();

    //On vérifie que l'opération est réalisée sur des types valides
    if (!typeValide(i1) || !typeValide(i2))
        throw ComputerException("Types des opérandes non valides");

    else {

        //On récupére les valeurs stockées dans les items
        vector<double> valeurItem1(2);
        vector<double> valeurItem2(2);

        //On récupére la valeur du premier item
        valeurItem1 = recupererValeur(i1);

        //On  récupére la valeur du 2ème item
        valeurItem2 = recupererValeur(i2);

        //On traite les entiers, réels et rationnels comme des réels

        double r1 = valeurItem1[0]/valeurItem1[1];
        double r2 = valeurItem2[0]/valeurItem2[1];

        //Si l'opération inférieure est vérifiée on renvoit la littérale 1 sinon la littérale 0

        if (r1 < r2)
            return ConstructeurLitterale::distinguerConstruire(QString::number(1));
        else
            return ConstructeurLitterale::distinguerConstruire(QString::number(0));

    }
}

Item Operateur::opAND(Item i1, Item i2) {
    //On récupére les types des items i1 et i2
    QString typeItem1 = i1.obtenirType();
    QString typeItem2 = i2.obtenirType();

    //On vérifie que l'opération est réalisée sur des types valides
    if (!typeValide(i1) || !typeValide(i2))
        throw ComputerException("Types des opérandes non valides");

    else {

        //On récupére les valeurs stockées dans les items
        vector<double> valeurItem1(2);
        vector<double> valeurItem2(2);

        //On récupére la valeur du premier item
        valeurItem1 = recupererValeur(i1);

        //On  récupére la valeur du 2ème item
        valeurItem2 = recupererValeur(i2);

        //On traite les entiers, réels et rationnels comme des réels

        double r1 = valeurItem1[0]/valeurItem1[1];
        double r2 = valeurItem2[0]/valeurItem2[1];

        //Si l'opération AND est vérifiée on renvoit la littérale 1 sinon la littérale 0

        if (r1 && r2)
            return ConstructeurLitterale::distinguerConstruire(QString::number(1));
        else
            return ConstructeurLitterale::distinguerConstruire(QString::number(0));

    }
}

Item Operateur::opOR(Item i1, Item i2) {

    //On récupére les types des items i1 et i2
    QString typeItem1 = i1.obtenirType();
    QString typeItem2 = i2.obtenirType();

    //On vérifie que l'opération est réalisée sur des types valides
    if (!typeValide(i1) || !typeValide(i2))
        throw ComputerException("Types des opérandes non valides");

    else {

        //On récupére les valeurs stockées dans les items
        vector<double> valeurItem1(2);
        vector<double> valeurItem2(2);

        //On récupére la valeur du premier item
        valeurItem1 = recupererValeur(i1);

        //On  récupére la valeur du 2ème item
        valeurItem2 = recupererValeur(i2);

        //On traite les entiers, réels et rationnels comme des réels

        double r1 = valeurItem1[0]/valeurItem1[1];
        double r2 = valeurItem2[0]/valeurItem2[1];

        //Si l'opération OR est vérifiée on renvoit la littérale 1 sinon la littérale 0

        if (r1 || r2)
            return ConstructeurLitterale::distinguerConstruire(QString::number(1));
        else
            return ConstructeurLitterale::distinguerConstruire(QString::number(0));

    }
}

Item Operateur::opNOT(Item i) {

    //On récupére les types des items i1 et i2
    QString typeItem1 = i.obtenirType();

    //On vérifie que l'opération est réalisée sur des types valides
    if (!typeValide(i))
        throw ComputerException("Types des opérandes non valides");

    else {

        //On récupére la valeur stockée dans l'item
        vector<double> valeurItem(2);

        //On récupére la valeur de l'item
        valeurItem = recupererValeur(i);

        //On traite les entiers, réels et rationnels comme des réels

        double r = valeurItem[0]/valeurItem[1];

        //Si l'opération NOT est vérifiée on renvoit la littérale 1 sinon la littérale 0

        if (!r)
            return ConstructeurLitterale::distinguerConstruire(QString::number(1));
        else
            return ConstructeurLitterale::distinguerConstruire(QString::number(0));

    }}


