//
// Created by Ismail Kadiri on 08/12/2020.
//

#include "Operateur.h"
#include <cmath>

//Initialisation de la map contenant les pointeurs des fonctions associés aux opérateurs d'arité 2
QMap<QString, function<Item(Item&, Item&)>> Operateur::inventaireOpArite2 = {

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
        {"OR", opOR},
        {"POW", opPOW}

};

//Initialisation de la map contenant les pointeurs des fonctions associés aux opérateurs d'arité 1
QMap<QString, function<Item(Item&)>> Operateur::inventaireOpArite1 = {
        {"NEG", opNEG},
        {"NOT", opNOT},
        {"NUM", opNUM},
        {"DEN", opDEN},
        {"SQRT", opSQRT},
        {"EXP", opEXP},
        {"LN",opLN},
        {"SIN", opSIN},
        {"COS", opCOS},
        {"ARCSIN", opARCSIN},
        {"ARCCOS", opARCCOS},
        {"TAN", opTAN},
        {"ARCTAN", opARCTAN}

};


bool Operateur::typeNumerique(Item &i) {
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
        throw ComputerException("Type non valide pour l'item");

    return valeur;
}

bool Operateur::typeVariable(Item& i) {

    //On récupère une ref sur persistence
    Persistence& persistence=Persistence::getPersistence();

    QString litteraleString = i.obtenirLitterale().versString().remove(0,1);
    litteraleString.chop(1);

    if (persistence.getMapVariable().contains(litteraleString.toUpper()))
        return true;
    else
        return false;

}

Item Operateur::processVariable(Item& i) {

    //On récupère une ref sur la pile
    Pile& pile = Pile::obtenirPile();

    //On vérifie bien que l'item est une variable
    if (typeVariable(i)) {
        //On évalue i
        opEval(i);
        //On sauvegarde l'item résultant de l'évaluation de i
        Item res = pile.end();
        //On pop l'item résultant de l'évaluation de i
        pile.pop();
        //On renvoie le résultat de l'évaluation de i
        return res;
    }

    //Si l'item n'est pas une variable on renvoie l'item inchangé
    return i;

}


Item Operateur::opPlus(Item& i1, Item& i2) {

    //Si les items sont des expressions correspondantes à des variables, on remplace la variable par sa valeur stockée
    i1 = processVariable(i1);
    i2 = processVariable(i2);

    //On récupère les types des items i1 et i2 après le processVariable
    QString typeItem1 = i1.obtenirType();
    QString typeItem2 = i2.obtenirType();

    //On vérifie que l'opération est réalisée sur des types valides
    if (!typeNumerique(i1) && !typeNumerique(i2))
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

    throw ComputerException("Problème avec l'opérateur +");
}

Item Operateur::opMoins(Item& i1, Item& i2) {

    //Si les items sont des expressions correspondantes à des variables, on remplace la variable par sa valeur stockée
    i1 = processVariable(i1);
    i2 = processVariable(i2);

    //On récupère les types des items i1 et i2 après le processVariable
    QString typeItem1 = i1.obtenirType();
    QString typeItem2 = i2.obtenirType();

    //On vérifie que l'opération est réalisée sur des types valides
    if (!typeNumerique(i1) && !typeNumerique(i2))
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

    throw ComputerException("Problème avec l'opérateur -");

}

Item Operateur::opMul(Item& i1, Item& i2) {

    //Si les items sont des expressions correspondantes à des variables, on remplace la variable par sa valeur stockée
    i1 = processVariable(i1);
    i2 = processVariable(i2);

    //On récupère les types des items i1 et i2 après le processVariable
    QString typeItem1 = i1.obtenirType();
    QString typeItem2 = i2.obtenirType();

    //On vérifie que l'opération est réalisée sur des types valides
    if (!typeNumerique(i1) && !typeNumerique(i2))
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

    throw ComputerException("Problème avec l'opérateur *");
}

