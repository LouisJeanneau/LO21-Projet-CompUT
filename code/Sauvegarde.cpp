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

Sauvegarde::Sauvegarde() : QWidget()
{

}

Sauvegarde::~Sauvegarde()
{

}

void Sauvegarde::sauvegardeEtat(){
    
    QDomDocument d;

    //QDomProcessingInstruction instruction=doc.createProcessingInstruction("xml","version=\"1.0\" encoding=\"ISO-8859-1\"");
    //d.appendChild(instruction);
    QDomElement calculatrice = d.createElement("calculatrice");
    d.appendChild(calculatrice);

    //Pile
    QDomElement pile = d.createElement("pile");
    calculatrice.appendChild(pile);
    for(unsigned int i = 0; i < refContr.refPile.taille(); i++){
        QDomElement element = doc.createElement("element");
        pile.appendChild(element);
        QString s = refContr.refPile.pop().obtenirLitterale().versString();
        QDomText valeurElement = doc.createTextNode(s);
        litterale.appendChild(valeurElement);
    }

    //Variables
    QDomElement variables = d.createElement("variables");
    calculatrice.appendChild(variables);
    for(auto v : refContr.refPers.mapVar.keys()){
        QDomElement variable = doc.createElement("variable");
        variables.appendChild(variable);
        variable.setAttribute("id", v);
        variable.setAttribute("value", refContr.refPers.mapVar.value(v));
    }  

    //Programmes
    QDomElement programmes = doc.createElement("programmes");
    claculatrice.appendChild(programmes);
    for(auto p : refContr.refPers.mapProg.keys()){
        QDomElement programme = doc.createElement("programme");
        programmes.appendChild(programme);
        programme.setAttribute("id", v);
        programme.setAttribute("value", refContr.refPers.mapProg.value(p));
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
        //Litterale *res = new Litterale(element.text());
        refContr.refPile.push(*res);
        element = element.previousSiblingElement();
    }

    //Variables
    balise = balise.nextSibling();
    QDomElement variable = balise.firstChildElement();
    while(!variable.isNull()){
        //Ajoute dans la QMap variable de persistance
        //variable.attribute("id") : nom de la variable
        //variable.attribute("value") : valeur de la variable
        variable = variable.nextSiblingElement();
    }

    //Programmes
    balise = balise.nextSibling();
    QDomElement programme = balise.firstChildElement();
    while(!programme.isNull()){
        //Ajoute dans la QMap programme de persistance
        //programme.attribute("id") : nom du programme
        //programme.attribute("value") : valeur du programme
        programme = programme.nextSiblingElement();
    }


    d.close();

}