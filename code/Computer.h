//
// Created by Lorenzo on 08/12/2020.
//

#ifndef PROJET_LO21_COMPUTER_H
#define PROJET_LO21_COMPUTER_H

#include <QString>
#include "Interpreteur.h"
#include "Pile.h"
#include "persistence.h"
#include "Exception.h"

using namespace std;

class Controleur {
	Interpreteur& refIntp;
	Pile& refPile;
    Persistence& refPers;
    QString message;
public:
	Controleur(Interpreteur& intp, Pile& p, Persistance& pers):refIntp(intp), refPile(p), refPers(pers){}
    void commande(const QString& c) {refIntp.interprete(c);}
    void setMessage(const QString& m) {message = m;}
    QString getMessage() const { return message; }
    void sauvegardeEtat();
    void recupereEtat();

};

#endif //PROJET_LO21_COMPUTER_H