//
// Created by Lorenzo on 15/12/2020.
//

#ifndef PROJET_LO21_SAUVEGARDE_H
#define PROJET_LO21_SAUVEGARDE_H

#include "Computer.h"
#include <QWidget>
#include "Persistence.h"
#include <QtXml>

class Sauvegarde : public QWidget
{
    Q_OBJECT
    Pile &refPile = Pile::obtenirPile();
    Persistence &persistence = Persistence::getPersistence();
public:
    Sauvegarde() = default;
	~Sauvegarde() = default;
    void sauvegardeEtat();
    void recupereEtat();
public slots:
    void commencerSauvegarde(){sauvegardeEtat();}
};

#endif //PROJET_LO21_SAUVEGARDE_H
