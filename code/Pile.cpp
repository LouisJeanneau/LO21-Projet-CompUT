//
// Created by Louis on 06/12/2020.
//


#include "Pile.h"
//ITEM
Item::Item(Litterale *l, QString t) : litPointeur(l), typeItem(t) {
}

Item::Item(const Item &i) : litPointeur(i.litPointeur), typeItem(i.typeItem) {
}

Item &Item::operator=(const Item &i) {
    this->litPointeur = i.litPointeur;
    this->typeItem = i.typeItem;
    return *this;
}

void Item::supprimer() {
    delete litPointeur;
}

bool Item::operator==(const Item &i) {
    return this->litPointeur == i.litPointeur;
}

//PILE
void Pile::pop() {
    if (estVide())
        throw ComputerException("Erreur du pop, Pile vide");
    listeItems.pop_back();
}

Item Pile::end(int n) {
    if (estVide())
        throw ComputerException("Erreur du end, Pile vide");
    Item i = listeItems.at(listeItems.size() - n - 1);
    return i;
}

void Pile::push(Item item) {
    listeItems.push_back(item);
}

bool Pile::estVide() {
    return taille() == 0;
}

unsigned int Pile::taille() {
    return listeItems.size();
}

Pile &Pile::obtenirPile() {
    static Pile instance;
    return instance;
}

void Pile::modifierEtat(QString e) {
    etat = e;
}

QString Pile::obtenirEtat() {
    return etat;
}

std::vector<Item> Pile::copierListeItems() {
    return listeItems;
}

void Pile::clear() {
    try {
        for (auto it = listeItems.begin(); it != listeItems.end(); ++it)
            it->supprimer();
        listeItems.clear();
    } catch (ComputerException &ce) {
        throw ComputerException("Erreur lors du CLEAR de la pile");
    }
}

void Pile::swap() {
    try {
        Item itemTop = end();
        listeItems.pop_back();
        Item itemSecond = end();
        listeItems.pop_back();
        listeItems.push_back(itemTop);
        listeItems.push_back(itemSecond);
    } catch (ComputerException &ce) {
        throw ComputerException("Erreur lors du SWAP de la pile");
    }
}

void Pile::drop() {
    try {
        if (estVide()) {
            throw ComputerException("Erreur lors du DROP");
        }
        listeItems.back().supprimer();
        listeItems.pop_back();
    } catch (ComputerException &ce) {
        throw ComputerException("Erreur lors du DROP");

    }
}

void Pile::dup() {
    try {
        QString stringTemp = end().obtenirLitterale().versString();
        Item itemTemp = ConstructeurLitterale::distinguerConstruire(stringTemp);
        listeItems.push_back(itemTemp);
    } catch (ComputerException &ce) {
        throw ComputerException("Erreur lors du DUP");
    }
}

void Pile::debug() {
    cout << "La pile actuellement :" << endl;
    for (auto it = listeItems.begin(); it != listeItems.end(); it++) {
        cout << it->obtenirLitterale().versString().toStdString() << endl;
    }
}