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
    virtual ~Litterale() = default;
    virtual QString versString() const = 0;


};

class Numerique:public Litterale{

};

class Reel : public Numerique{
    double reel;
public:
    explicit Reel(double d): reel(d) {};
    double obtenirReel() const {return reel;}
    void negative(){reel=-reel;};  
    QString versString() const;
    ~Reel() override = default;   
};

class Rationnel: public Numerique{
    int numerateur;
    int denominateur;
    void simplification();
    friend class Operateur;
public:
    int obtenirNumerateur()const{return numerateur;}
    int obtenirDenominateur()const{return denominateur;}
    void setRationnel(int n, int d);
    Rationnel(int n,int d) { setRationnel(n, d); }
    QString versString() const;
    ~Rationnel() = default;
    Rationnel operator+(const Rationnel & r) const;
};

class Entier : public Numerique{
    int entier;
public:
    Entier(int i): entier(i) {};
    int obtenirEntier()const {return entier;}
    QString versString() const;
    ~Entier() = default;
};

class Programme : public Litterale{
    QString programme;
    int delimitateur;
public:
    Programme(QString s) : programme(std::move(s)) {}
    QString obtenirProgramme()const {return programme;};
    ~Programme() = default;
    QString versString() const;
};


class Atome : public Litterale{
    QString atome;
    int delimitateur;
    int fonction=0; //indiquer le role joue:0:non associé（par defaut） 1 :identificateur de numerique 2:identificateur de programme
    Programme * p = nullptr;
    Numerique * n = nullptr; 
public:
    QString obtenirAtome()const {return atome;}
    int obtenirfonction ()const{return fonction;}
    void Associer(Programme* pro = nullptr,Numerique* nu = nullptr){
        if(pro!=nullptr)
        {
            fonction=2;
            p=pro;}
        if(nu!=nullptr)
        {
            fonction=1;
            n=nu;
        }//initialiser ou remplacer l'association
    }
    explicit Atome(QString s) : atome(std::move(s)) {}
    int siDejaIdentifi(){return fonction==1||fonction==2 ;}; 

    int siPredefini(QString a)//1:predefini,il faut rectifier
    {
        if(QString::compare(a,"DIV")||\
                QString::compare(a,"NEG")||\
                QString::compare(a,"AND")||\
                QString::compare(a,"OR")||\
                QString::compare(a,"NOT")||\
                QString::compare(a,"EVAL")||\
                QString::compare(a,"DUP")||\
                QString::compare(a,"DROP")||\
                QString::compare(a,"SWAP")||\
                QString::compare(a,"CLEAR")||\
                QString::compare(a,"IFT")||\
                QString::compare(a,"STO")||\
                QString::compare(a,"FORGET"))
            return 1;
        else return 0;
    }


    QString versString() const;
    ~Atome() {delete p;delete n;}
    void effacer(){p=nullptr;n=nullptr;}    //FORGET
};


class Expression : public Litterale{
    Atome * atome; 
public:
    Expression(Atome* a): atome(a) {};
    ~Expression() {
        delete atome;
    }

    QString versString() const;
};

class ConstructeurLitterale{
public:
    static Item distinguerConstruire(QString s);
};

#endif // LITTERAL_H


