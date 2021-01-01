//
// Created by Louis on 06/12/2020.
//


#include "Interpreteur.h"
#include <iostream>
#include <QMap>

using namespace std;

//Le but d'interprete est de prendre l'entiereté de la chaine entrée par l'utilisateur et de la couper en opérandes à évaluer
void Interpreteur::interprete(QString commandeEntree) {
    QString unElement;

    //Tant qu'on n'a pas fini de traiter l'intégralité de la chaine
    while(commandeEntree.length()){
        unElement.clear();

        //Le début de la chaine est un espace : on le supprime
        if(commandeEntree.at(0) == " "){
            commandeEntree.remove(0,1);
            continue;
        }
        //Le début de la chaine est un guillemet, on est face à une expression
        else if(commandeEntree.at(0) == "'"){
            //Si l'expression n'est pas fermée, on lance une erreur
            int index = commandeEntree.indexOf('\'', 1);
            if(index == -1) {
                pile.modifierEtat("Erreur : Expression non fini");
                throw ComputerException(commandeEntree.toStdString());
            }
            unElement = commandeEntree.left(index+1);
            if(unElement.contains(' ')){
                pile.modifierEtat("Erreur : L'expression contient un espace");
                throw ComputerException(commandeEntree.toStdString());
            }
            commandeEntree.remove(0, index+1);
        }
        //Le début de la chaine est un crochet, on est face à un programme
        else if(commandeEntree.at(0) == "["){
            //Si le programme n'est pas fermé, on lance une erreur
            int index = commandeEntree.lastIndexOf("]");
            if(index == -1){
                pile.modifierEtat("Erreur : Programme non finie");
                throw ComputerException(commandeEntree.toStdString());
            }
            unElement = commandeEntree.left(index+1);
            commandeEntree.remove(0, index+1);
        }
        //L'opérande s'arrête au premier espace rencontré
        else{
            int index = commandeEntree.indexOf(' ');
            //Si il n'y a pas d'espace dans la chaine, nous sommes face au dernier opérandes
            if(index == -1)
                index = commandeEntree.length();
            unElement = commandeEntree.left(index);
            commandeEntree.remove(0, index);
        }

        //On execute le traitement de l'opérande
        try {
            execute(unElement);
        } catch (ComputerException &ce) {
            throw ComputerException(commandeEntree.toStdString());
        }
    }
}

//Le but d'execute est de faire correspondre l'opérande à la bonne action à effectuer
void Interpreteur::execute(QString operande) {
    //Si l'opérande est dans l'inventaire d'opérateurs d'arité 1
    if(Operateur::inventaireOpArite1.contains(operande)){
        if(pile.estVide()){
            pile.modifierEtat("Il manque une opérande pour cette opération");
            throw ComputerException(" ");
        }
        Item i1 = pile.end();
        try {
            Item resultat=Operateur::inventaireOpArite1[operande](i1);
            pile.pop();
            i1.supprimer();
            pile.push(resultat);
        } catch (ComputerException &ce) {
            pile.modifierEtat(ce.what());
            throw ComputerException(" ");
        }
    }
    //Si l'opérande est dans l'inventaire d'opérateurs d'arité 2
    else if(Operateur::inventaireOpArite2.contains(operande)){
        if(pile.taille()<2){
            pile.modifierEtat("Il manque une ou plusieurs opérandes pour cette opération");
            throw ComputerException(" ");
        }
        Item i1 = pile.end();
        Item i2 = pile.end(1);
        try {
            Item resultat=Operateur::inventaireOpArite2[operande](i2, i1);
            pile.pop();
            i1.supprimer();
            pile.pop();
            i2.supprimer();
            pile.push(resultat);
            return;
        } catch (ComputerException &ce) {
            pile.modifierEtat(ce.what());
            throw ComputerException(" ");
        }
    }
    //Dans cette partie, ce sont des opérateurs spéciaux : ils ont une arité variable ou concernent la pile
    else if(operande == "EVAL"){
        if(pile.estVide()){
            pile.modifierEtat("Il manque une opérande pour cette opération");
            throw ComputerException(" ");
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
            throw ComputerException(" ");
        }
    }
    else if(operande == "IFT"){
        if(pile.taille()<2){
            pile.modifierEtat("Il manque une ou plusieurs opérandes pour cette opération");
            throw ComputerException(" ");
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
            throw ComputerException(" ");
        }
    }
    else if(operande == "IFTE"){
        if(pile.taille()<3){
            pile.modifierEtat("Il manque une ou plusieurs opérandes pour cette opération");
            throw ComputerException(" ");
        }
        Item i1 = pile.end(2);
        Item i2 = pile.end(1);
        Item i3 = pile.end();
        try {
            pile.pop();
            pile.pop();
            pile.pop();
            Operateur::opIFTE(i1,i2,i3);
            i1.supprimer();
            i2.supprimer();
            i3.supprimer();
            return;
        } catch (ComputerException &ce) {
            pile.push(i1);
            pile.push(i2);
            pile.push(i3);
            pile.modifierEtat(ce.what());
            throw ComputerException(" ");
        }

    }
    else if(operande == "WHILE"){
        if(pile.taille()<2){
            pile.modifierEtat("Il manque une ou plusieurs opérandes pour cette opération");
            throw ComputerException(" ");
        }
        Item i1 = pile.end(1);
        Item i2 = pile.end();
        try {
            pile.pop();
            pile.pop();
            Operateur::opWHILE(i1,i2);
            i1.supprimer();
            i2.supprimer();
            return;
        } catch (ComputerException &ce) {
            pile.push(i1);
            pile.push(i2);
            pile.modifierEtat(ce.what());
            throw ComputerException(" ");
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
            throw ComputerException(" ");
        }
        Item i1 = pile.end();
        Item i2 = pile.end(1);
        if(i1.obtenirType() != "Expression"){
            pile.modifierEtat("L'identifiant n'est pas conforme");
            throw ComputerException(" ");
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
            throw ComputerException(" ");
        }
    }
    else if(persistence.getMapVariable().contains(operande)){
        try {
            QString temp=persistence.getMapVariable().operator[](operande);
            Item resultat = ConstructeurLitterale::distinguerConstruire(temp);
            pile.push(resultat);
        } catch (ComputerException &ce) {
            pile.modifierEtat(ce.what());
            throw ComputerException(" ");
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
            throw ComputerException(" ");
        }
    }
    else {
        try {
            Item resultat = ConstructeurLitterale::distinguerConstruire(operande);
            pile.push(resultat);
        } catch (ComputerException &ce) {
            pile.modifierEtat(ce.what());
            throw ComputerException(" ");
        }
    }
}

Interpreteur &Interpreteur::obtenirInterpreteur() {
    static Interpreteur instance;
    return instance;
}
