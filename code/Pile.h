//
// Created by Louis on 06/12/2020.
//

#ifndef LO21_PROJET_PILE_H
#define LO21_PROJET_PILE_H

#include <vector>
#include <QObject>
#include <string>
#include "Litterale.h"

using namespace std;

class Litterale;

class Item{
    Litterale* litPointeur;
    QString typeItem;
public:
    explicit Item(Litterale* l, QString t): litPointeur(l), typeItem(t){
        cout << "Construction défaut" << endl;
    }
    Item(const Item& i): litPointeur(i.litPointeur), typeItem(i.typeItem){
        cout << "Construction recopie" << endl;
    }
    Item& operator=(const Item& i){ this->litPointeur=i.litPointeur;
    this->typeItem = i.typeItem;
    cout << "Construction affectation" << endl;
    return *this;}
    ~Item(){
        cout << "Déstruction défaut" << endl;
    };
    void supprimer(){  }
    bool estVide(){
        if(litPointeur == nullptr){
            return true;
        }
        return false;
    }
    Litterale& obtenirLitterale(){return *litPointeur;}
    QString obtenirType() {return typeItem;}

};

class Pile : public QObject{
Q_OBJECT
    static Pile instance;
    Pile() = default;
    friend class vuePrincipale;
public:
    static Pile& obtenirPile();
    void pop();
    Item end(int n=0);
    void push(Item item);
    bool estVide();
    unsigned int taille();
    void debug();
    std::vector<Item> listeItems;
signals:
    void modificationEtat(QString etat);
};

#endif //LO21_PROJET_PILE_H
