//
// Created by Ismail Kadiri on 29/12/2020.
//

#ifndef PROJET_LO21_PERSISTANCE_H
#define PROJET_LO21_PERSISTANCE_H

#ifndef PERSISTENCE_H
#define PERSISTENCE_H

#include <QMap>
#include <QWidget>

class Persistance : public QObject {
Q_OBJECT
    static Persistance instance;

    Persistance() = default;

    QMap<QString, QString> mapVariable;
    QMap<QString, QString> mapProgramme;
public:

    void ajouterVariable(QString atome, QString variable);

    void supprimerVariable(QString atome);

    QMap<QString, QString> obtenirMapVariable() { return mapVariable; };

    unsigned int obtenirTailleMapVariable() { return mapVariable.size(); };

    void ajouterProgramme(QString saisieAtome, QString saisieProgramme);

    void supprimerProgramme(QString atome);

    QMap<QString, QString> obtenirMapProgramme() { return mapProgramme; };

    unsigned int obtenirTailleMapProgramme() { return mapProgramme.size(); };

    static Persistance &obtenirPersistence();

signals:

    void actualiserAffichage();
};

#endif // PERSISTENCE_H


#endif //PROJET_LO21_PERSISTANCE_H
