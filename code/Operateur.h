//
// Created by Ismail Kadiri on 08/12/2020.
//

#ifndef PROJET_LO21_OPERATEUR_H
#define PROJET_LO21_OPERATEUR_H

#include <QDebug>
#include <iostream>
#include <QtCore/QString>
#include <QMap>
#include <functional>
#include "Litterale.h"
#include "Pile.h"
#include "Exception.h"
#include "Interpreteur.h"
#include "Persistance.h"
#include <cmath>

class Operateur {

private:

    Operateur() = default;

    ~Operateur() noexcept = default;

    Operateur(const Operateur &) = delete;

    Operateur &operator=(const Operateur &) = delete;

    static bool typeNumerique(Item &i);

    static std::vector<double> recupererValeur(Item &i);

    static Item processVariable(Item &i);


public:

    //Maps contenant les pointeurs de fonctions associés aux opérateurs d'arité respectivement 2,1 et 0
    static QMap<QString, function<Item(Item &, Item &)>> inventaireOpArite2;
    static QMap<QString, function<Item(Item &)>> inventaireOpArite1;


    //Design pattern singleton
    static auto &operateurInstance() {
        static Operateur opInstance;
        return opInstance;
    }

    //Méthodes opérateurs

    static void opEval(Item &i);

    //Operateurs Numeriques
    static Item opPlus(Item &i1, Item &i2);

    static Item opMoins(Item &i1, Item &i2);

    static Item opMul(Item &i1, Item &i2);

    static Item opDivision(Item &i1, Item &i2);

    static Item opDIV(Item &i1, Item &i2);

    static Item opMOD(Item &i1, Item &i2);

    static Item opNEG(Item &i);

    //Opérateurs Numériques OPTIONNELS
    static Item opNUM(Item &i);

    static Item opDEN(Item &i);

    static Item opPOW(Item &i1, Item &i2);

    static Item opSQRT(Item &i);

    static Item opEXP(Item &i);

    static Item opLN(Item &i);

    static Item opSIN(Item &i);

    static Item opCOS(Item &i);

    static Item opARCSIN(Item &i);

    static Item opARCCOS(Item &i);

    static Item opTAN(Item &i);

    static Item opARCTAN(Item &i);


    //Operateurs Logiques: retournent la littérale 0 si faux et la littérale 1 si vrai
    static Item opEgal(Item &i1, Item &i2);

    static Item opDifferent(Item &i1, Item &i2);

    static Item opInfEgal(Item &i1, Item &i2);

    static Item opSupEgal(Item &i1, Item &i2);

    static Item opSup(Item &i1, Item &i2);

    static Item opInf(Item &i1, Item &i2);

    static Item opAND(Item &i1, Item &i2);

    static Item opOR(Item &i1, Item &i2);

    static Item opNOT(Item &i);


    //Operateurs conditionnels et de boucles
    static void opIFT(Item &i1, Item &i2); //test logique
    //Operateurs conditionnels OPTIONNELS
    static void opIFTE(Item &i1, Item &i2, Item &i3);

    static void opWHILE(Item &i1, Item &i2);


};

#endif //PROJET_LO21_OPERATEUR_H

