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
                throw ComputerException(commandeEntree.toStdString());
            unElement = commandeEntree.left(index+1);
            commandeEntree.remove(0, index+1);
            execute(unElement);
        }
        else if(commandeEntree.at(0) == "["){
            int index = commandeEntree.lastIndexOf("]");
            if(index == -1){
                throw ComputerException("Programme non finie");
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

    if(inventaireOpArite1.contains(operande)){
        if(pile.estVide()){
            pile.modifierEtat("Il manque une opérande pour cette opération");
            return;
        }
        Item i1 = pile.end();
        try {
            Item resultat=inventaireOpArite1[operande](i1);
            pile.pop();
            i1.supprimer();
            pile.push(resultat);
        } catch (ComputerException &ce) {
            pile.modifierEtat(ce.what());
            return;
        }
    }
    else if(inventaireOpArite2.contains(operande)){
        if(pile.taille()<2){
            pile.modifierEtat("Il manque une ou plusieurs opérandes pour cette opération");
            return;
        }
        Item i1 = pile.end();
        Item i2 = pile.end(1);
        try {
            Item resultat=inventaireOpArite2[operande](i2, i1);
            pile.pop();
            i1.supprimer();
            pile.pop();
            i2.supprimer();
            pile.push(resultat);
            return;
        } catch (ComputerException &ce) {
            pile.modifierEtat(ce.what());
            return;
        }

    }
    else if(operande == "EVAL"){
        if(pile.estVide()){
            pile.modifierEtat("Il manque une opérande pour cette opération");
            return;
        }
        Item i = pile.end();
        try {
            pile.pop();
            Operateur::opEval(i);
            i.supprimer();
            return;
        } catch (ComputerException &ce) {
            pile.push(i);
            pile.modifierEtat(ce.what());
            return;
        }
    }

    else if(operande == "IFT"){
        if(pile.taille()<2){
            pile.modifierEtat("Il manque une ou plusieurs opérandes pour cette opération");
            return;
        }
        Item i1 = pile.end(1);
        Item i2 = pile.end();
        try {
            pile.pop();
            pile.pop();
            Operateur::opIFT(i1,i2);
            i1.supprimer();
            i2.supprimer();
            return;
        } catch (ComputerException &ce) {
            pile.push(i1);
            pile.push(i2);
            pile.modifierEtat(ce.what());
            return;
        }

    }
    else if(operande == "CLEAR"){
        pile.clear();
        return;
    }
    else if(operande == "SWAP"){
        pile.swap();
        return;
    }
    else if(operande == "DROP"){
        pile.drop();
        return;
    }
    else if(operande == "DUP"){
        pile.dup();
        return;
    }
    else if(operande == "STO"){
        if(pile.taille()<2){
            pile.modifierEtat("Il manque une ou plusieurs opérandes pour cette opération");
            return;
        }
        Item i1 = pile.end();
        Item i2 = pile.end(1);
        if(i1.obtenirType() != "Expression"){
            pile.modifierEtat("L'identifiant n'est pas conforme");
            return;
        }
        try {
            QString atome = i1.obtenirLitterale().versString();
            atome.chop(1);
            atome.remove(0,1);
            if(i2.obtenirType() == "Programme")
                persistence.ajouterProgramme(atome, i2.obtenirLitterale().versString());
            else
                persistence.ajouterVariable(atome, i2.obtenirLitterale().versString());
            pile.pop();
            i1.supprimer();
            pile.pop();
            i2.supprimer();
            return;
        } catch (ComputerException &ce) {
            pile.modifierEtat(ce.what());
            return;
        }
    }
    else if(persistence.getMapVariable().contains(operande)){
        try {
            QString temp=persistence.getMapVariable().operator[](operande);
            Item resultat = ConstructeurLitterale::distinguerConstruire(temp);
            pile.push(resultat);
        } catch (ComputerException &ce) {
            pile.modifierEtat(ce.what());
            return;
        }
    }
    else if(persistence.getMapProgramme().contains(operande)){
        try {
            QString temp=persistence.getMapProgramme().operator[](operande);
            temp.chop(1);
            temp.remove(0, 1);
            interprete(temp);
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
