#ifndef PERSISTENCE_H
#define PERSISTENCE_H
#include <QMap>
#include <QWidget>

class Persistence
{

public:
    static QMap<QString, QString> mapVariable;
    static QMap<QString, QString> mapProgramme;
    Persistence(){
        mapVariable.insert("VAR","42");
    };
    void setMapVariable(QString atome,QString variable){mapVariable.insert(atome,variable);};
    QMap<QString, QString> getMapVariable(){return mapVariable;};
    unsigned int getMapVariableSize(){return mapVariable.size();};
};

#endif // PERSISTENCE_H
