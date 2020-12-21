#include "fenetreprincipale.h"

fenetrePrincipale::fenetrePrincipale(QWidget *parent)
    : QWidget(parent) // Appel au constructeur de la classe de base
{
    //Créer les différents Objets
    nombreItemAAfficher = 5;
    message = new QLineEdit;
    vuePile = new QTableWidget(getNombreItemAAfficher(),1);
    commande = new QLineEdit;
    controleur = new Controleur(Interpreteur::obtenirInterpreteur(),pile);
    vueParametre = new class vueParametre();
    vueVariable = new class vueVariable();
    vueProgramme = new class vueProgramme();
    vueParametre->setFenetrePrincipale(this);
    vueVariable->setFenetrePrincipale(this);
    vueProgramme->setFenetrePrincipale(this);
    persistence = new Persistence;


    // Boutons pour le clavier
    afficherClavierCalculateur = new QPushButton("Clavier Calculateur");
    afficherClavierVariable = new QPushButton("Clavier Variable");
    afficherClavierCalculateur->setToolTip("Cliquez pour afficher/cacher le clavier");

    boutonVariable = new QPushButton("Variable");
    boutonProgramme = new QPushButton("Programme");
    boutonParametre = new QPushButton("Paramètre");

    bouton0 = new QPushButton("0");
    bouton1 = new QPushButton("1");
    bouton2 = new QPushButton("2");
    bouton3 = new QPushButton("3");
    bouton4 = new QPushButton("4");
    bouton5 = new QPushButton("5");
    bouton6 = new QPushButton("6");
    bouton7 = new QPushButton("7");
    bouton8 = new QPushButton("8");
    bouton9 = new QPushButton("9");
    boutonCLEAR = new QPushButton("CLEAR");
    boutonEVAL = new QPushButton("EVAL");
    boutonPLUS = new QPushButton("+");
    boutonMOINS = new QPushButton("-");
    boutonFOIS = new QPushButton("*");
    boutonDIVISER = new QPushButton("/");

    //CREATION LAYOUT DE L'APPLICATION + DES CLAVIERS
    couche = new QVBoxLayout;
    clavierNumerique = new QGridLayout;
    affichageClaviers = new QHBoxLayout;
    placeClaviers = new QHBoxLayout;
    affichageVues = new QHBoxLayout;

    //Layout horizontal des trois boutons de vues
    affichageVues->addWidget(boutonVariable);
    affichageVues->addWidget(boutonProgramme);
    affichageVues->addWidget(boutonParametre);

    //Layout horizontal des deux boutons d'affichages claviers
    affichageClaviers->addWidget(afficherClavierCalculateur);
    affichageClaviers->addWidget(afficherClavierVariable);

    //Layout Clavier Numérique
    clavierNumerique->addWidget(bouton1,0,0,1,1);
    clavierNumerique->addWidget(bouton2,0,1,1,1);
    clavierNumerique->addWidget(bouton3,0,2,1,1);
    clavierNumerique->addWidget(boutonPLUS,0,3,1,1);
    clavierNumerique->addWidget(bouton4,1,0,1,1);
    clavierNumerique->addWidget(bouton5,1,1,1,1);
    clavierNumerique->addWidget(bouton6,1,2,1,1);
    clavierNumerique->addWidget(boutonMOINS,1,3,1,1);
    clavierNumerique->addWidget(bouton7,2,0,1,1);
    clavierNumerique->addWidget(bouton8,2,1,1,1);
    clavierNumerique->addWidget(bouton9,2,2,1,1);
    clavierNumerique->addWidget(boutonFOIS,2,3,1,1);
    clavierNumerique->addWidget(boutonCLEAR,3,0,1,1);
    clavierNumerique->addWidget(bouton0,3,1,1,1);
    clavierNumerique->addWidget(boutonEVAL,3,2,1,1);
    clavierNumerique->addWidget(boutonDIVISER,3,3,1,1);

    //Layout Horizontal des deux claviers
    placeClaviers->addLayout(clavierNumerique);

    //LAYOUT Positionner les objets sur la fenêtre
    couche->addLayout(affichageVues);
    couche->addWidget(message);
    couche->addWidget(vuePile);
    couche->addWidget(commande);
    couche->addLayout(affichageClaviers);
    couche->addLayout(placeClaviers);

    //setLayout(couche); //On rattache le layout à la fenêtre (this)
    setLayout(couche);

    //3 : Mettre un titre à la fenêtre
    setWindowTitle("Comp'UT");
    //4 : Couleur à la barre + empêcher l'édition
    message->setStyleSheet("background-color :#16697a; color : #ffa62b");
    message->setReadOnly(true);
    //5 : Bonne apparence vuePile + non modifiable
    vuePile->setStyleSheet("background-color :#ffa62b; color : #db6400");
    //vuePile->verticalHeader();
    vuePile->horizontalHeader()->setVisible(false);
    vuePile->horizontalHeader()->setStretchLastSection(true);

    QStringList labelList;
    for(unsigned int i=1; i<=getNombreItemAAfficher(); i++){
        QString str = QString::number(i);
        str += " : ";
        labelList << str;
    }
    vuePile->setVerticalHeaderLabels(labelList);

    for(unsigned int i = 0; i<getNombreItemAAfficher();i++){
        vuePile->setItem(i,0,new QTableWidgetItem(""));
    }

    //=========================6 : Connecter signaux/slots===============
    QObject::connect(&pile, SIGNAL(modificationEtat()),this,SLOT(refresh()));
    connect(commande, SIGNAL(returnPressed()),this,SLOT(getNextCommande()));

    // CONNECTER LES BOUTONS DU CLAVIER NUMERIQUE
    QObject::connect(bouton1,SIGNAL(clicked()),this,SLOT(empile_1()));
    QObject::connect(bouton2,SIGNAL(clicked()),this,SLOT(empile_2()));
    QObject::connect(bouton3,SIGNAL(clicked()),this,SLOT(empile_3()));
    QObject::connect(bouton4,SIGNAL(clicked()),this,SLOT(empile_4()));
    QObject::connect(bouton5,SIGNAL(clicked()),this,SLOT(empile_5()));
    QObject::connect(bouton6,SIGNAL(clicked()),this,SLOT(empile_6()));
    QObject::connect(bouton7,SIGNAL(clicked()),this,SLOT(empile_7()));
    QObject::connect(bouton8,SIGNAL(clicked()),this,SLOT(empile_8()));
    QObject::connect(bouton9,SIGNAL(clicked()),this,SLOT(empile_9()));
    QObject::connect(bouton0,SIGNAL(clicked()),this,SLOT(empile_0()));
    QObject::connect(boutonPLUS,SIGNAL(clicked()),this,SLOT(empile_PLUS()));
    QObject::connect(boutonMOINS,SIGNAL(clicked()),this,SLOT(empile_MOINS()));
    QObject::connect(boutonFOIS,SIGNAL(clicked()),this,SLOT(empile_FOIS()));
    QObject::connect(boutonDIVISER,SIGNAL(clicked()),this,SLOT(empile_DIV()));
    QObject::connect(boutonCLEAR,SIGNAL(clicked()),this,SLOT(empile_CLEAR()));
    QObject::connect(boutonEVAL,SIGNAL(clicked()),this,SLOT(empile_EVAL()));

    //AFFICHER LE CLAVIER OU NON
    QObject::connect(afficherClavierCalculateur,SIGNAL(clicked()),this,SLOT(affichageClavierCalculateur()));

    //AFFICHER LES VUES
    QObject::connect(boutonVariable,SIGNAL(clicked()),this,SLOT(ouverture_vue_variable()));
    QObject::connect(boutonProgramme,SIGNAL(clicked()),this,SLOT(ouverture_vue_programme()));
    QObject::connect(boutonParametre,SIGNAL(clicked()),this,SLOT(ouverture_vue_parametre()));

    //PARAMETRE
    //QObject::connect(this->vueParametre, SIGNAL(valueChanged()),QComputer::vuePile,SLOT());
    //==========================================================================
    //7 : Focus barre de commande
    commande->setFocus();
}

