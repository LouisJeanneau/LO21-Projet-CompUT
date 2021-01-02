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

void Sauvegarde::sauvegardeEtat() {

    QDomDocument d("Sauvegarde");

    QDomProcessingInstruction instruction = d.createProcessingInstruction("xml",
                                                                          "version=\"1.0\" encoding=\"ISO-8859-1\"");
    d.appendChild(instruction);
    QDomElement calculatrice = d.createElement("calculatrice");
    d.appendChild(calculatrice);

    //Pile
    QDomElement pile = d.createElement("pile");
    calculatrice.appendChild(pile);
    while (!refPile.estVide()) {
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
    for (auto v : persistence.obtenirMapVariable().keys()) {
        QDomElement variable = d.createElement("variable");
        variables.appendChild(variable);
        variable.setAttribute("id", v);
        variable.setAttribute("value", persistence.obtenirMapVariable().value(v));
    }

    //Programmes
    QDomElement programmes = d.createElement("programmes");
    calculatrice.appendChild(programmes);
    for (auto p : persistence.obtenirMapProgramme().keys()) {
        QDomElement programme = d.createElement("programme");
        programmes.appendChild(programme);
        programme.setAttribute("id", p);
        programme.setAttribute("value", persistence.obtenirMapProgramme().value(p));
    }


    QFile fichier("calculatrice.xml");
    if (!fichier.open(QIODevice::WriteOnly)) {
        fichier.close();
        QMessageBox::critical(this, "Erreur", "Impossible d'écrire dans le document XML");
        exit(EXIT_FAILURE);
    }
    QTextStream stream(&fichier);
    stream << d.toString();
    //d.save(stream, 4);

    fichier.close();
    std::cout << "Fonction sauvegarde fin" << std::endl;
}

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

    //Pile
    QDomNode balise = d->firstChild();
    balise = balise.nextSibling();
    balise = balise.firstChild();
    QDomElement element = balise.lastChildElement();
    while (!element.isNull()) {
        //Construire une nouvelle litérale avec le texte récupéré
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
        persistence.ajouterVariable((QString) variable.attribute("id"), (QString) variable.attribute("value"));
        variable = variable.nextSiblingElement();
    }

    //Programmes
    balise = balise.nextSibling();
    QDomElement programme = balise.firstChildElement();
    while (!programme.isNull()) {
        //Ajoute dans la QMap programme de persistance
        //programme.attribute("id") : nom du programme
        //programme.attribute("value") : valeur du programme
        persistence.ajouterProgramme((QString) programme.attribute("id"), (QString) programme.attribute("value"));
        programme = programme.nextSiblingElement();
    }


    calculatrice.close();

}
