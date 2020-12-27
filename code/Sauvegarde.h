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
    Pile& refPile;
    Persistence &persistence = Persistence::getPersistence();
public:
    Sauvegarde(Pile& p) : refPile(p) {};
	~Sauvegarde();
    void sauvegardeEtat();
    void recupereEtat();
};

#endif //PROJET_LO21_SAUVEGARDE_H
