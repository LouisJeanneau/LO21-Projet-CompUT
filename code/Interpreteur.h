//
// Created by Louis on 06/12/2020.
//

#ifndef LO21_PROJET_INTERPRETER_H
#define LO21_PROJET_INTERPRETER_H

#include <QtCore/QString>
#include <functional>
#include "Pile.h"
#include "Exception.h"
#include "Operateur.h"
#include "Persistence.h"

class Interpreteur{
    Pile& pile=Pile::obtenirPile();
    Persistence& persistence= Persistence::obtenirPersistence();
    static Interpreteur instance;
    Interpreteur() = default;

public:
    void interpreter(QString commandeEntree);
    void executer(QString operande);
    static Interpreteur& obtenirInterpreteur();
};

#endif //LO21_PROJET_INTERPRETER_H
