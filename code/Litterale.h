#ifndef LITTERAL_H
#define LITTERAL_H

#include <QString>
#include <iostream>
#include "Pile.h"
#include "Exception.h"

using namespace std;

class Item;

class Litterale {
public:
    virtual ~Litterale() {    }

    virtual QString versString() const = 0;


};

class Numerique : public Litterale {
public:
    Numerique() = default;

    ~Numerique() = default;
};

class Reel : public Numerique {
    double reel;
public:
    explicit Reel(double d) : reel(d) {};

    double obtenirReel() const { return reel; }

    QString versString() const;

    ~Reel() {
    }
};

class Rationnel : public Numerique {
    int numerateur;
    int denominateur;
public:
    Rationnel(int n, int d);

    int obtenirNumerateur() const { return numerateur; }

    int obtenirDenominateur() const { return denominateur; }

    QString versString() const;

    ~Rationnel() {
    }

    Rationnel operator+(const Rationnel &r) const;
};

class Entier : public Numerique {
    int entier;
public:
    Entier(int i) : entier(i) {};

    int obtenirEntier() const { return entier; }

    QString versString() const;

    ~Entier() {
    }
};

class Programme : public Litterale {
    QString programme;
public:
    Programme(QString s) : programme(std::move(s)) {}

    ~Programme() {}

    QString versString() const;
};

class Expression : public Litterale {
    QString expression;
public:
    Expression(QString e) : expression(e) {};

    QString versString() const;
};

class ConstructeurLitterale {
public:
    static Item distinguerConstruire(QString s);
};

#endif // LITTERAL_H


