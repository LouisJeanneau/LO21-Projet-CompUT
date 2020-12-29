//
// Created by Louis on 06/12/2020.
//

#include <iostream>
#include <QApplication>
#include "Interpreteur.h"
#include "fenetreprincipale.h"

using namespace std;

int main(int argc, char *argv[]) {
    qDebug() << "test1";
    QApplication a(argc, argv);
    qDebug() << "test2";
    fenetrePrincipale fenetre;
    qDebug() << "test3";
    fenetre.show();
    return a.exec();
}
