#ifndef PERSISTENCE_H
#define PERSISTENCE_H

#include <QMap>
#include <QWidget>

class Persistence
{
    QMap<QString, QString> mapVariable;
    QMap<QString, QString> mapProgramme;
public:
    Persistence(){
        mapVariable.insert("VAR","42");
    };
    void setMapVariable(QString atome,QString variable){mapVariable.insert(atome,variable);}
    QMap<QString, QString> getMapVariable(){return mapVariable;}
    unsigned int getMapVariableSize(){return mapVariable.size();}
    void setMapProgramme(QString atome,QString programme){mapProgramme.insert(atome,programme);}
    QMap<QString, QString> getMapProgramme(){return mapProgramme;}
    unsigned int getMapProgrammeSize(){return mapProgramme.size();}
};

#endif // PERSISTENCE_H