Item Operateur::opDivision(Item& i1, Item& i2) {

    //Si les items sont des expressions correspondantes à des variables, on remplace la variable par sa valeur stockée
    i1 = processVariable(i1);
    i2 = processVariable(i2);

    //On récupère les types des items i1 et i2 après le processVariable
    QString typeItem1 = i1.obtenirType();
    QString typeItem2 = i2.obtenirType();

    //On vérifie que l'opération est réalisée sur des types valides
    if (!typeNumerique(i1) && !typeNumerique(i2))
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

    throw ComputerException("Problème avec l'opérateur /");
}

Item Operateur::opDIV(Item& i1, Item& i2) {

    //Si les items sont des expressions correspondantes à des variables, on remplace la variable par sa valeur stockée
    i1 = processVariable(i1);
    i2 = processVariable(i2);

    //On récupère les types des items i1 et i2 après le processVariable
    QString typeItem1 = i1.obtenirType();
    QString typeItem2 = i2.obtenirType();

    //On vérifie que l'opération est réalisée sur des types valides
    if (!typeNumerique(i1) && !typeNumerique(i2))
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

Item Operateur::opMOD(Item& i1, Item& i2) {

    //Si les items sont des expressions correspondantes à des variables, on remplace la variable par sa valeur stockée
    i1 = processVariable(i1);
    i2 = processVariable(i2);

    //On récupère les types des items i1 et i2 après le processVariable
    QString typeItem1 = i1.obtenirType();
    QString typeItem2 = i2.obtenirType();

    //On vérifie que l'opération est réalisée sur des types valides
    if (!typeNumerique(i1) && !typeNumerique(i2))
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

Item Operateur::opNEG(Item& i) {

    //Si l'items est une expression correspondante à une variable; on remplace la variable par sa valeur stockée
    i = processVariable(i);

    //On récupère le type de i après processVariable
    QString typeItem = i.obtenirType();

    //On vérifie que l'opération est réalisée sur des types valides
    if (!typeNumerique(i))
        throw ComputerException("Types de l'opérande non valide");

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

    throw ComputerException("Problème avec l'opérateur NEG");

}

Item Operateur::opNUM(Item& i) {

    //Si l'items est une expression correspondante à une variable; on remplace la variable par sa valeur stockée
    i = processVariable(i);

    //On récupère le type de i après processVariable
    QString typeItem = i.obtenirType();

    //On vérifie que l'opération est réalisée sur des types valides
    if (!typeNumerique(i))
        throw ComputerException("Types de l'opérande non valide");

    else {

        //Si l'item est une expression correspondante à une variable, on remplace la variable par sa valeur stockée
        i = processVariable(i);

        //On récupére le type de i
        QString typeItem = i.obtenirType();

        //On récupére les valeurs stockées dans les items
        vector<double> valeurItem(2);

        //On récupére la valeur de l'item
        valeurItem = recupererValeur(i);

        if (typeItem == "Reel")
            throw ComputerException("Erreur: item réel");
        else
            return ConstructeurLitterale::distinguerConstruire(QString::number(valeurItem[0]));


    }

    throw ComputerException("Problème avec l'opérateur NUM");
}

Item Operateur::opDEN(Item& i) {

    //Si l'items est une expression correspondante à une variable; on remplace la variable par sa valeur stockée
    i = processVariable(i);

    //On récupère le type de i après processVariable
    QString typeItem = i.obtenirType();

    //On vérifie que l'opération est réalisée sur des types valides
    if (!typeNumerique(i))
        throw ComputerException("Types de l'opérande non valide");

    else {

        //Si l'item est une expression correspondante à une variable, on remplace la variable par sa valeur stockée
        i = processVariable(i);

        //On récupére le type de i
        QString typeItem = i.obtenirType();

        //On récupére les valeurs stockées dans les items
        vector<double> valeurItem(2);

        //On récupére la valeur de l'item
        valeurItem = recupererValeur(i);

        if (typeItem == "Reel")
            throw ComputerException("Erreur: item réel");
        else
            return ConstructeurLitterale::distinguerConstruire(QString::number(valeurItem[1]));


    }

    throw ComputerException("Problème avec l'opérateur DEN");
}

Item Operateur::opPOW(Item& i1, Item& i2) {

    //Si l'item est une expression correspondante à une variable, on remplace la variable par sa valeur stockée
    i1 = processVariable(i1);
    i2 = processVariable(i2);

    //On récupére le type de i1 et i2
    QString typeItem1 = i1.obtenirType();
    QString typeItem2 = i2.obtenirType();

    //On vérifie que l'opération est réalisée sur un type valide
    if (!typeNumerique(i1) && !typeNumerique(i2))
        throw ComputerException("Types des opérandes non valides");

    else {

        //On récupére les valeurs stockées dans les items
        vector<double> valeurItem1(2);
        vector<double> valeurItem2(2);


        //On récupére la valeur de l'item i1 et i2
        valeurItem1 = recupererValeur(i1);
        valeurItem2 = recupererValeur(i2);

        double base = valeurItem1[0]/valeurItem1[1];
        double puissance = valeurItem2[0]/valeurItem2[1];

        return ConstructeurLitterale::distinguerConstruire(QString::number(pow(base, puissance)));

    }

    throw ComputerException("Problème avec l'opérateur POW");
}

Item Operateur::opSQRT(Item& i) {

    //Si l'item est une expression correspondante à une variable, on remplace la variable par sa valeur stockée
    i = processVariable(i);

    //On récupére le type de i
    QString typeItem = i.obtenirType();

    //On vérifie que l'opération est réalisée sur un type valide
    if (!typeNumerique(i))
        throw ComputerException("Type de l'opérande non valide");

    else {

        //On récupére les valeurs stockées dans les items
        vector<double> valeurItem(2);

        //On récupére la valeur de l'item i
        valeurItem = recupererValeur(i);

        //On réalise le calcul de la valeur de littérale stockée dans i
        double res = valeurItem[0] / valeurItem[1];

        //Si la valeur n'est pas strictement positive on renvoit une erreur
        if (res <= 0)
            throw ComputerException("Opérande négative");

        else {
            //Si l'item n'est pas un rationnel on renvoit un réel
            if (typeItem != "Rationnel")
                return ConstructeurLitterale::distinguerConstruire(QString::number(sqrt(res)));

            //Si l'item est un rationnel, on vérifie que la racine carrée de son numérateur et de son dénominateur sont des entiers
            else {

                double num = sqrt(valeurItem[0]);

                //Si la racine carrée du numérateur n'est pas un entier, on renvoit un réel
                if (QString::number(num).contains("."))
                    return ConstructeurLitterale::distinguerConstruire(QString::number(sqrt(res)));
                else {

                    double den = sqrt(valeurItem[1]);

                    //Si la racine carrée du dénominateur n'est pas un entier on renvoie un réel
                    if (QString::number(den).contains("."))
                        return ConstructeurLitterale::distinguerConstruire(QString::number(sqrt(res)));

                    //À ce stade le numérateur et le dénominateur sont des entiers, on renvoit donc un rationnel
                    Rationnel r(num, den);
                    QString resultatString = QString::number(r.obtenirNumerateur()) + "/" + QString::number(r.obtenirDenominateur());
                    return ConstructeurLitterale::distinguerConstruire(resultatString);

                }

            }
        }

    }

    throw ComputerException("Problème avec l'opérateur SQRT");
}

Item Operateur::opEXP(Item& i) {

    //Si l'item est une expression correspondante à une variable, on remplace la variable par sa valeur stockée
    i = processVariable(i);

    //On récupére le type de i
    QString typeItem = i.obtenirType();

    //On vérifie que l'opération est réalisée sur un type valide
    if (!typeNumerique(i))
        throw ComputerException("Type de l'opérande non valide");

    else {

        //On récupére les valeurs stockées dans les items
        vector<double> valeurItem(2);

        //On récupére la valeur de l'item i
        valeurItem = recupererValeur(i);

        //On réalise le calcul de la valeur de littérale stockée dans i
        double res = valeurItem[0]/valeurItem[1];


        return ConstructeurLitterale::distinguerConstruire(QString::number(exp(res)));

    }

    throw ComputerException("Problème avec l'opérateur EXP");
}

Item Operateur::opLN(Item& i) {

    //Si l'item est une expression correspondante à une variable, on remplace la variable par sa valeur stockée
    i = processVariable(i);

    //On récupére le type de i
    QString typeItem = i.obtenirType();

    //On vérifie que l'opération est réalisée sur un type valide
    if (!typeNumerique(i))
        throw ComputerException("Type de l'opérande non valide");

    else {

        //On récupére les valeurs stockées dans les items
        vector<double> valeurItem(2);

        //On récupére la valeur de l'item i
        valeurItem = recupererValeur(i);

        //On réalise le calcul de la valeur de littérale stockée dans i
        double res = valeurItem[0]/valeurItem[1];

        //Si la valeur de la littérale est négative, on renvoit une erreur
        if (res <= 0)
            throw ComputerException("Opérande négative");
        else
            return ConstructeurLitterale::distinguerConstruire(QString::number(log(res)));

    }

    throw ComputerException("Problème avec l'opérateur LN");
}

Item Operateur::opSIN(Item& i) {

    //Si l'item est une expression correspondante à une variable, on remplace la variable par sa valeur stockée
    i = processVariable(i);

    //On récupére le type de i
    QString typeItem = i.obtenirType();

    //On vérifie que l'opération est réalisée sur un type valide
    if (!typeNumerique(i))
        throw ComputerException("Type de l'opérande non valide");

    else {

        //On récupére les valeurs stockées dans les items
        vector<double> valeurItem(2);

        //On récupére la valeur de l'item i
        valeurItem = recupererValeur(i);

        //On réalise le calcul de la valeur de littérale stockée dans i
        double res = valeurItem[0]/valeurItem[1];

        return ConstructeurLitterale::distinguerConstruire(QString::number(sin(res)));

    }

    throw ComputerException("Problème avec l'opérateur SIN");
}

Item Operateur::opCOS(Item& i) {

    //Si l'item est une expression correspondante à une variable, on remplace la variable par sa valeur stockée
    i = processVariable(i);

    //On récupére le type de i
    QString typeItem = i.obtenirType();

    //On vérifie que l'opération est réalisée sur un type valide
    if (!typeNumerique(i))
        throw ComputerException("Type de l'opérande non valide");

    else {

        //On récupére les valeurs stockées dans les items
        vector<double> valeurItem(2);

        //On récupére la valeur de l'item i
        valeurItem = recupererValeur(i);

        //On réalise le calcul de la valeur de littérale stockée dans i
        double res = valeurItem[0]/valeurItem[1];

        return ConstructeurLitterale::distinguerConstruire(QString::number(cos(res)));

    }

    throw ComputerException("Problème avec l'opérateur COS");
}

Item Operateur::opARCSIN(Item& i) {

    //Si l'item est une expression correspondante à une variable, on remplace la variable par sa valeur stockée
    i = processVariable(i);

    //On récupére le type de i
    QString typeItem = i.obtenirType();

    //On vérifie que l'opération est réalisée sur un type valide
    if (!typeNumerique(i))
        throw ComputerException("Type de l'opérande non valide");

    else {

        //On récupére les valeurs stockées dans les items
        vector<double> valeurItem(2);

        //On récupére la valeur de l'item i
        valeurItem = recupererValeur(i);

        //On réalise le calcul de la valeur de littérale stockée dans i
        double res = valeurItem[0]/valeurItem[1];

        if (res < -1 || res > 1)
            throw ComputerException("L'opérande n'est pas dans le domaine de définition de la fonction");
        else
            return ConstructeurLitterale::distinguerConstruire(QString::number(asin(res)));

    }

    throw ComputerException("Problème avec l'opérateur ARCSIN");
}

Item Operateur::opARCCOS(Item& i) {

    //Si l'item est une expression correspondante à une variable, on remplace la variable par sa valeur stockée
    i = processVariable(i);

    //On récupére le type de i
    QString typeItem = i.obtenirType();

    //On vérifie que l'opération est réalisée sur un type valide
    if (!typeNumerique(i))
        throw ComputerException("Type de l'opérande non valide");

    else {

        //On récupére les valeurs stockées dans les items
        vector<double> valeurItem(2);

        //On récupére la valeur de l'item i
        valeurItem = recupererValeur(i);

        //On réalise le calcul de la valeur de littérale stockée dans i
        double res = valeurItem[0]/valeurItem[1];

        if (res < -1 || res > 1)
            throw ComputerException("L'opérande n'est pas dans le domaine de définition de la fonction");
        else
            return ConstructeurLitterale::distinguerConstruire(QString::number(acos(res)));

    }

    throw ComputerException("Problème avec l'opérateur ARCCOS");
}

Item Operateur::opTAN(Item& i) {

    //Si l'item est une expression correspondante à une variable, on remplace la variable par sa valeur stockée
    i = processVariable(i);

    //On récupére le type de i
    QString typeItem = i.obtenirType();

    //On vérifie que l'opération est réalisée sur un type valide
    if (!typeNumerique(i))
        throw ComputerException("Type de l'opérande non valide");

    else {

        //On récupére les valeurs stockées dans les items
        vector<double> valeurItem(2);

        //On récupére la valeur de l'item i
        valeurItem = recupererValeur(i);

        //On réalise le calcul de la valeur de littérale stockée dans i
        double res = valeurItem[0]/valeurItem[1];

        return ConstructeurLitterale::distinguerConstruire(QString::number(tan(res)));

    }

    throw ComputerException("Problème avec l'opérateur TAN");
}

Item Operateur::opARCTAN(Item& i) {
    //Si l'item est une expression correspondante à une variable, on remplace la variable par sa valeur stockée
    i = processVariable(i);

    //On récupére le type de i
    QString typeItem = i.obtenirType();

    //On vérifie que l'opération est réalisée sur un type valide
    if (!typeNumerique(i))
        throw ComputerException("Type de l'opérande non valide");

    else {

        //On récupére les valeurs stockées dans les items
        vector<double> valeurItem(2);

        //On récupére la valeur de l'item i
        valeurItem = recupererValeur(i);

        //On réalise le calcul de la valeur de littérale stockée dans i
        double res = valeurItem[0]/valeurItem[1];

        return ConstructeurLitterale::distinguerConstruire(QString::number(atan(res)));

    }

    throw ComputerException("Problème avec l'opérateur ARCTAN");
}



Item Operateur::opEgal(Item& i1, Item& i2) {

    //Si les items sont des expressions correspondantes à des variables, on remplace la variable par sa valeur stockée
    i1 = processVariable(i1);
    i2 = processVariable(i2);

    //On récupère les types des items i1 et i2 après le processVariable
    QString typeItem1 = i1.obtenirType();
    QString typeItem2 = i2.obtenirType();

    //On vérifie que l'opération est réalisée sur des types valides
    if (!typeNumerique(i1) && !typeNumerique(i2))
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

Item Operateur::opDifferent(Item& i1, Item& i2) {

    //Si les items sont des expressions correspondantes à des variables, on remplace la variable par sa valeur stockée
    i1 = processVariable(i1);
    i2 = processVariable(i2);

    //On récupère les types des items i1 et i2 après le processVariable
    QString typeItem1 = i1.obtenirType();
    QString typeItem2 = i2.obtenirType();

    //On vérifie que l'opération est réalisée sur des types valides
    if (!typeNumerique(i1) && !typeNumerique(i2))
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

Item Operateur::opInfEgal(Item& i1, Item& i2) {

    //Si les items sont des expressions correspondantes à des variables, on remplace la variable par sa valeur stockée
    i1 = processVariable(i1);
    i2 = processVariable(i2);

    //On récupère les types des items i1 et i2 après le processVariable
    QString typeItem1 = i1.obtenirType();
    QString typeItem2 = i2.obtenirType();

    //On vérifie que l'opération est réalisée sur des types valides
    if (!typeNumerique(i1) && !typeNumerique(i2))
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

Item Operateur::opSupEgal(Item& i1, Item& i2) {

    //Si les items sont des expressions correspondantes à des variables, on remplace la variable par sa valeur stockée
    i1 = processVariable(i1);
    i2 = processVariable(i2);

    //On récupère les types des items i1 et i2 après le processVariable
    QString typeItem1 = i1.obtenirType();
    QString typeItem2 = i2.obtenirType();

    //On vérifie que l'opération est réalisée sur des types valides
    if (!typeNumerique(i1) && !typeNumerique(i2))
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

Item Operateur::opSup(Item& i1, Item& i2) {

    //Si les items sont des expressions correspondantes à des variables, on remplace la variable par sa valeur stockée
    i1 = processVariable(i1);
    i2 = processVariable(i2);

    //On récupère les types des items i1 et i2 après le processVariable
    QString typeItem1 = i1.obtenirType();
    QString typeItem2 = i2.obtenirType();

    //On vérifie que l'opération est réalisée sur des types valides
    if (!typeNumerique(i1) && !typeNumerique(i2))
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

Item Operateur::opInf(Item& i1, Item& i2) {

    //Si les items sont des expressions correspondantes à des variables, on remplace la variable par sa valeur stockée
    i1 = processVariable(i1);
    i2 = processVariable(i2);

    //On récupére les types des items i1 et i2
    QString typeItem1 = i1.obtenirType();
    QString typeItem2 = i2.obtenirType();

    //On vérifie que l'opération est réalisée sur des types valides
    if (!typeNumerique(i1) || !typeNumerique(i2))
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

Item Operateur::opAND(Item& i1, Item& i2) {

    //Si les items sont des expressions correspondantes à des variables, on remplace la variable par sa valeur stockée
    i1 = processVariable(i1);
    i2 = processVariable(i2);

    //On récupére les types des items i1 et i2
    QString typeItem1 = i1.obtenirType();
    QString typeItem2 = i2.obtenirType();

    //On vérifie que l'opération est réalisée sur des types valides
    if (!typeNumerique(i1) || !typeNumerique(i2))
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

Item Operateur::opOR(Item& i1, Item& i2) {

    //Si les items sont des expressions correspondantes à des variables, on remplace la variable par sa valeur stockée
    i1 = processVariable(i1);
    i2 = processVariable(i2);

    //On récupére les types des items i1 et i2
    QString typeItem1 = i1.obtenirType();
    QString typeItem2 = i2.obtenirType();

    //On vérifie que l'opération est réalisée sur des types valides
    if (!typeNumerique(i1) || !typeNumerique(i2))
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

Item Operateur::opNOT(Item& i) {

    //Si l'item est une expression correspondante à une variable, on remplace la variable par sa valeur stockée
    i = processVariable(i);

    //On récupére les types des items i1 et i2
    QString typeItem1 = i.obtenirType();

    //On vérifie que l'opération est réalisée sur des types valides
    if (!typeNumerique(i))
        throw ComputerException("Type de l'opérande non valide");

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

void Operateur::opEval(Item& i) {

    //On n'évalue qu'une expression ou un programme pour pas générer de problèmes
    if (i.obtenirType() != "Expression" && i.obtenirType() != "Programme")
        throw ComputerException("Évaluation d'un item n'étant ni une expression ni un programme");
    else {
        //On récupère une ref sur l'interpreteur
        Interpreteur& interpreteur = Interpreteur::obtenirInterpreteur();

        //On récupère la littérale pointée par l'item
        auto &litterale = i.obtenirLitterale();

        //On récupère la valeur stockée dans la littérale en une chaîne de caractère en retirant les délimitateurs '' ou []
        QString litteraleString = litterale.versString();
        litteraleString.chop(1);
        litteraleString.remove(0, 1);

        //On envoie la chaîne de caractère à l'interpreteur
        interpreteur.interprete(litteraleString);
    }
}

void Operateur::opIFT(Item& i1, Item& i2) {

    //On récupère une ref sur la pile
    Pile& pile = Pile::obtenirPile();

    //Si le premier item contient une littérale numérique, on réalise le test directement sur la valeur de la littérale
    if (typeNumerique(i1)) {

        //On récupère la valeur, et on la traite comme un réel (gère les cas d'entiers, rationnels, et réels)
        vector<double> valeurItem1 = recupererValeur(i1);
        double r1 = valeurItem1[0]/valeurItem1[1];

        //Si r1 est différent de 0 alors on évalue i2, sinon on ne l'évalue pas
        if (r1)
            opEval(i2);

    }

    else if (i1.obtenirType() == "Expression" || i1.obtenirType() == "Programme") {

        //On évalue le premier item
        opEval(i1);

        //On récupère l'item le plus haut de la pile suite à l'évaluation en le retirant de la pile
        Item res = pile.end();
        pile.pop();

        //On récupère la valeur, et on la traite comme un réel (gère les cas d'entiers, rationnels, et réels)
        vector<double> valeurItemRes = recupererValeur(res);
        double r2 = valeurItemRes[0]/valeurItemRes[1];

        //Si r1 est différent de 0 alors on évalue i2, sinon on ne l'évalue pas
        if (r2)
            opEval(i2);

        //Il faut liberer la mémoire alloué à la littérale qui était contenue dans l'item res, sinon la mémoire fuite
        res.supprimer();
    }
}

void Operateur::opIFTE(Item& i1, Item& i2, Item& i3) {

    //On récupère une ref sur la pile
    Pile& pile = Pile::obtenirPile();

    //Si le premier item contient une littérale numérique, on réalise le test directement sur la valeur de la littérale
    if (typeNumerique(i1)) {

        //On récupère la valeur, et on la traite comme un réel (gère les cas d'entiers, rationnels, et réels)
        vector<double> valeurItem1 = recupererValeur(i1);
        double r1 = valeurItem1[0]/valeurItem1[1];

        //Si r1 est différent de 0 alors on évalue i2, sinon évalue i3
        if (r1)
            opEval(i2);
        else
            opEval(i3);

    }

    else if (i1.obtenirType() == "Expression" || i1.obtenirType() == "Programme") {

        //On évalue le premier item
        opEval(i1);

        //On récupère l'item le plus haut de la pile suite à l'évaluation en le retirant de la pile
        Item res = pile.end();
        pile.pop();

        //On récupère la valeur, et on la traite comme un réel (gère les cas d'entiers, rationnels, et réels)
        vector<double> valeurItemRes = recupererValeur(res);
        double r2 = valeurItemRes[0]/valeurItemRes[1];

        //Si r1 est différent de 0 alors on évalue i2, sinon on évalue i3
        if (r2)
            opEval(i2);
        else
            opEval(i3);

        //Il faut liberer la mémoire alloué à la littérale qui était contenue dans l'item res, sinon la mémoire fuite
        res.supprimer();
    }

}

void Operateur::opWHILE(Item& i1, Item& i2) {

    //On récupère une ref sur la pile
    Pile& pile = Pile::obtenirPile();

    //Si le premier item contient une littérale numérique, on réalise le test directement sur la valeur de la littérale
    if (typeNumerique(i1)) {

        //On récupère la valeur, et on la traite comme un réel (gère les cas d'entiers, rationnels, et réels)
        vector<double> valeurItem1 = recupererValeur(i1);
        double r1 = valeurItem1[0]/valeurItem1[1];
        qDebug() << "r1 vaut " << r1;
        //Si r1 est différent de 0 alors on évalue i2, sinon évalue i3
        if (r1) {
            opEval(i2);
            opWHILE(i1, i2);
        }
    }

    else if (i1.obtenirType() == "Expression" || i1.obtenirType() == "Programme") {

        //On évalue le premier item
        opEval(i1);

        //On récupère l'item le plus haut de la pile suite à l'évaluation en le retirant de la pile
        Item res = pile.end();
        pile.pop();

        //On récupère la valeur, et on la traite comme un réel (gère les cas d'entiers, rationnels, et réels)
        vector<double> valeurItemRes = recupererValeur(res);
        double r2 = valeurItemRes[0]/valeurItemRes[1];

        //Si r1 est différent de 0 alors on évalue i2, sinon on évalue i3
        if (r2) {
            opEval(i2);
            opWHILE(i1,i2);
        }

        //Il faut liberer la mémoire alloué à la littérale qui était contenue dans l'item res, sinon la mémoire fuite
        res.supprimer();

    }


}

