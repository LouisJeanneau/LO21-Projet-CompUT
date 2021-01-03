#include "Persistance.h"
#include "Exception.h"

using namespace std;

Persistance &Persistance::obtenirPersistence() {
    static Persistance instance;
    return instance;
}

void Persistance::ajouterVariable(QString saisieAtome, QString saisieVariable) {
    if (saisieAtome != NULL && saisieVariable != NULL) {
        if (saisieAtome == '0' || saisieAtome == '1' || saisieAtome == '2' || saisieAtome == '3' ||
            saisieAtome == '4' ||
            saisieAtome == '5' || saisieAtome == '6' || saisieAtome == '7' || saisieAtome == '8' ||
            saisieAtome == '9' ||
            saisieAtome == '+' || saisieAtome == '-' || saisieAtome == '*' || saisieAtome == '/' ||
            saisieAtome == "CLEAR" || saisieAtome == "EVAL") {
            throw ComputerException("Cet atome ne peut pas être réutilisé.");
        } else {
            if (saisieVariable.contains(' ')) {
                throw ComputerException("Rentrez une unique expression sans espace pour une variable.");
            }
            if (mapProgramme.contains(saisieAtome))
                throw ComputerException("Ce nom est déjà lié à un programme");
            else {
                mapVariable.insert(saisieAtome, saisieVariable);
                emit actualiserAffichage();
                return;
            }
        }
    } else {
        throw ComputerException("Remplissez tous les champs avant de valider.");
    }
}

void Persistance::supprimerVariable(QString atome) {
    mapVariable.remove(atome);
    emit actualiserAffichage();
}

void Persistance::ajouterProgramme(QString saisieAtome, QString saisieProgramme) {
    if (saisieAtome != NULL && saisieProgramme != NULL) {
        if (saisieAtome == '0' || saisieAtome == '1' || saisieAtome == '2' || saisieAtome == '3' ||
            saisieAtome == '4' ||
            saisieAtome == '5' || saisieAtome == '6' || saisieAtome == '7' || saisieAtome == '8' ||
            saisieAtome == '9' ||
            saisieAtome == '+' || saisieAtome == '-' || saisieAtome == '*' || saisieAtome == '/' ||
            saisieAtome == "CLEAR" || saisieAtome == "EVAL") {
            throw ComputerException("Cet atome ne peut pas être réutilisé.");
        } else {
            if (!saisieProgramme.contains('[') || !saisieProgramme.contains(']'))
                throw ComputerException("Ajouter les [ ] au programme");
            if (mapVariable.contains(saisieAtome))
                throw ComputerException("Ce nom est déjà lié à une variable");
            mapProgramme.insert(saisieAtome, saisieProgramme);
            emit actualiserAffichage();
            return;
        }
    } else {
        throw ComputerException("Remplissez tous les champs avant de valider.");
    }
}

void Persistance::supprimerProgramme(QString atome) {
    mapProgramme.remove(atome);
    emit actualiserAffichage();
}
