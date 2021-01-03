//
// Created by Lorenzo on 15/12/2020.
//

#ifndef PROJET_LO21_SAUVEGARDE_H
#define PROJET_LO21_SAUVEGARDE_H

#include "Computer.h"
#include "Persistance.h"
#include "fenetreprincipale.h"
#include <QWidget>
#include <QtXml>

class Sauvegarde : public QWidget {
Q_OBJECT
    Pile &refPile = Pile::obtenirPile();
    Persistance &persistance = Persistance::obtenirPersistance();
    fenetrePrincipale *refFenetrePrincipale;
public:
    Sauvegarde() = default;

    ~Sauvegarde() = default;

    void sauvegardeEtat();

    void recupereEtat();

    void setFenetrePrincipale(class fenetrePrincipale *fenetrePrincipaleCopie) { refFenetrePrincipale = fenetrePrincipaleCopie; }

    class fenetrePrincipale *getFenetrePrincipale() { return refFenetrePrincipale; }
};

#endif //PROJET_LO21_SAUVEGARDE_H
