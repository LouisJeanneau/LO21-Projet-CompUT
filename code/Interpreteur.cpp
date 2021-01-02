//
// Created by Louis on 06/12/2020.
//


#include "Interpreteur.h"
#include <iostream>
#include <QMap>

using namespace std;

//Le but d'interpreter est de prendre l'entiereté de la chaine entrée par l'utilisateur et de la couper en opérandes à évaluer
void Interpreteur::interpreter(QString commandeEntree) {
    QString unElement;
    int index = 0;

    //Tant qu'on n'a pas fini de traiter l'intégralité de la chaine
    while (commandeEntree.length()) {
        unElement.clear();

        //Le début de la chaine est un espace : on le supprime
        if (commandeEntree.at(0) == " ") {
            commandeEntree.remove(0, 1);
            continue;
        }
            //Le début de la chaine est un guillemet, on est face à une expression
        else if (commandeEntree.at(0) == "'") {
            //Si l'expression n'est pas fermée, on lance une erreur
            index = commandeEntree.indexOf('\'', 1) + 1;
            if (index == 0) {
                pile.modifierEtat("Erreur : Expression non fini");
                throw ComputerException(commandeEntree.toStdString());
            }
            unElement = commandeEntree.left(index);
            if (unElement.contains(' ')) {
                pile.modifierEtat("Erreur : L'expression contient un espace");
                throw ComputerException(commandeEntree.toStdString());
            }

        }
            //Le début de la chaine est un crochet, on est face à un programme
        else if (commandeEntree.at(0) == "[") {
            //Si le programme n'est pas fermé, on lance une erreur
            index = commandeEntree.lastIndexOf("]") + 1;
            if (index == 0) {
                pile.modifierEtat("Erreur : Programme non finie");
                throw ComputerException(commandeEntree.toStdString());
            }
            unElement = commandeEntree.left(index);
        }
            //L'opérande s'arrête au premier espace rencontré
        else {
            index = commandeEntree.indexOf(' ');
            //Si il n'y a pas d'espace dans la chaine, nous sommes face au dernier opérandes
            if (index == -1)
                index = commandeEntree.length();
            unElement = commandeEntree.left(index);
        }

        //On execute le traitement de l'opérande
        try {
            executer(unElement);
            commandeEntree.remove(0, index);
        } catch (ComputerException &ce) {
            throw ComputerException(commandeEntree.toStdString());
        }
    }
    pile.modifierEtat("Ligne d'opérandes interprétée !");
}

