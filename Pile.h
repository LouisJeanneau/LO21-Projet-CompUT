//
// Created by Louis on 06/12/2020.
//

#ifndef LO21_PROJET_PILE_H
#define LO21_PROJET_PILE_H

#include <vector>
#include "Litterale.h"

class Item{
    Litterale lit;
public:
    Litterale& obtenirLitterale(){return lit;}
};

class Pile{
    std::vector<Item> listeItems;
public:
    Item pop();
    void push(Item item);
    bool estVide();
    unsigned int taille();
};

#endif //LO21_PROJET_PILE_H
