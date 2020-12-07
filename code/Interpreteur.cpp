//
// Created by Louis on 06/12/2020.
//


#include "Interpreteur.h"


void Interpreteur::interprete(QString commandeEntree) {
    QString unElement;

    while(commandeEntree.length() != 0){
        //Tant qu'on a pas traite toute la phrase

        unElement.clear();

        if(commandeEntree.at(0) == " "){
            commandeEntree.remove(0,1);
        }
        else if(commandeEntree.at(0) == "'"){
            unsigned int index = commandeEntree.indexOf('\'', 1);
            if(index == -1)
                throw ComputerException("Axiome non finie");
            unElement = commandeEntree.left(index);
            commandeEntree.chop(index);
            execute(unElement);
        }
        else if(commandeEntree.at(0) == "["){
            unsigned int index = commandeEntree.lastIndexOf(']');
            if(index == -1)
                throw ComputerException("Programme non finie");
            unElement = commandeEntree.left(index);
            commandeEntree.chop(index);
            execute(unElement);
        }
    }

}

void Interpreteur::execute(QString operande) {

}