#ifndef PERSISTENCE_H
#define PERSISTENCE_H

#include <QMap>
#include <QWidget>

class Persistence
{

public:
    static QMap<QString, QString> mapVariable;
    static QMap<QString, QString> mapProgramme;
    Persistence();
    void setMapVariable(QString atome,QString variable){mapVariable.insert(atome,variable);}
    QMap<QString, QString> getMapVariable(){return mapVariable;}
    unsigned int getMapVariableSize(){return mapVariable.size();}
    void setMapProgramme(QString atome,QString programme){mapProgramme.insert(atome,programme);}
    QMap<QString, QString> getMapProgramme(){return mapProgramme;}
    unsigned int getMapProgrammeSize(){return mapProgramme.size();}
};

#endif // PERSISTENCE_H
