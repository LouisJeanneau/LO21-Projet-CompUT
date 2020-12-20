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
    listeVariable = new QVBoxLayout;
    layoutSaisie = new QHBoxLayout;

    layoutSaisie->addWidget(entreeAtome);
    layoutSaisie->addWidget(entreeVariable);
    layoutSaisie->addWidget(validerCreation);
    listeVariable->addWidget(texteCreationVariable);
    listeVariable->addLayout(layoutSaisie);
    listeVariable->addWidget(texteVariableEnregistre);
    //QMap<QString, QString> mapVariable = fenetrePrincipale->getMapVariable();
    /*
    for(auto e : fenetrePrincipale->getMapVariable().toStdMap()){
       QByteArray ba = e.first.toLocal8Bit();
       QByteArray bb = e.second.toLocal8Bit();
       char * atome = ba.data();
       char * desc = bb.data();
       QLabel *atome_affichage_variable = new QLabel(atome);
       QLabel *description_affichage_variable = new QLabel(desc);
       QMessageBox::critical(this,"Erreur","Remplissez tous les champs avant de valider.");
       QHBoxLayout *layout_ligne_variable = new QHBoxLayout();
       layout_ligne_variable->addWidget(atome_affichage_variable);
       layout_ligne_variable->addWidget(description_affichage_variable);
       listeVariable->addLayout(layout_ligne_variable);
    }*/

    setLayout(listeVariable);

    QObject::connect(validerCreation,SIGNAL(clicked()),this,SLOT(ajouterVariable()));
}

void vueVariable::ajouterVariable(){
    QString saisieAtome = entreeAtome->text();
    QString saisieVariable = entreeVariable->text();
    if(saisieAtome!=NULL && saisieVariable!=NULL){
        entreeAtome->clear();
        entreeVariable->clear();
        fenetrePrincipale->setVariable(saisieAtome,saisieVariable);
        this->refreshVariable();
    } else {
        QMessageBox::critical(this,"Erreur","Remplissez tous les champs avant de valider.");
    }
}

void vueVariable::refreshVariable(){

};