//Le but d'executer est de faire correspondre l'opérande à la bonne action à effectuer
void Interpreteur::executer(QString operande) {
    try {
        //Si l'opérande est dans l'inventaire d'opérateurs d'arité 1
        if (Operateur::inventaireOpArite1.contains(operande)) {
            if (pile.estVide()) {
                throw ComputerException("Il manque une opérande pour cette opération");
            }
            Item i1 = pile.end();

            Item resultat = Operateur::inventaireOpArite1[operande](i1);
            pile.pop();
            i1.supprimer();
            pile.push(resultat);

        }
            //Si l'opérande est dans l'inventaire d'opérateurs d'arité 2
        else if (Operateur::inventaireOpArite2.contains(operande)) {
            if (pile.taille() < 2) {
                throw ComputerException("Il manque une ou plusieurs opérandes pour cette opération");
            }
            Item i1 = pile.end();
            Item i2 = pile.end(1);

            Item resultat = Operateur::inventaireOpArite2[operande](i2, i1);
            pile.pop();
            i1.supprimer();
            pile.pop();
            i2.supprimer();
            pile.push(resultat);

        }
            //Dans cette partie, ce sont des opérateurs spéciaux : ils ont une arité variable ou concernent la pile
        else if (operande == "EVAL") {
            if (pile.estVide()) {
                throw ComputerException("Il manque une opérande pour cette opération");
            }
            Item i = pile.end();
            try {
                pile.pop();
                Operateur::opEval(i);
                i.supprimer();
            } catch (ComputerException &ce) {
                pile.push(i);
                throw ComputerException(ce.what());
            }
        } else if (operande == "IFT") {
            if (pile.taille() < 2) {
                throw ComputerException("Il manque une ou plusieurs opérandes pour cette opération");
            }
            Item i1 = pile.end(1);
            Item i2 = pile.end();
            try {
                pile.pop();
                pile.pop();
                Operateur::opIFT(i1, i2);
                i1.supprimer();
                i2.supprimer();
            } catch (ComputerException &ce) {
                pile.push(i1);
                pile.push(i2);
                throw ComputerException(ce.what());
            }
        } else if (operande == "IFTE") {
            if (pile.taille() < 3) {
                throw ComputerException("Il manque une ou plusieurs opérandes pour cette opération");
            }
            Item i1 = pile.end(2);
            Item i2 = pile.end(1);
            Item i3 = pile.end();
            try {
                pile.pop();
                pile.pop();
                pile.pop();
                Operateur::opIFTE(i1, i2, i3);
                i1.supprimer();
                i2.supprimer();
                i3.supprimer();
            } catch (ComputerException &ce) {
                pile.push(i1);
                pile.push(i2);
                pile.push(i3);
                throw ComputerException(ce.what());
            }

        } else if (operande == "WHILE") {
            if (pile.taille() < 2) {
                throw ComputerException("Il manque une ou plusieurs opérandes pour cette opération");
            }
            Item i1 = pile.end(1);
            Item i2 = pile.end();
            try {
                pile.pop();
                pile.pop();
                Operateur::opWHILE(i1, i2);
                i1.supprimer();
                i2.supprimer();
            } catch (ComputerException &ce) {
                pile.push(i1);
                pile.push(i2);
                throw ComputerException(ce.what());
            }

        } else if (operande == "CLEAR") {
            pile.clear();
        } else if (operande == "SWAP") {
            pile.swap();
        } else if (operande == "DROP") {
            pile.drop();
        } else if (operande == "DUP") {
            pile.dup();
        } else if (operande == "STO") {
            if (pile.taille() < 2) {
                throw ComputerException("Il manque une ou plusieurs opérandes pour cette opération");
            }
            Item i1 = pile.end();
            Item i2 = pile.end(1);
            if (i1.obtenirType() != "Expression") {
                throw ComputerException("L'identifiant n'est pas conforme");
            }

            QString atome = i1.obtenirLitterale().versString();
            atome.chop(1);
            atome.remove(0, 1);
            if (i2.obtenirType() == "Programme")
                persistence.ajouterProgramme(atome, i2.obtenirLitterale().versString());
            else
                persistence.ajouterVariable(atome, i2.obtenirLitterale().versString());
            pile.pop();
            i1.supprimer();
            pile.pop();
            i2.supprimer();

        } else if (operande == "FORGET") {
            Item i = pile.end();
            if (i.obtenirType() != "Expression")
                throw ComputerException("Erreur : il faut réaliser FORGET sur une expression");
            QString identifiant = i.obtenirLitterale().versString();
            identifiant.chop(1);
            identifiant.remove(0, 1);
            if (persistence.obtenirMapVariable().contains(identifiant))
                persistence.supprimerVariable(identifiant);
            else if (persistence.obtenirMapProgramme().contains(identifiant))
                persistence.supprimerProgramme(identifiant);
            else {
                throw ComputerException(
                        "Erreur : Cette expression n'est pas l'identificateur d'une variable / programme");
            }
            pile.pop();
            i.supprimer();
        } else if (persistence.obtenirMapVariable().contains(operande)) {

            QString temp = persistence.obtenirMapVariable().operator[](operande);
            Item resultat = ConstructeurLitterale::distinguerConstruire(temp);
            pile.push(resultat);

        } else if (persistence.obtenirMapProgramme().contains(operande)) {

            QString temp = persistence.obtenirMapProgramme().operator[](operande);
            temp.chop(1);
            temp.remove(0, 1);
            interpreter(temp);

        } else {

            Item resultat = ConstructeurLitterale::distinguerConstruire(operande);
            pile.push(resultat);

        }
    } catch (ComputerException &ce) {
        pile.modifierEtat(ce.what());
        throw ComputerException();
    }
}

Interpreteur &Interpreteur::obtenirInterpreteur() {
    static Interpreteur instance;
    return instance;
}
