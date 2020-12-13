//
// Created by Louis on 06/12/2020.
//

#ifndef LO21_PROJET_PILE_H
#define LO21_PROJET_PILE_H

#include <vector>
#include <QObject>
#include "Litterale.h"

class Item{
    Litterale* litPointeur;
public:
    explicit Item(Litterale* l): litPointeur(l){}
    Litterale& obtenirLitterale(){return *litPointeur;}
};

class Pile : public QObject{
    std::vector<Item> listeItems;
public:
    Pile();
    Item pop();
    void push(Item item);
    bool estVide();
    unsigned int taille();
};

#endif //LO21_PROJET_PILE_H
