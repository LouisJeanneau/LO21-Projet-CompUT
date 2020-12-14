//
// Created by Ismail Kadiri on 08/12/2020.
//

#ifndef PROJET_LO21_OPERATEUR_H
#define PROJET_LO21_OPERATEUR_H

#include <iostream>
#include <map>
#include <string>
#include "Pile.h"
#include <QtCore/QString>
#include <QMap>

class Operateur {

private:

    Operateur();
    ~Operateur() noexcept;


public:

    //Map contenant tous les opérateurs ainsi que leur arité
    static QMap<QString,int> inventaireOperateur;
    Operateur(const Operateur&) = delete;
    Operateur& operator=(const Operateur &) = delete;

    //Design pattern singleton
    static auto& operateurInstance() {
        static Operateur opInstance;
        return opInstance;

    }

    //Méthodes opérateurs

    // Étant donné que Opérateur s'occupe de dépiler les éléments dont elle a besoin et que
    // des éléments Item sont stockés dans la pile
    // Les paramètres d'entrée et de sortie des opérations seront également des items (dépend des cas)

    void opEval();

    //Operateurs Numeriques
    Item opPlus();
    Item opMoins();
    Item opMul();
    Item opDivision();
    Item opDIV(); //retourne le quotient de la division
    Item opMOD(); //retourne le reste de la division
    Item opNEG(Item i); //transforme un nombre positif en négatif

    //Operateurs Logiques: retournent la littérale 0 si faux et la littérale 1 si vrai
    Item opEgal();
    Item opDifferent();
    Item opInfEgal();
    Item opSupEgal();
    Item opSup();
    Item opInf();
    Item opAND();
    Item opOR();
    Item opNOT();

    //Operateurs de manipulation de la Pile
    Item opDUP(); //retourne une copie de l'item au haut de la pile
    void opDROP(); //supprime le premier item dans la pile
    void opSWAP(); //intervertit les deux derniers éléments empilés dans la pile
    void opCLEAR(); //vide tous les éléments de la pile

    //Operateurs conditionnels et de boucles
    void opIFT(); //test logique



};



#endif //PROJET_LO21_OPERATEUR_H

