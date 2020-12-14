//
// Created by Louis on 06/12/2020.
//

#include "Pile.h"


Item Pile::pop() {
    Item temporaire = listeItems.back();
    listeItems.pop_back();
    return temporaire;
}

void Pile::push(Item item) {
    listeItems.push_back(item);
}

bool Pile::estVide() {
    return taille()==0;
}

unsigned int Pile::taille() {
    return listeItems.size();
}

Pile &Pile::obtenirPile() {
    static Pile instance;
    return instance;
}