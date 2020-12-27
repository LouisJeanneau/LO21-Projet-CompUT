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
            int index = commandeEntree.lastIndexOf("]");
            if(index == -1){
                //throw ComputerException("Programme non finie");
                cout << commandeEntree.toStdString() << endl;
            }

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

    QMap<QString, std::function<Item(Item, Item)>> inventaireOpArite2=Operateur::inventaireOpArite2;
    QMap<QString, std::function<Item(Item)>> inventaireOpArite1=Operateur::inventaireOpArite1;
    QMap<QString, std::function<Item()>> inventaireOpArite0=Operateur::inventaireOpArite0;

    if(inventaireOpArite0.contains(operande)){
        Item resultat=inventaireOpArite0[operande]();
        if(resultat.estVide()){
            pile.modifierEtat("Opération arité 0 ratée");
            return;
        }
        pile.push(resultat);
    }
    else if(inventaireOpArite1.contains(operande)){
        if(pile.estVide()){
            pile.modifierEtat("Il manque un opérateur pour cette opération");
            return;
        }
        Item i1 = pile.end();
        try {
            Item resultat=inventaireOpArite1[operande](i1);
            pile.pop();
            pile.push(resultat);
        } catch (ComputerException &ce) {
            pile.modifierEtat(ce.what());
            return;
        }
    }
    else if(inventaireOpArite2.contains(operande)){
        if(pile.taille()<2){
            pile.modifierEtat("Il manque un ou plusieurs opérateur pour cette opération");
            return;
        }
        Item i1 = pile.end();
        Item i2 = pile.end(1);
        try {
            Item resultat=inventaireOpArite2[operande](i2, i1);
            pile.pop();
            pile.pop();
            pile.push(resultat);
            return;
        } catch (ComputerException &ce) {
            pile.modifierEtat(ce.what());
            return;
        }

    }
    else {
        Item resultat = ConstructeurLitterale::distinguerConstruire(operande);
        pile.push(resultat);
    }
}

Interpreteur &Interpreteur::obtenirInterpreteur() {
    static Interpreteur instance;
    return instance;
}
