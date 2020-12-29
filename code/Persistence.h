//
// Created by Ismail Kadiri on 29/12/2020.
//

#ifndef PROJET_LO21_PERSISTENCE_H
#define PROJET_LO21_PERSISTENCE_H

#ifndef PERSISTENCE_H
#define PERSISTENCE_H

#include <QMap>
#include <QWidget>

class Persistence : public QObject {
Q_OBJECT
    static Persistence instance;

    Persistence() = default;

    QMap<QString, QString> mapVariable;
    QMap<QString, QString> mapProgramme;
public:

    void ajouterVariable(QString atome, QString variable);

    void supprimerVariable(QString atome);

    QMap<QString, QString> getMapVariable() { return mapVariable; };

    unsigned int getMapVariableSize() { return mapVariable.size(); };

<<<<<<< HEAD
    void ajouterProgramme(QString atome, QString variable) { mapProgramme.insert(atome, variable); };
=======
    void ajouterProgramme(QString saisieAtome, QString saisieProgramme);

    void supprimerProgramme(QString atome);
>>>>>>> cb4f4c4790baa45009d5c63d3ed3290984b8ebd4

    QMap<QString, QString> getMapProgramme() { return mapProgramme; };

    unsigned int getMapProgrammeSize() { return mapProgramme.size(); };

    static Persistence &getPersistence();

signals:

    void actualiserAffichage();
};

#endif // PERSISTENCE_H


#endif //PROJET_LO21_PERSISTENCE_H
