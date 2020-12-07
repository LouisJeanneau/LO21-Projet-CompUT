//
// Created by Louis on 06/12/2020.
//

#ifndef LO21_PROJET_INTERPRETER_H
#define LO21_PROJET_INTERPRETER_H

#include <QtCore/QString>
#include "Pile.h"
#include "Exception.h"

class Interpreteur{
    Pile* pointeurPile;
public:
    void interprete(QString commandeEntree);
    void execute(QString operande);
};

#endif //LO21_PROJET_INTERPRETER_H
