#include "Persistence.h"
#include "Exception.h"

using namespace std;

Persistence &Persistence::getPersistence(){
    static Persistence instance;
    return instance;
}

void Persistence::ajouterVariable(QString saisieAtome, QString saisieVariable) {
    if(saisieAtome!=NULL && saisieVariable!=NULL){
        if(saisieAtome == '0' || saisieAtome == '1' || saisieAtome == '2' || saisieAtome == '3' || saisieAtome == '4' ||
           saisieAtome == '5' || saisieAtome == '6' || saisieAtome == '7' || saisieAtome == '8' || saisieAtome == '9' ||
           saisieAtome == '+' || saisieAtome == '-' || saisieAtome == '*' || saisieAtome == '/' ||
           saisieAtome == "CLEAR" || saisieAtome == "EVAL"){
            throw ComputerException("Cet atome ne peut pas être réutilisé.");
        }
        else {
            if (saisieVariable.contains(' ')){
                throw ComputerException("Rentrez une unique expression sans espace pour une variable.");
            }
            else{
                mapVariable.insert(saisieAtome,saisieVariable);
                emit actualiserAffichage();
                return;
            }
        }
    }
    else {
        throw ComputerException("Remplissez tous les champs avant de valider.");
    }
}

void Persistence::supprimerVariable(QString atome) {
    mapVariable.remove(atome);
}
