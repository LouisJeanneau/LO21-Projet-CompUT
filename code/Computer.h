#ifndef _COMPUTER_H
#define _COMPUTER_H

#include <QString>
#include "Interpreter.h"
#include "Pile.h"
#include "Exception.h"

using namespace std;

class Controleur {
	Interpreter& refIntp;
	Pile& refPile;
    QString message;
public:
	Controleur(Interpreter& intp, Pile& p):refIntp(intp), refPile(p){}
    void commande(const QString& c) {refIntp.interprete(c);}
    void setMessage(const QString& m):message(m) {}
    QString getMessage() const { return message; }

};

#endif