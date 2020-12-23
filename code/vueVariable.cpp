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
    tableVariable = new QTableWidget(Persistence::mapVariable.size(),2);
    listeVariable = new QVBoxLayout;
    layoutSaisie = new QHBoxLayout;
    texteSuppression = new QLabel("Choisir l'élément à supprimer :");
    choixSuppression = new QComboBox;
    validerSuppresion = new QPushButton("Supprimer");

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
    for (it = Persistence::mapVariable.begin(); it != Persistence::mapVariable.end(); it++){
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
    coucheSuppression->addWidget(validerSuppresion);
    listeVariable->addLayout(coucheSuppression);
    setLayout(listeVariable);
    QObject::connect(validerCreation,SIGNAL(clicked()),this,SLOT(ajouterVariable()));
    mapper = new QSignalMapper(this);
    QObject::connect(mapper,SIGNAL(mapped(QString)),this,SLOT(enleverMapVariable(QString)));
    QObject::connect(validerSuppresion,SIGNAL(clicked()),mapper,SLOT(map()));
    mapper->setMapping(validerSuppresion, choixSuppression->currentText());
    QObject::connect(choixSuppression,SIGNAL(currentIndexChanged()),this,SLOT(miseAJourMapper()));
}

void vueVariable::miseAJourMapper(){
    mapper->setMapping(validerSuppresion, choixSuppression->currentText());
}

void vueVariable::ajouterVariable(){
    QString saisieAtome = entreeAtome->text();
    QString saisieVariable = entreeVariable->text();
    if(saisieAtome!=NULL && saisieVariable!=NULL){
        entreeAtome->clear();
        entreeVariable->clear();
        Persistence::mapVariable.insert(saisieAtome,saisieVariable);
        refreshVariable();
    } else {
        QMessageBox::critical(this,"Erreur","Remplissez tous les champs avant de valider.");
    }
}

void vueVariable::refreshVariable(){
    tableVariable->setRowCount(Persistence::mapVariable.size());
    QMap<QString,QString>::iterator it;
    int i = 0;
    for (it = Persistence::mapVariable.begin(); it != Persistence::mapVariable.end(); it++){
        tableVariable->setCellWidget(i,0,new QLabel(""));
        tableVariable->setCellWidget(i,1,new QLabel(""));
        i++;
    }
    choixSuppression->clear();
    i = 0;
    for (it = Persistence::mapVariable.begin(); it != Persistence::mapVariable.end(); it++){
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
