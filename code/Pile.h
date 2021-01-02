//
// Created by Louis on 06/12/2020.
//

#ifndef LO21_PROJET_PILE_H
#define LO21_PROJET_PILE_H

#include <vector>
#include <QObject>
#include <string>
#include <functional>
#include <QMap>
#include "Litterale.h"

using namespace std;

class Litterale;

class Item {
    Litterale *litPointeur;
    QString typeItem;
public:
    explicit Item(Litterale *l, QString t);

    Item(const Item &i);

    Item &operator=(const Item &i);

    ~Item() {};

    void supprimer();

    Litterale &obtenirLitterale() { return *litPointeur; }

    QString obtenirType() { return typeItem; }

    bool operator==(const Item &i);

};

class Pile : public QObject {
Q_OBJECT
    QString etat;
    std::vector<Item> listeItems;
    static Pile instance;

    Pile() = default;

public:
    static Pile &obtenirPile();

    void pop();

    Item end(int n = 0);

    void push(Item item);

    bool estVide();

    unsigned int taille();

    void debug();

    QString obtenirEtat() const;

    void modifierEtat(QString e);

    std::vector<Item> copierListeItems();

    void swap();

    void clear();

    void drop();

    void dup();

};

#endif //LO21_PROJET_PILE_H
