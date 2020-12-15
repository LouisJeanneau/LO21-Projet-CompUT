//
// Created by Louis on 06/12/2020.
//

#ifndef LO21_PROJET_PILE_H
#define LO21_PROJET_PILE_H

#include <vector>
#include <QObject>
#include <string>
#include "Litterale.h"

class Item{
    Litterale* litPointeur;
    string typeItem;
public:
    explicit Item(Litterale* l): litPointeur(l){}
    ~Item() = default;
    void supprimer(){ delete litPointeur; }
    Litterale& obtenirLitterale(){return *litPointeur;}
    string obtenirType() {return typeItem;}

};

class Pile : public QObject{
    std::vector<Item> listeItems;
    static Pile instance;
    Pile() = default;
public:
    static Pile& obtenirPile();
    Item pop();
    void push(Item item);
    bool estVide();
    unsigned int taille();
};

#endif //LO21_PROJET_PILE_H
