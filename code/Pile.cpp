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
    listeItems.pop_back();
    modifierEtat("Pop réussi");
}

Item Pile::end(int n) {
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
        for (auto it = listeItems.begin(); it != listeItems.end(); it++)
            it->supprimer();
        modifierEtat("Pile vidée");
    } catch (ComputerException &ce) {
        modifierEtat("Erreur lors du clear de la pile");
    }
}

void Pile::swap() {

}

void Item::supprimer() {
    delete litPointeur;
}

