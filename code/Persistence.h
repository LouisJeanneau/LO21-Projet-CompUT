//
// Created by Ismail Kadiri on 29/12/2020.
//

#ifndef PROJET_LO21_PERSISTENCE_H
#define PROJET_LO21_PERSISTENCE_H

#ifndef PERSISTENCE_H
#define PERSISTENCE_H
#include <QMap>
#include <QWidget>

class Persistence
{
    static Persistence instance;
    Persistence() = default;
    QMap<QString, QString> mapVariable;
    QMap<QString, QString> mapProgramme;
public:
    void setMapVariable(QString atome,QString variable){mapVariable.insert(atome,variable);};
    QMap<QString, QString> getMapVariable(){return mapVariable;};
    unsigned int getMapVariableSize(){return mapVariable.size();};
    void setMapProgramme(QString atome,QString variable){mapProgramme.insert(atome,variable);};
    QMap<QString, QString> getMapProgramme(){return mapProgramme;};
    unsigned int getMapProgrammeSize(){return mapProgramme.size();};
    static Persistence& getPersistence();
};

#endif // PERSISTENCE_H


#endif //PROJET_LO21_PERSISTENCE_H
