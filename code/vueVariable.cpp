#include "vueVariable.h"

vueVariable::vueVariable(QWidget * parent):
    QWidget(parent)
{
    setWindowTitle("Modification des variables");
    texteCreationVariable = new QLabel("Entrez votre nouvelle variable :");
    texteVariableEnregistre = new QLabel("Variables enregistrées :");
    entreeAtome = new QLineEdit;
    entreeAtome->setPlaceholderText("ex: PI");
    entreeVariable = new QLineEdit;
    entreeVariable->setPlaceholderText("ex: 3.1415");
    validerCreation = new QPushButton("Valider");
    tableVariable = new QTableWidget(persistence.getMapVariableSize(),2);
    listeVariable = new QVBoxLayout;
    layoutSaisie = new QHBoxLayout;
    texteSuppression = new QLabel("Choisir l'élément à supprimer :");
    choixSuppression = new QComboBox;
    validerSuppression = new QPushButton("Supprimer");

    layoutSaisie->addWidget(entreeAtome);
    layoutSaisie->addWidget(entreeVariable);
    layoutSaisie->addWidget(validerCreation);
    listeVariable->addWidget(texteCreationVariable);
    listeVariable->addLayout(layoutSaisie);
    listeVariable->addWidget(texteVariableEnregistre);
    QStringList nomColonnesTableVariable;
    nomColonnesTableVariable << "Atomes";
    nomColonnesTableVariable << "Variable";
    tableVariable->setHorizontalHeaderLabels(nomColonnesTableVariable);
    tableVariable->verticalHeader()->setVisible(false);
    QMap<QString,QString>::iterator it;
    int i = 0;
    for (it = persistence.getMapVariable().begin(); it != persistence.getMapVariable().end(); it++){
        QLabel *key = new QLabel(it.key());
        QLabel *value = new QLabel(it.value());
        tableVariable->setCellWidget(i,0,key);
        tableVariable->setCellWidget(i,1,value);
        choixSuppression->insertItem(i,it.key());
        i++;
    }
    listeVariable->addWidget(tableVariable);
    listeVariable->addWidget(texteSuppression);
    QHBoxLayout *coucheSuppression = new QHBoxLayout;
    coucheSuppression->addWidget(choixSuppression);
    coucheSuppression->addWidget(validerSuppression);
    listeVariable->addLayout(coucheSuppression);
    setLayout(listeVariable);
    QObject::connect(validerCreation,SIGNAL(clicked()),this,SLOT(ajouterVariable()));
    QObject::connect(validerSuppression,SIGNAL(clicked()),this,SLOT(recupererKey()));
}

void vueVariable::recupererKey(){
    persistence.getMapVariable().remove(choixSuppression->currentText());
    refreshVariable();
}

void vueVariable::ajouterVariable(){
    QString saisieAtome = entreeAtome->text();
    saisieAtome = saisieAtome.toUpper();
    QString saisieVariable = entreeVariable->text();
    if(saisieAtome!=NULL && saisieVariable!=NULL){
        if(saisieAtome == '0' || saisieAtome == '1' || saisieAtome == '2' || saisieAtome == '3' || saisieAtome == '4' ||
           saisieAtome == '5' || saisieAtome == '6' || saisieAtome == '7' || saisieAtome == '8' || saisieAtome == '9' ||
           saisieAtome == '+' || saisieAtome == '-' || saisieAtome == '*' || saisieAtome == '/' ||
           saisieAtome == "CLEAR" || saisieAtome == "EVAL"){
           QMessageBox::critical(this,"Erreur","Cet atome ne peut pas être réutilisé.");
           entreeAtome->clear();
        } else {
            for (int i = 0; i<saisieVariable.size();i++){
                if (saisieVariable[i] == ' '){
                    QMessageBox::critical(this,"Erreur","Rentrez une unique expression sans espace pour une variable.");
                    return;
                }
            }
            entreeAtome->clear();
            entreeVariable->clear();
            QMap<QString,QString>::iterator it;
            int i = 0;
            for (it = persistence.getMapVariable().begin(); it != persistence.getMapVariable().end(); it++){
                if(saisieAtome == it.key()){
                    it.value()=saisieVariable;
                    i = 1;
                }
            }
            if(i == 0){
                persistence.getMapVariable().insert(saisieAtome,saisieVariable);
            }
            refreshVariable();
        }
    } else {
        QMessageBox::critical(this,"Erreur","Remplissez tous les champs avant de valider.");
    }
}

void vueVariable::refreshVariable(){
    tableVariable->setRowCount(persistence.getMapVariableSize());
    QMap<QString,QString>::iterator it;
    int i = 0;
    for (it = persistence.getMapVariable().begin(); it != persistence.getMapVariable().end(); it++){
        tableVariable->setCellWidget(i,0,new QLabel(""));
        tableVariable->setCellWidget(i,1,new QLabel(""));
        i++;
    }
    choixSuppression->clear();
    i = 0;
    for (it = persistence.getMapVariable().begin(); it != persistence.getMapVariable().end(); it++){
        QLabel *key = new QLabel(it.key());
        QLabel *value = new QLabel(it.value());
        tableVariable->setCellWidget(i,0,key);
        tableVariable->setCellWidget(i,1,value);
        choixSuppression->insertItem(i,it.key());
        i++;
    }
    fenetrePrincipale->refreshTableVariable();
};

void vueVariable::supprimerVariable(){

}
