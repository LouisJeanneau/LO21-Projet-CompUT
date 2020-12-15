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

class Operateur {

private:

    Operateur();
    ~Operateur() noexcept;
    Operateur(const Operateur&) = delete;
    Operateur& operator=(const Operateur &) = delete;


public:

    //Map contenant tous les opérateurs ainsi que leur arité
    static QMap<QString,int> inventaireOperateur;

    //Maps contenant les pointeurs de fonctions associés aux opérateurs d'arité respectivement 2,1 et 0
    static QMap<QString, function<Litterale&(Item, Item)>> inventaireOpArite2;
    static QMap<QString, function<Litterale&(Item)>> inventaireOpArite1;
    static QMap<QString, std::function<Litterale&()>> inventaireOpArite0;


    //Design pattern singleton
    static auto& operateurInstance() {
        static Operateur opInstance;
        return opInstance;
    }

    //Méthodes opérateurs

    void opEval(Item i);

    //Operateurs Numeriques
    static Litterale& opPlus(Item i1, Item i2);
    static Litterale& opMoins(Item i1, Item i2);
    static Litterale& opMul(Item i1, Item i2);
    static Litterale& opDivision(Item i1, Item i2);
    static Litterale& opDIV(Item i1, Item i2); //retourne le quotient de la division
    static Litterale& opMOD(Item i1, Item i2); //retourne le reste de la division
    static Litterale& opNEG(Item i); //transforme un nombre positif en négatif

    //Operateurs Logiques: retournent la littérale 0 si faux et la littérale 1 si vrai
    static Litterale& opEgal(Item i1, Item i2);
    static Litterale& opDifferent(Item i1, Item i2);
    static Litterale& opInfEgal(Item i1, Item i2);
    static Litterale& opSupEgal(Item i1, Item i2);
    static Litterale& opSup(Item i1, Item i2);
    static Litterale& opInf(Item i1, Item i2);
    static Litterale& opAND(Item i1, Item i2);
    static Litterale& opOR(Item i1, Item i2);
    static Litterale& opNOT(Item i1, Item i2);

    //Operateurs de manipulation de la Pile
    static Litterale& opDUP(Item i); //retourne une copie de l'Litterale au haut de la pile
    static void opDROP(Item i); //supprime le premier Litterale dans la pile
    static void opSWAP(Item i1, Item i2); //intervertit les deux derniers éléments empilés dans la pile
    static void opCLEAR(); //vide tous les éléments de la pile

    //Operateurs conditionnels et de boucles
    static void opIFT(Item i1, Item i2); //test logique



};



#endif //PROJET_LO21_OPERATEUR_H

