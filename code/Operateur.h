//
// Created by Ismail Kadiri on 08/12/2020.
//

#ifndef PROJET_LO21_OPERATEUR_H
#define PROJET_LO21_OPERATEUR_H

#include <iostream>
#include <map>
#include <string>
#include <QtCore/QString>
#include <QMap>
#include <functional>
#include "Litterale.h"
#include "Pile.h"

class Operateur {

private:

    Operateur();
    ~Operateur() noexcept;


public:
    //Map contenant tous les opérateurs ainsi que leur arité

    static QMap<QString,int> inventaireOperateur;

    static QMap<QString, std::function<Litterale(Item, Item)>> inventaireOpArite2;
    static QMap<QString, std::function<Litterale(Item)>> inventaireOpArite1;
    static QMap<QString, std::function<Litterale()>> inventaireOpArite0;

    Operateur(const Operateur&) = delete;
    Operateur& operator=(const Operateur &) = delete;

    //Design pattern singleton
    static auto& operateurInstance() {
        static Operateur opInstance;
        return opInstance;

    }

    //Méthodes opérateurs

    // Étant donné que Opérateur s'occupe de dépiler les éléments dont elle a besoin et que
    // des éléments Litterale sont stockés dans la pile
    // Les paramètres d'entrée et de sortie des opérations seront également des Litterales (dépend des cas)

    void opEval(Item i);

    //Operateurs Numeriques
    static Litterale opPlus(Item i1, Item i2);
    Litterale opMoins(Item i1, Item i2);
    Litterale opMul(Item i1, Item i2);
    Litterale opDivision(Item i1, Item i2);
    Litterale opDIV(Item i1, Item i2); //retourne le quotient de la division
    Litterale opMOD(Item i1, Item i2); //retourne le reste de la division
    static Litterale opNEG(Item i); //transforme un nombre positif en négatif

    //Operateurs Logiques: retournent la littérale 0 si faux et la littérale 1 si vrai
    Litterale opEgal(Item i1, Item i2);
    Litterale opDifferent(Item i1, Item i2);
    Litterale opInfEgal(Item i1, Item i2);
    Litterale opSupEgal(Item i1, Item i2);
    Litterale opSup(Item i1, Item i2);
    Litterale opInf(Item i1, Item i2);
    Litterale opAND(Item i1, Item i2);
    Litterale opOR(Item i1, Item i2);
    Litterale opNOT(Item i1, Item i2);

    //Operateurs de manipulation de la Pile
    Litterale opDUP(); //retourne une copie de l'Litterale au haut de la pile
    void opDROP(); //supprime le premier Litterale dans la pile
    void opSWAP(); //intervertit les deux derniers éléments empilés dans la pile
    void opCLEAR(); //vide tous les éléments de la pile

    //Operateurs conditionnels et de boucles
    void opIFT(Item i1, Item i2); //test logique



};



#endif //PROJET_LO21_OPERATEUR_H

