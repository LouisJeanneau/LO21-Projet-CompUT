#include "fenetreprincipale.h"

fenetrePrincipale::fenetrePrincipale(QWidget *parent)
    : QWidget(parent) // Appel au constructeur de la classe de base
{
    //Créer les différents Objets
    NbItemAAfficher = 5;
    message = new QLineEdit;
    vuePile = new QTableWidget(getNombreItemAAfficher(),1);
    commande = new QLineEdit;
    controleur = new Controleur(Interpreteur::obtenirInterpreteur(),pile);
    vue_param = new vueParametre();
    vue_variable = new vueVariable();
    vue_programme = new vueProgramme();
    vue_param->setFenetrePrincipale(this);
    vue_variable->setFenetrePrincipale(this);
    vue_programme->setFenetrePrincipale(this);
    persistence = new Persistence;


    // Boutons pour le clavier
    afficherClavierCalculateur = new QPushButton("Clavier Calculateur");
    afficherClavierVariable = new QPushButton("Clavier Variable");
    afficherClavierCalculateur->setToolTip("Cliquez pour afficher/cacher le clavier");

    bouton_Variable = new QPushButton("Variable");
    bouton_Programme = new QPushButton("Programme");
    bouton_Parametre = new QPushButton("Paramètre");

    bouton_0 = new QPushButton("0");
    bouton_1 = new QPushButton("1");
    bouton_2 = new QPushButton("2");
    bouton_3 = new QPushButton("3");
    bouton_4 = new QPushButton("4");
    bouton_5 = new QPushButton("5");
    bouton_6 = new QPushButton("6");
    bouton_7 = new QPushButton("7");
    bouton_8 = new QPushButton("8");
    bouton_9 = new QPushButton("9");
    bouton_CLEAR = new QPushButton("CLEAR");
    bouton_EVAL = new QPushButton("EVAL");
    bouton_PLUS = new QPushButton("+");
    bouton_MOINS = new QPushButton("-");
    bouton_FOIS = new QPushButton("*");
    bouton_DIV = new QPushButton("/");

    //CREATION LAYOUT DE L'APPLICATION + DES CLAVIERS
    couche = new QVBoxLayout;
    clavierNumerique = new QGridLayout;
    affichageClaviers = new QHBoxLayout;
    placeClaviers = new QHBoxLayout;
    layout_vues = new QHBoxLayout;

    //Layout horizontal des trois boutons de vues
    layout_vues->addWidget(bouton_Variable);
    layout_vues->addWidget(bouton_Programme);
    layout_vues->addWidget(bouton_Parametre);

    //Layout horizontal des deux boutons d'affichages claviers
    affichageClaviers->addWidget(afficherClavierCalculateur);
    affichageClaviers->addWidget(afficherClavierVariable);

    //Layout Clavier Numérique
    clavierNumerique->addWidget(bouton_1,0,0,1,1);
    clavierNumerique->addWidget(bouton_2,0,1,1,1);
    clavierNumerique->addWidget(bouton_3,0,2,1,1);
    clavierNumerique->addWidget(bouton_PLUS,0,3,1,1);
    clavierNumerique->addWidget(bouton_4,1,0,1,1);
    clavierNumerique->addWidget(bouton_5,1,1,1,1);
    clavierNumerique->addWidget(bouton_6,1,2,1,1);
    clavierNumerique->addWidget(bouton_MOINS,1,3,1,1);
    clavierNumerique->addWidget(bouton_7,2,0,1,1);
    clavierNumerique->addWidget(bouton_8,2,1,1,1);
    clavierNumerique->addWidget(bouton_9,2,2,1,1);
    clavierNumerique->addWidget(bouton_FOIS,2,3,1,1);
    clavierNumerique->addWidget(bouton_CLEAR,3,0,1,1);
    clavierNumerique->addWidget(bouton_0,3,1,1,1);
    clavierNumerique->addWidget(bouton_EVAL,3,2,1,1);
    clavierNumerique->addWidget(bouton_DIV,3,3,1,1);

    //Layout Horizontal des deux claviers
    placeClaviers->addLayout(clavierNumerique);

    //LAYOUT Positionner les objets sur la fenêtre
    couche->addLayout(layout_vues);
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
    QObject::connect(bouton_1,SIGNAL(clicked()),this,SLOT(empile_1()));
    QObject::connect(bouton_2,SIGNAL(clicked()),this,SLOT(empile_2()));
    QObject::connect(bouton_3,SIGNAL(clicked()),this,SLOT(empile_3()));
    QObject::connect(bouton_4,SIGNAL(clicked()),this,SLOT(empile_4()));
    QObject::connect(bouton_5,SIGNAL(clicked()),this,SLOT(empile_5()));
    QObject::connect(bouton_6,SIGNAL(clicked()),this,SLOT(empile_6()));
    QObject::connect(bouton_7,SIGNAL(clicked()),this,SLOT(empile_7()));
    QObject::connect(bouton_8,SIGNAL(clicked()),this,SLOT(empile_8()));
    QObject::connect(bouton_9,SIGNAL(clicked()),this,SLOT(empile_9()));
    QObject::connect(bouton_0,SIGNAL(clicked()),this,SLOT(empile_0()));
    QObject::connect(bouton_PLUS,SIGNAL(clicked()),this,SLOT(empile_PLUS()));
    QObject::connect(bouton_MOINS,SIGNAL(clicked()),this,SLOT(empile_MOINS()));
    QObject::connect(bouton_FOIS,SIGNAL(clicked()),this,SLOT(empile_FOIS()));
    QObject::connect(bouton_DIV,SIGNAL(clicked()),this,SLOT(empile_DIV()));
    QObject::connect(bouton_CLEAR,SIGNAL(clicked()),this,SLOT(empile_CLEAR()));
    QObject::connect(bouton_EVAL,SIGNAL(clicked()),this,SLOT(empile_EVAL()));

    //AFFICHER LE CLAVIER OU NON
    QObject::connect(afficherClavierCalculateur,SIGNAL(clicked()),this,SLOT(affichageClavierCalculateur()));

    //AFFICHER LES VUES
    QObject::connect(bouton_Variable,SIGNAL(clicked()),this,SLOT(ouverture_vue_variable()));
    QObject::connect(bouton_Programme,SIGNAL(clicked()),this,SLOT(ouverture_vue_programme()));
    QObject::connect(bouton_Parametre,SIGNAL(clicked()),this,SLOT(ouverture_vue_parametre()));

    //PARAMETRE
    //QObject::connect(this->vue_param, SIGNAL(valueChanged()),QComputer::vuePile,SLOT());
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
    for(auto it=pile.listeItems;it!=pile->end() && nb <getNombreItemAAfficher(); ++it, ++nb){
        vuePile->item(nb,0)->setText((*it).toString());
    }
    auto it=listeItems.begin(); it!=listeItems.end(); it++
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
    if (bouton_0->isVisible()){
        bouton_0->setVisible(false);
        bouton_1->setVisible(false);
        bouton_2->setVisible(false);
        bouton_3->setVisible(false);
        bouton_4->setVisible(false);
        bouton_5->setVisible(false);
        bouton_6->setVisible(false);
        bouton_7->setVisible(false);
        bouton_8->setVisible(false);
        bouton_9->setVisible(false);
        bouton_PLUS->setVisible(false);
        bouton_MOINS->setVisible(false);
        bouton_FOIS->setVisible(false);
        bouton_DIV->setVisible(false);
        bouton_CLEAR->setVisible(false);
        bouton_EVAL->setVisible(false);
    } else {
        bouton_0->setVisible(true);
        bouton_1->setVisible(true);
        bouton_2->setVisible(true);
        bouton_3->setVisible(true);
        bouton_4->setVisible(true);
        bouton_5->setVisible(true);
        bouton_6->setVisible(true);
        bouton_7->setVisible(true);
        bouton_8->setVisible(true);
        bouton_9->setVisible(true);
        bouton_PLUS->setVisible(true);
        bouton_MOINS->setVisible(true);
        bouton_FOIS->setVisible(true);
        bouton_DIV->setVisible(true);
        bouton_CLEAR->setVisible(true);
        bouton_EVAL->setVisible(true);
    }
}

void fenetrePrincipale::ouverture_vue_variable(){
    vue_variable->show();
}

void fenetrePrincipale::ouverture_vue_programme(){
    vue_programme->show();
}

void fenetrePrincipale::ouverture_vue_parametre(){
    vue_param->show();
}

void fenetrePrincipale :: refreshMethode() {
    vuePile->setRowCount(getNumberItemAAfficher());
    QStringList labelList;
    for(unsigned int i=1; i<=getNumberItemAAfficher(); i++){
        QString str = QString::number(i);
        str += " : ";
        labelList << str;
    }
    vuePile->setVerticalHeaderLabels(labelList);
    message-> setText(pile->getMessage());

    //On efface tout
    for(unsigned int i = 0; i<getNumberItemAAfficher();i++){
        vuePile->setItem(i,0,new QTableWidgetItem(""));
    }

    //On parcourt le contenu de la pile et on affiche les éléments dans vuePile
    unsigned int nb = 0;
    for(Pile::iterator it=pile->begin();it!=pile->end() && nb <getNumberItemAAfficher(); ++it, ++nb){
        vuePile->item(nb,0)->setText((*it).toString());
    }

}
