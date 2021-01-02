#include "vueProgramme.h"

vueProgramme::vueProgramme(QWidget * parent):
    QWidget(parent)
{
    setWindowTitle("Modification des Programmes");
    setWindowModality(Qt::ApplicationModal);
    texteCreationProgramme = new QLabel("Entrez votre nouveau programme :");
    texteProgrammeEnregistre = new QLabel("Programmes enregistrées :");
    entreeAtomePG = new QLineEdit;
    entreeAtomePG->setPlaceholderText("ex: ABS");
    entreeProgramme = new QLineEdit;
    entreeProgramme->setPlaceholderText("ex: [ DUP 0 < [NEG] IFT ]");
    validerCreationPG = new QPushButton("Valider");
    tableProgramme = new QTableWidget(persistence.obtenirTailleMapProgramme(), 2);
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
    tableProgramme->horizontalHeader()->setStretchLastSection(true);
    tableProgramme->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    QMap<QString,QString>::iterator it;
    int i = 0;
    auto mapProgramme = persistence.obtenirMapProgramme();
    for(auto it = mapProgramme.begin(); it != mapProgramme.end(); it++){
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
    //Shortcut
    QShortcut* shortcut = new QShortcut(QKeySequence(Qt::Key_Return), this);
    QObject::connect(shortcut, SIGNAL(activated()),validerCreationPG, SLOT(click()));
}

void vueProgramme::recupererKey(){
    persistence.supprimerProgramme(choixSuppressionPG->currentText());
}

void vueProgramme::ajouterProgramme() {
    QString saisieAtomePG = entreeAtomePG->text();
    saisieAtomePG = saisieAtomePG.toUpper();
    QString saisieProgramme = entreeProgramme->text();
    try {
        persistence.ajouterProgramme(saisieAtomePG, saisieProgramme);
    } catch (ComputerException &ce) {
        QMessageBox::critical(this,"Erreur",ce.what());
    }
    entreeAtomePG->clear();
    entreeProgramme->clear();
    entreeAtomePG->setFocus();
    refreshProgramme();
}

void vueProgramme::refreshProgramme(){
    std::cout << "Salut moi c'est refreshProgramme" << std::endl;
    tableProgramme->setRowCount(persistence.obtenirTailleMapProgramme());
    int i = 0;
    auto mapProgramme = persistence.obtenirMapProgramme();
    for (auto it = mapProgramme.begin(); it != mapProgramme.end(); it++){
        tableProgramme->setCellWidget(i,0,new QLabel(""));
        tableProgramme->setCellWidget(i,1,new QLabel(""));
        i++;
    }
    choixSuppressionPG->clear();
    i = 0;
    for (auto it = mapProgramme.begin(); it != mapProgramme.end(); it++){
        QLabel *key = new QLabel(it.key());
        QLabel *value = new QLabel(it.value());
        tableProgramme->setCellWidget(i,0,key);
        tableProgramme->setCellWidget(i,1,value);
        choixSuppressionPG->insertItem(i,it.key());
        i++;
    }
    fenetrePrincipale->refreshTableVariableProgramme();
}

void vueProgramme::appelRefreshProgramme() {
    refreshProgramme();
};



