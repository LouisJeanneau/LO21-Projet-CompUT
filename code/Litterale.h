//
// Created by Louis on 06/12/2020.
//

#ifndef PROJET_LO21_LITTERALE_H
#define PROJET_LO21_LITTERALE_H

#include <QString>
#include <QVector>
#include <utility>
#include <memory>

class Litterale;
class LitteraleNumeric;
class Entier;
class Reel;
class Rationnel;
class Complexe;
class Atome;
class Expression;
class Programme;
class FabriqueLitterale;

using namespace std;

class Litterale {
public:
    virtual ~Litterale() = default;
    virtual QString versString() const = 0;
};


class LitteraleNumerique : public Litterale {
public:
};


class Entier : public LitteraleNumerique {
private:
    int valeur;
public:
    explicit Entier(int n) : valeur(n) {}
    int obtenirValeur() const { return valeur; }
    QString versString() const override;
};


class Reel : public LitteraleNumerique {
private:
    double valeur;
public:
    explicit Reel(double n) : valeur(n) {}
    double obtenirValeur() const { return valeur; }
    QString versString() const override;
};


class Rationnel : public LitteraleNumerique {
private:
    int numerateur;
    int denominateur;
public:
    Rationnel(int n, int d) : numerateur(n), denominateur(d) {}
    int obtenirNumerateur() const { return numerateur; }
    int obtenirDenominateur() const { return denominateur; }
    QString versString() const override;
    void simplifier();
};


class Atome : public Litterale {
private:
    QString identificateur;
public:
    Atome(QString s) : identificateur(std::move(s)) {}
    QString obtenirIdentificateur() const { return identificateur; }
};


class Expression : public Litterale {
private:
    QString valeur;
public:
    explicit Expression(QString s) : valeur(std::move(s)) {}
    QString obtenirValeur() const { return valeur; }
};


class Programme : public Litterale {
private:
    QString valeur;
public:
    Programme(QString s) : valeur(std::move(s)) {}
    QString getValeur() const { return valeur; }
};


class FabriqueLitterale {
private:
    FabriqueLitterale() = default;
    ~FabriqueLitterale() = default;
    FabriqueLitterale(const FabriqueLitterale &fl) = delete;
    FabriqueLitterale& operator=(const FabriqueLitterale &fl) = delete;
    static FabriqueLitterale instance;

public:
    static FabriqueLitterale& obtenirInstance();

    //Fabriques
    Litterale *fabriquerLitterale(const QString &s);

    Litterale *fabriquerLitterale(Litterale &l);

    LitteraleNumeric *fabriquerLitNum(const QString &s);

    LitteraleNumeric *fabriquerLitNum(LitteraleNumeric &l);

    Litterale *fabriquerComplexe(const QString &s);

    Litterale *fabriquerComplexe(LitteraleNumeric *l1, LitteraleNumeric *l2);

    Atome *fabriquerAtome(const QString &s);

    Atome *fabriquerAtome(Atome &a);

    Expression *fabriquerExpression(const QString &s);

    Programme *fabriquerProgramme(const QString &s);

    Entier *fabriquer(const Entier &e);

    Entier *fabriquer(int valeur);

    Reel *fabriquer(const Reel &r);

    Reel *fabriquer(double valeur);

    Rationnel *fabriquer(const Rationnel &ra);

    //Rationnel* fabriquer(int num, int den);
    Complexe *fabriquer(const Complexe &c);

    Atome *fabriquer(const Atome &a);

    LitteraleNumeric *fabriquer/*Rationnel*/(int n, int d);
};

#endif //PROJET_LO21_LITTERALE_H
