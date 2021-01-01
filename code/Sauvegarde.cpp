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

void Sauvegarde::sauvegardeEtat(){
    
    QDomDocument d;

    //QDomProcessingInstruction instruction=doc.createProcessingInstruction("xml","version=\"1.0\" encoding=\"ISO-8859-1\"");
    //d.appendChild(instruction);
    QDomElement calculatrice = d.createElement("calculatrice");
    d.appendChild(calculatrice);

    //Pile
    QDomElement pile = d.createElement("pile");
    calculatrice.appendChild(pile);
    for(unsigned int i = 0; i < refPile.taille(); i++){
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
    for(auto v : Persistence::mapVariable.keys()){
        QDomElement variable = doc.createElement("variable");
        variables.appendChild(variable);
        variable.setAttribute("id", v);
        variable.setAttribute("value", Persistence::mapVariable.value(v));
    }  

    //Programmes
    QDomElement programmes = doc.createElement("programmes");
    claculatrice.appendChild(programmes);
    for(auto p : Persistence::mapProgramme.keys()){
        QDomElement programme = doc.createElement("programme");
        programmes.appendChild(programme);
        programme.setAttribute("id", p);
        programme.setAttribute("value", Persistence::mapProgramme.value(p));
    } 


    QFile fichier("calculatrice.xml");
    if(!fichier.open(QIODevice::WriteOnly))
    {
        fichier.close();
        QMessageBox::critical(this,"Erreur","Impossible d'écrire dans le document XML");
        return;
    }

    QTextStream stream(&fichier);
    stream << d.toString();
    //d.save(stream, 4);

    fichier.close();
}

void Sauvegarde::recupereEtat(){
    QDomDocument *d = new QDomDocument("calculatrice");
    QFile calculatrice("calculatrice.xml");
    if(!calculatrice.open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(this,"Erreur à l'ouverture du document XML","Le document XML n'a pas pu être ouvert.");
        return;
    }
    if (!d->setContent(&calculatrice))
    {
        calculatrice.close();
        QMessageBox::warning(this, "Erreur à l'ouverture du document XML", "Le document XML n'a pas pu être attribué à l'objet QDomDocument.");
        return;
    }

    //Pile
    QDomNode balise = d.firstChild();
    QDomElement element = balise.lastChildElement();
    while(!element.isNull()){
        //Construire une nouvelle litérale avec le texte récupéré
        Item res = ConstructeurLitterale::distinguerConstruire(element.text());
        refPile.push(res);
        element = element.previousSiblingElement();
    }

    //Variables
    balise = balise.nextSibling();
    QDomElement variable = balise.firstChildElement();
    while(!variable.isNull()){
        //Ajoute dans la QMap variable de persistance
        //variable.attribute("id") : nom de la variable
        //variable.attribute("value") : valeur de la variable
        Persistence::setMapVariable(variable.attribute("id"), variable.attribute("value"));
        variable = variable.nextSiblingElement();
    }

    //Programmes
    balise = balise.nextSibling();
    QDomElement programme = balise.firstChildElement();
    while(!programme.isNull()){
        //Ajoute dans la QMap programme de persistance
        //programme.attribute("id") : nom du programme
        //programme.attribute("value") : valeur du programme
        Persistence::setMapProgramme(programme.attribute("id"), programme.attribute("value"));
        programme = programme.nextSiblingElement();
    }


    calculatrice.close();

}