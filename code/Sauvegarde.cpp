//
// Created by Lorenzo on 15/12/2020.
//

#include <QTextStream>
#include <QMessageBox>
#include <QDomDocument>
#include <QDomElement>
#include <QFile>
#include <iostream>

#include "Sauvegarde.h"

using namespace std;

//Méthode d'enregistrement de l'état de la calculatrice dans le fichier XML
void Sauvegarde::sauvegardeEtat() {

    QDomDocument d("Sauvegarde");

    QDomProcessingInstruction instruction = d.createProcessingInstruction("xml","version=\"1.0\" encoding=\"ISO-8859-1\"");
    d.appendChild(instruction);
    QDomElement calculatrice = d.createElement("calculatrice");
    d.appendChild(calculatrice);

    //Pile
    QDomElement pile = d.createElement("pile");
    calculatrice.appendChild(pile);
    while (!refPile.estVide()) {
        //Récupère l'élément le plus haut de la pile et l'insère entre balises
        QDomElement element = d.createElement("element");
        pile.appendChild(element);
        QString s = refPile.end().obtenirLitterale().versString();
        refPile.pop();
        QDomText valeurElement = d.createTextNode(s);
        element.appendChild(valeurElement);
    }

    //Variables
    QDomElement variables = d.createElement("variables");
    calculatrice.appendChild(variables);
    for (auto v : persistance.obtenirMapVariable().keys()) {
        //Récupère un élément de la QMap
        QDomElement variable = d.createElement("variable");
        variables.appendChild(variable);
        //Met en attribut "id" de la balise l'identificateur la variable
        variable.setAttribute("id", v);
        //Met en attribut "value" de la balise la valeur de la variable
        variable.setAttribute("value", persistance.obtenirMapVariable().value(v));
    }

    //Programmes
    QDomElement programmes = d.createElement("programmes");
    calculatrice.appendChild(programmes);
    for (auto p : persistance.obtenirMapProgramme().keys()) {
        //Récupère un élément de la QMap
        QDomElement programme = d.createElement("programme");
        programmes.appendChild(programme);
        //Met en attribut "id" de la balise l'identificateur du programme
        programme.setAttribute("id", p);
        //Met en attribut "value" de la balise la valeur du programme
        programme.setAttribute("value", persistance.obtenirMapProgramme().value(p));
    }

    //Paramètres
    QDomElement parametres = d.createElement("parametres");
    calculatrice.appendChild(parametres);
    QDomElement nbItem = d.createElement("nbItemAAfficherPile");
    parametres.appendChild(nbItem);
    //Met en attribut "value" de la balise le nombre d'items à afficher dans la pile
    nbItem.setAttribute("value", refFenetrePrincipale->getNombreItemAAfficher());


    QFile fichier("calculatrice.xml");
    if (!fichier.open(QIODevice::WriteOnly)) {
        fichier.close();
        QMessageBox::critical(this, "Erreur", "Impossible d'écrire dans le document XML");
        exit(EXIT_FAILURE);
    }

    QTextStream stream(&fichier);
    stream << d.toString();

    fichier.close();
}

//Méthode de récupération de la sauvegarde dans le fichier XML
void Sauvegarde::recupereEtat() {
    QDomDocument *d = new QDomDocument("calculatrice");
    QFile calculatrice("calculatrice.xml");
    if (!calculatrice.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, "Erreur à l'ouverture du document XML",
                             "Le document XML n'a pas pu être ouvert. Si il était inexistant, il sera crée à la première sauvegarde.");
        return;
    }
    if (!d->setContent(&calculatrice)) {
        calculatrice.close();
        QMessageBox::warning(this, "Erreur à l'ouverture du document XML",
                             "Le document XML n'a pas pu être attribué à l'objet QDomDocument.");
        return;
    }

    QDomNode balise = d->firstChild();
    balise = balise.nextSibling();

    //Pile
    balise = balise.firstChild();
    QDomElement element = balise.lastChildElement();
    while (!element.isNull()) {
        //Construire une nouvelle littérale avec le texte récupéré et l'ajouter à la pile
        Item res = ConstructeurLitterale::distinguerConstruire(element.text());
        refPile.push(res);
        element = element.previousSiblingElement();
    }

    //Variables
    balise = balise.nextSibling();
    QDomElement variable = balise.firstChildElement();
    while (!variable.isNull()) {
        //Ajoute dans la QMap variable de persistance
        //variable.attribute("id") : nom de la variable
        //variable.attribute("value") : valeur de la variable
        persistance.ajouterVariable((QString) variable.attribute("id"), (QString) variable.attribute("value"));
        variable = variable.nextSiblingElement();
    }

    //Programmes
    balise = balise.nextSibling();
    QDomElement programme = balise.firstChildElement();
    while (!programme.isNull()) {
        //Ajoute dans la QMap programme de persistance
        //programme.attribute("id") : nom du programme
        //programme.attribute("value") : valeur du programme
        persistance.ajouterProgramme((QString) programme.attribute("id"), (QString) programme.attribute("value"));
        programme = programme.nextSiblingElement();
    }

    //Paramètres
    balise = balise.nextSibling();
    QDomElement nbItem = balise.firstChildElement();
    //Définir le bon nombre d'items à afficher dans la pile
    refFenetrePrincipale->setNombreItemAAfficher(nbItem.attribute("value").toInt());

    calculatrice.close();

}
