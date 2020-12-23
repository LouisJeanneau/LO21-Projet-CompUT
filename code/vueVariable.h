#ifndef VUEVARIABLE_H
#define VUEVARIABLE_H
#include "fenetreprincipale.h"

class fenetrePrincipale;

class vueVariable : public QWidget {
Q_OBJECT
    QLineEdit *entreeAtome;
    QLineEdit *entreeVariable;
    QPushButton *validerCreation;
    QHBoxLayout *layoutSaisie;
    QVBoxLayout *listeVariable;
    QLabel *texteCreationVariable;
    QLabel *texteVariableEnregistre;
    QTableWidget *tableVariable;
    fenetrePrincipale *fenetrePrincipale;
    QLabel *texteSuppression;
    QComboBox *choixSuppression;
    QPushButton *validerSuppresion;
    QSignalMapper * mapper;
public:
explicit vueVariable(QWidget *parent = 0);
    ~vueVariable(){};
    void setFenetrePrincipale(class fenetrePrincipale* fenetrePrincipaleCopie){fenetrePrincipale = fenetrePrincipaleCopie;}
    class fenetrePrincipale *getFenetrePrincipale(){return fenetrePrincipale;}
    void refreshVariable();
public slots:
void ajouterVariable();
void supprimerVariable();
void enleverMapVariable(QString key){
    Persistence::mapVariable.remove(key);
    refreshVariable();
}
void miseAJourMapper();
};
#endif // VUEVARIABLE_H
