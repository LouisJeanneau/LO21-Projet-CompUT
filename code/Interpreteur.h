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
    Persistence& persistence=Persistence::getPersistence();
    static Interpreteur instance;
    Interpreteur() = default;

public:
    void interprete(QString commandeEntree);
    void execute(QString operande);
    static Interpreteur& obtenirInterpreteur();
};

#endif //LO21_PROJET_INTERPRETER_H
