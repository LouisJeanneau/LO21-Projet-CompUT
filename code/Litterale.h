#ifndef LITTERAL_H
#define LITTERAL_H

#include <QString>
#include <iostream>
#include "code/Pile.h"
#include "code/Exception.h"

using namespace std;

class Item;

class Litterale {
public:
    virtual ~Litterale() {
        cout << "Litterale detruite" << endl;
    }
    virtual QString versString() const = 0;


};

class Numerique:public Litterale{
public:
    Numerique() = default;
    ~Numerique() = default;
};

class Reel : public Numerique{
    double reel;
public:
    explicit Reel(double d): reel(d) {};
    double obtenirReel() const {return reel;}
    void negative(){reel=-reel;};  
    QString versString() const;
    ~Reel() {
        cout << "Reel detruite" << endl;
    }
};

class Rationnel: public Numerique{
    int numerateur;
    int denominateur;
    void simplification();
public:
    int obtenirNumerateur()const{return numerateur;}
    int obtenirDenominateur()const{return denominateur;}
    void setRationnel(int n, int d);
    Rationnel(int n,int d) { setRationnel(n, d); }
    QString versString() const;
    ~Rationnel() {
        cout << "Rationnel detruite" << endl;
    }
    Rationnel operator+(const Rationnel & r) const;
};

class Entier : public Numerique{
    int entier;
public:
    Entier(int i): entier(i) {};
    int obtenirEntier()const {return entier;}
    QString versString() const;
    ~Entier() {
        cout << "Entier detruit" << endl;
    }
};

class Programme : public Litterale{
    QString programme;
public:
    Programme(QString s) : programme(std::move(s)) {}
    ~Programme() {
        cout << "Programme detruit" << endl;
    }
    QString versString() const;
};

class Expression : public Litterale{
    QString expression;
public:
    Expression(QString e): expression(e) {};
    ~Expression() {
    }
    QString versString() const;
};

class ConstructeurLitterale{
public:
    static Item distinguerConstruire(QString s);
};

#endif // LITTERAL_H


