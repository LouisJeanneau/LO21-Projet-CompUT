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
            unElement = commandeEntree.left(index);
            if(index == -1)
                index = 1;
            commandeEntree.remove(0, index);
            execute(unElement);
        }
    }

}

void Interpreteur::execute(QString operande) {
    //QMap<QString, int> listeOp = Operateur.listeOperateur;

    /*
    if(operande.startsWith('\'')){
        //Creation et empilement d'une expression
    }
    else if(operande.startsWith('[')){
        //Creation et empilement d'un programme
    }
    else if (listeOp.contains(operande)){
        //UTILISATION DU BON OPERATEUR
    }

    else if( est numérique){
        //Creation et empilement d'une literale numérique
    }
     */
}

Interpreteur &Interpreteur::obtenirInterpreteur() {
    static Interpreteur instance;
    return instance;
}
