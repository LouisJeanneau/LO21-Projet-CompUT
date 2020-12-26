//
// Created by Louis on 06/12/2020.
//

#include "Pile.h"


void Pile::pop() {
    listeItems.pop_back();
    modificationEtat("Pop réussi");
}

Item Pile::end(int n) {
    Item i=listeItems.at(listeItems.size()-n-1);
    return i;
}

void Pile::push(Item item) {
    listeItems.push_back(item);
    modificationEtat("Push d'un item réussi");
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

void Pile::debug() {
    cout << "La pile actuellement :" << endl;
    for(auto it=listeItems.begin(); it!=listeItems.end(); it++){
        cout << it->obtenirLitterale().versString().toStdString() << endl;
    }
}


