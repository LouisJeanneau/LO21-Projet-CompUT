//
// Created by Lorenzo on 08/12/2020.
//

#ifndef PROJET_LO21_COMPUTER_H
#define PROJET_LO21_COMPUTER_H

#include <QString>
#include "Interpreteur.h"
#include "Pile.h"
#include "Persistance.h"
#include "Exception.h"

using namespace std;

class Controleur {
    Interpreteur &refIntp;
    Pile &refPile;
    QString message;
public:
    Controleur(Interpreteur &intp, Pile &p) : refIntp(intp), refPile(p) {}
    //void commande(const QString& c){refIntp.interpreter(c);}
    //void setMessage(const QString& m) {message = m;}
    //QString getMessage() const { return message; }

};

bool estUnOperateur(const QString s);

bool estUnNombre(const QString s);

#endif //PROJET_LO21_COMPUTER_H
