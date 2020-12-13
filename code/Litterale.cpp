//
// Created by Louis on 06/12/2020.
//

#include "Litterale.h"


using namespace std;



int gcd(int a, int b)
{
    if (a == 0)
        return b;
    if (b == 0)
        return a;
    if (a == b)
        return a;
    if (a > b)
        return gcd(a-b, b);
    return gcd(a, b-a);
}

QString Entier::versString() const {
    return QString::number(valeur);
}

QString Reel::versString() const {
    return QString::number(valeur);
}

QString Rationnel::versString() const {
    return QString::number(numerateur)+QString::number(denominateur);
}

void Rationnel::simplifier() {
    int pgcd = gcd(numerateur, denominateur);
    numerateur/=pgcd;
    denominateur/=pgcd;
}

FabriqueLitterale &FabriqueLitterale::obtenirInstance() {
    static FabriqueLitterale instance;
    return instance;
}
