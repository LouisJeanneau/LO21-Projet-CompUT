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

    //Programmes
    QDomElement programmes = doc.createElement("programmes");
    claculatrice.appendChild(programmes);


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