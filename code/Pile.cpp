//
// Created by Louis on 06/12/2020.
//


#include "Pile.h"

Item::Item(Litterale *l, QString t) : litPointeur(l), typeItem(t){
    cout << "Construction defaut" << endl;
}

Item::Item(const Item &i) : litPointeur(i.litPointeur), typeItem(i.typeItem) {
    cout << "Construction recopie" << endl;
}

Item &Item::operator=(const Item &i) {
    this->litPointeur = i.litPointeur;
    this->typeItem = i.typeItem;
    cout << "Construction affectation" << endl;
    return *this;
}


void Pile::pop() {
    if(estVide())
        throw ComputerException("Echec du pop, Pile vide");
    listeItems.pop_back();
    modifierEtat("Pop réussi");
}

Item Pile::end(int n) {
    if(estVide())
        throw ComputerException("Echec du end, Pile vide");
    Item i=listeItems.at(listeItems.size()-n-1);
    return i;
}

void Pile::push(Item item) {
    listeItems.push_back(item);
    modifierEtat("Push d'un item réussi");
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

void Pile::modifierEtat(QString e) {
    etat=e;
    emit refresh();
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
        modifierEtat("Pile vidée");
    } catch (ComputerException &ce) {
        modifierEtat("Erreur lors du clear de la pile");
    }
}

void Pile::swap() {
    try{
        Item itemTop = end();
        listeItems.pop_back();
        Item itemSecond = end();
        listeItems.pop_back();
        listeItems.push_back(itemTop);
        listeItems.push_back(itemSecond);
        modifierEtat("Swap réussi");
    } catch (ComputerException &ce) {
        modifierEtat("Erreur lors du swap de la pile");
    }
}

void Pile::drop() {
    try{
        if(estVide()){
            modifierEtat("Erreur lors du drop");
            return;
        }
        listeItems.back().supprimer();
        listeItems.pop_back();
        modifierEtat("Drop réussi");
    } catch (ComputerException &ce) {
        modifierEtat("Erreur lors du drop");
    }
}

void Pile::dup() {
    try{
        QString stringTemp = end().obtenirLitterale().versString();
        Item itemTemp = ConstructeurLitterale::distinguerConstruire(stringTemp);
        listeItems.push_back(itemTemp);
        modifierEtat("Dup réussi");
    } catch (ComputerException &ce) {
        modifierEtat("Erreur lors du dup");
    }
}

void Item::supprimer() {
    delete litPointeur;
}

