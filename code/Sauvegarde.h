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
    Controleur& refContr;
public:
	Sauvegarde();
	~Sauvegarde();
    void sauvegardeEtat();
};

#endif //PROJET_LO21_SAUVEGARDE_H