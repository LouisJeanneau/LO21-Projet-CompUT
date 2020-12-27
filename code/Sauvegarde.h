//
// Created by Lorenzo on 15/12/2020.
//

#ifndef PROJET_LO21_SAUVEGARDE_H
#define PROJET_LO21_SAUVEGARDE_H

#include <QtXml>
#include <QWidget>
#include "Computer.h"

class Sauvegarde : public QWidget
{
    Pile& refPile;
public:
	Sauvegarde(Pile& p) : refPile(p) {}
	~Sauvegarde();
    void sauvegardeEtat();
    void recupereEtat();
};

#endif //PROJET_LO21_SAUVEGARDE_H