// FIN DU CONSTRUCTEUR QCOMPUTER

//===================SLOTS QCOMPUTER

void fenetrePrincipale :: refresh() {
    //message-> setText(pile.getMessage()); ////////////////////////////A FAIRE
    //On efface tout
    for(unsigned int i = 0; i<getNombreItemAAfficher();i++){
        vuePile->item(i,0)->setText("");
    }

    //On parcourt le contenu de la pile et on affiche les éléments dans vuePile
    unsigned int nb = 0;
    for(auto it=pile.listeItems.begin();it!=pile.listeItems.end() && nb <getNombreItemAAfficher(); ++it, ++nb){
        vuePile->item(nb,0)->setText(it->obtenirLitterale().versString());
    }
}
void fenetrePrincipale::getNextCommande(){
    message->clear();
    QString saisieComplete = commande->text();
    QTextStream stream(&saisieComplete);
    QString unElement;
    do {
        stream >> unElement;
        if(unElement != ""){
            controleur->commande(unElement);
        }
    } while(unElement!="");
    if(message->text()==NULL){
        commande->clear();
    }
}

void fenetrePrincipale::affichageClavierCalculateur(){
    if (bouton0->isVisible()){
        bouton0->setVisible(false);
        bouton1->setVisible(false);
        bouton2->setVisible(false);
        bouton3->setVisible(false);
        bouton4->setVisible(false);
        bouton5->setVisible(false);
        bouton6->setVisible(false);
        bouton7->setVisible(false);
        bouton8->setVisible(false);
        bouton9->setVisible(false);
        boutonPLUS->setVisible(false);
        boutonMOINS->setVisible(false);
        boutonFOIS->setVisible(false);
        boutonDIVISER->setVisible(false);
        boutonCLEAR->setVisible(false);
        boutonEVAL->setVisible(false);
    } else {
        bouton0->setVisible(true);
        bouton1->setVisible(true);
        bouton2->setVisible(true);
        bouton3->setVisible(true);
        bouton4->setVisible(true);
        bouton5->setVisible(true);
        bouton6->setVisible(true);
        bouton7->setVisible(true);
        bouton8->setVisible(true);
        bouton9->setVisible(true);
        boutonPLUS->setVisible(true);
        boutonMOINS->setVisible(true);
        boutonFOIS->setVisible(true);
        boutonDIVISER->setVisible(true);
        boutonCLEAR->setVisible(true);
        boutonEVAL->setVisible(true);
    }
}

void fenetrePrincipale::ouvertureVueVariable(){
    vueVariable->show();
}

void fenetrePrincipale::ouvertureVueProgramme(){
    vueProgramme->show();
}

void fenetrePrincipale::ouvertureVueParametre(){
    vueParametre->show();
}

void fenetrePrincipale :: refreshMethode() {
    vuePile->setRowCount(getNombreItemAAfficher());
    QStringList labelList;
    for(unsigned int i=1; i<=getNombreItemAAfficher(); i++){
        QString str = QString::number(i);
        str += " : ";
        labelList << str;
    }
    vuePile->setVerticalHeaderLabels(labelList);
    //message-> setText(pile->getMessage());

    //On efface tout
    for(unsigned int i = 0; i<getNombreItemAAfficher();i++){
        vuePile->setItem(i,0,new QTableWidgetItem(""));
    }

    //On parcourt le contenu de la pile et on affiche les éléments dans vuePile
    unsigned int nb = 0;
    for(auto it=pile.listeItems.begin();it!=pile.listeItems.end() && nb <getNombreItemAAfficher(); ++it, ++nb){
        vuePile->item(nb,0)->setText(it->obtenirLitterale().versString());
    }

}
