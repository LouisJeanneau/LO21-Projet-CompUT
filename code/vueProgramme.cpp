#include "vueProgramme.h"

vueProgramme::vueProgramme(QWidget * parent):
    QWidget(parent)
{
    setWindowTitle("Modification des Programmes");
    texteCreationProgramme = new QLabel("Entrez votre nouveau programme :");
    texteProgrammeEnregistre = new QLabel("Programmes enregistrées :");
    entreeAtomePG = new QLineEdit;
    entreeAtomePG->setPlaceholderText("ex: ABS");
    entreeProgramme = new QLineEdit;
    entreeProgramme->setPlaceholderText("ex: [ DUP 0 < [NEG] IFT ]");
    validerCreationPG = new QPushButton("Valider");
    listeProgramme = new QVBoxLayout;
    layoutSaisiePG = new QHBoxLayout;

    layoutSaisiePG->addWidget(entreeAtomePG);
    layoutSaisiePG->addWidget(entreeProgramme);
    layoutSaisiePG->addWidget(validerCreationPG);
    listeProgramme->addWidget(texteCreationProgramme);
    listeProgramme->addLayout(layoutSaisiePG);
    listeProgramme->addWidget(texteProgrammeEnregistre);
    setLayout(listeProgramme);

    QObject::connect(validerCreationPG,SIGNAL(clicked()),this,SLOT(ajouterProgramme()));
}

void vueProgramme::ajouterProgramme(){
    QString saisieAtomePG = entreeAtomePG->text();
    QString saisieProgramme = entreeProgramme->text();
    if(saisieAtomePG!=NULL && saisieProgramme!=NULL){
        entreeAtomePG->clear();
        entreeProgramme->clear();
        /*
        Variable *variable = new Variable();
        variable->setAtomeVariable(&saisieAtomePG);
        variable->setDescriptionVariable(&saisieProgramme);
        QHBoxLayout *layoutVariable = new QHBoxLayout;

        layoutVariable->addWidget(variable);
        */

    } else {
        QMessageBox::critical(this,"Erreur","Remplissez tous les champs avant de valider.");
    }
}
