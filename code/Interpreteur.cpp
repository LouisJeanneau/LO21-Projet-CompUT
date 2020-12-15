//
// Created by Louis on 06/12/2020.
//


#include "Interpreteur.h"
#include <iostream>
#include <QMap>

using namespace std;

void Interpreteur::interprete(QString commandeEntree) {
    QString unElement;

    while(commandeEntree.length() != 0){
        //Tant qu'on a pas traite toute la phrase
        unElement.clear();

        if(commandeEntree.at(0) == " "){
            commandeEntree.remove(0,1);
        }
        else if(commandeEntree.at(0) == "'"){
            cout << "axiome" << endl;
            int index = commandeEntree.indexOf('\'', 1);
            if(index == -1)
                throw ComputerException("Axiome non finie");
            unElement = commandeEntree.left(index+1);
            commandeEntree.remove(0, index+1);
            execute(unElement);
        }
        else if(commandeEntree.at(0) == "["){
            int index = commandeEntree.lastIndexOf(']');
            if(index == -1)
                throw ComputerException("Programme non finie");
            unElement = commandeEntree.left(index+1);
            commandeEntree.remove(0, index+1);
            execute(unElement);
        }
        else{
            int index = commandeEntree.indexOf(' ');
            if(index == -1)
                index = commandeEntree.length();
            unElement = commandeEntree.left(index);
            commandeEntree.remove(0, index);
            execute(unElement);
        }
    }

}

void Interpreteur::execute(QString operande) {
    //Test de chaque operateur
    Litterale* resPointeur;
    /*
    QMap<QString, std::function<Litterale&(Item, Item)>> inventaireOpArite2=Operateur::inventaireOpArite2;
    QMap<QString, std::function<Litterale&(Item)>> inventaireOpArite1=Operateur::inventaireOpArite1;
    QMap<QString, std::function<Litterale&()>> inventaireOpArite0=Operateur::inventaireOpArite0;

    if(inventaireOpArite0.contains(operande)){
        Litterale& resPointeur=inventaireOpArite0[operande]();
        Item iRes(&resPointeur);
    }
    else if(inventaireOpArite1.contains(operande)){
        Item i1 = pile.pop();
        Litterale& resPointeur=inventaireOpArite1[operande](i1);
        Item iRes(&resPointeur);
    }
    else if(inventaireOpArite2.contains(operande)){

    }
     */
}

Interpreteur &Interpreteur::obtenirInterpreteur() {
    static Interpreteur instance;
    return instance;
}
