//
// Created by Ismail Kadiri on 08/12/2020.
//

#ifndef PROJET_LO21_OPERATEUR_H
#define PROJET_LO21_OPERATEUR_H

#include <iostream>
#include <QtCore/QString>
#include <QMap>
#include <functional>
#include "Litterale.h"
#include "Pile.h"
#include "Exception.h"

class Operateur {

private:

    Operateur();
    ~Operateur() noexcept;
    Operateur(const Operateur&) = delete;
    Operateur& operator=(const Operateur &) = delete;
    static bool typeValide(Item& i);
    static std::vector<double> recupererValeur(Item& i);


public:

    //Maps contenant les pointeurs de fonctions associés aux opérateurs d'arité respectivement 2,1 et 0
    static QMap<QString, function<Item(Item, Item)>> inventaireOpArite2;
    static QMap<QString, function<Item(Item)>> inventaireOpArite1;
    static QMap<QString, std::function<Item()>> inventaireOpArite0;


    //Design pattern singleton
    static auto& operateurInstance() {
        static Operateur opInstance;
        return opInstance;
    }

    //Méthodes opérateurs

    void opEval(Item i);

    //Operateurs Numeriques
    static Item opPlus(Item i1, Item i2);
    static Item opMoins(Item i1, Item i2);
    static Item opMul(Item i1, Item i2);
    static Item opDivision(Item i1, Item i2);
    static Item opDIV(Item i1, Item i2); //retourne le quotient de la division
    static Item opMOD(Item i1, Item i2); //retourne le reste de la division
    static Item opNEG(Item i); //transforme un nombre positif en négatif

    //Operateurs Logiques: retournent la littérale 0 si faux et la littérale 1 si vrai
    static Item opEgal(Item i1, Item i2);
    static Item opDifferent(Item i1, Item i2);
    static Item opInfEgal(Item i1, Item i2);
    static Item opSupEgal(Item i1, Item i2);
    static Item opSup(Item i1, Item i2);
    static Item opInf(Item i1, Item i2);
    static Item opAND(Item i1, Item i2);
    static Item opOR(Item i1, Item i2);
    static Item opNOT(Item i);

    //Operateurs de manipulation de la Pile
    static void opDUP(Item i); //retourne une copie de Litterale au haut de la pile
    static void opDROP(Item i); //supprime le premier Litterale dans la pile
    static void opSWAP(Item i1, Item i2); //intervertit les deux derniers éléments empilés dans la pile
    static void opCLEAR(); //vide tous les éléments de la pile

    //Operateurs conditionnels et de boucles
    static void opIFT(Item i1, Item i2); //test logique



};



#endif //PROJET_LO21_OPERATEUR_H

