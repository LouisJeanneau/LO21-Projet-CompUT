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
    tableProgramme = new QTableWidget(persistence.getMapProgrammeSize(),2);
    listeProgramme = new QVBoxLayout;
    layoutSaisiePG = new QHBoxLayout;
    texteSuppressionPG = new QLabel("Choisir l'élément à supprimer :");
    choixSuppressionPG = new QComboBox;
    validerSuppresionPG = new QPushButton("Supprimer");

    layoutSaisiePG->addWidget(entreeAtomePG);
    layoutSaisiePG->addWidget(entreeProgramme);
    layoutSaisiePG->addWidget(validerCreationPG);
    listeProgramme->addWidget(texteCreationProgramme);
    listeProgramme->addLayout(layoutSaisiePG);
    listeProgramme->addWidget(texteProgrammeEnregistre);

    QStringList nomColonnesTableProgramme;
    nomColonnesTableProgramme << "Atomes";
    nomColonnesTableProgramme << "Programmes";
    tableProgramme->setHorizontalHeaderLabels(nomColonnesTableProgramme);
    tableProgramme->verticalHeader()->setVisible(false);
    QMap<QString,QString>::iterator it;
    int i = 0;
    for (auto it = persistence.getMapProgramme().begin(); it != persistence.getMapProgramme().end(); it++){
        QLabel *key = new QLabel(it.key());
        QLabel *value = new QLabel(it.value());
        tableProgramme->setCellWidget(i,0,key);
        tableProgramme->setCellWidget(i,1,value);
        choixSuppressionPG->insertItem(i,it.key());
        i++;
    }
    listeProgramme->addWidget(tableProgramme);
    listeProgramme->addWidget(texteSuppressionPG);
    QHBoxLayout *coucheSuppression = new QHBoxLayout;
    coucheSuppression->addWidget(choixSuppressionPG);
    coucheSuppression->addWidget(validerSuppresionPG);
    listeProgramme->addLayout(coucheSuppression);

    setLayout(listeProgramme);

    QObject::connect(validerCreationPG,SIGNAL(clicked()),this,SLOT(ajouterProgramme()));
    QObject::connect(validerSuppresionPG,SIGNAL(clicked()),this,SLOT(recupererKey()));
}

void vueProgramme::recupererKey(){
    persistence.getMapProgramme().remove(choixSuppressionPG->currentText());
    refreshProgramme();
}

void vueProgramme::ajouterProgramme(){
    QString saisieAtomePG = entreeAtomePG->text();
    saisieAtomePG = saisieAtomePG.toUpper();
    QString saisieProgramme = entreeProgramme->text();
    if(saisieAtomePG!=NULL && saisieProgramme!=NULL){
        if(saisieAtomePG == '0' || saisieAtomePG == '1' || saisieAtomePG == '2' || saisieAtomePG == '3' || saisieAtomePG == '4' ||
           saisieAtomePG == '5' || saisieAtomePG == '6' || saisieAtomePG == '7' || saisieAtomePG == '8' || saisieAtomePG == '9' ||
           saisieAtomePG == '+' || saisieAtomePG == '-' || saisieAtomePG == '*' || saisieAtomePG == '/' ||
           saisieAtomePG == "CLEAR" || saisieAtomePG == "EVAL"){
           QMessageBox::critical(this,"Erreur","Cet atome ne peut pas être réutilisé.");
           entreeAtomePG->clear();
        } else {
            int estProgramme = 0;
            for (int i = 0; i<saisieProgramme.size();i++){
                if (saisieProgramme[i] == ' '){
                    estProgramme = 1;
                }
            }
            if(estProgramme == 0){
                QMessageBox::critical(this,"Erreur","Pour enregistrer une variable, utilisez l'onglet Variable.");
                return;
            }
            entreeAtomePG->clear();
            entreeProgramme->clear();
            QMap<QString,QString>::iterator it;
            int i = 0;
            for (it = persistence.getMapProgramme().begin(); it != persistence.getMapProgramme().end(); it++){
                if(saisieAtomePG == it.key()){
                    it.value()=saisieProgramme;
                    i = 1;
                }
            }
            if(i == 0){
                persistence.getMapProgramme().insert(saisieAtomePG,saisieProgramme);
            }
            refreshProgramme();
        }
    } else {
        QMessageBox::critical(this,"Erreur","Remplissez tous les champs avant de valider.");
    }
}

void vueProgramme::refreshProgramme(){
    tableProgramme->setRowCount(persistence.getMapProgrammeSize());
    QMap<QString,QString>::iterator it;
    int i = 0;
    for (it = persistence.getMapProgramme().begin(); it != persistence.getMapProgramme().end(); it++){
        tableProgramme->setCellWidget(i,0,new QLabel(""));
        tableProgramme->setCellWidget(i,1,new QLabel(""));
        i++;
    }
    choixSuppressionPG->clear();
    i = 0;
    for (it = persistence.getMapProgramme().begin(); it != persistence.getMapProgramme().end(); it++){
        QLabel *key = new QLabel(it.key());
        QLabel *value = new QLabel(it.value());
        tableProgramme->setCellWidget(i,0,key);
        tableProgramme->setCellWidget(i,1,value);
        choixSuppressionPG->insertItem(i,it.key());
        i++;
    }
    fenetrePrincipale->refreshTableVariable();
};

void vueProgramme::supprimerProgramme(){

}
