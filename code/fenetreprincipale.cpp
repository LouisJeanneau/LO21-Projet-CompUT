#include "fenetreprincipale.h"
#include "Pile.h"


// =======================================   CONSTRUCTEUR   ======================================= //
fenetrePrincipale::fenetrePrincipale(QWidget *parent)
        : QWidget(parent)
{

    // ===== CREATION DES OBJETS =====
    nombreItemAAfficher = 5;
    message = new QLineEdit;
    vuePile = new QTableWidget(getNombreItemAAfficher(), 1);
    commande = new QLineEdit;


    // ===== CREATION DES VUES =====
    vueParametre = new class vueParametre();
    vueVariable = new class vueVariable();
    vueProgramme = new class vueProgramme();
    vueParametre->setFenetrePrincipale(this);
    vueVariable->setFenetrePrincipale(this);
    vueProgramme->setFenetrePrincipale(this);

    // ===== BOUTON POUR L'AFFICHAGE DES VUES =====
    boutonVariable = new QPushButton("Variable");
    boutonProgramme = new QPushButton("Programme");
    boutonParametre = new QPushButton("Paramètre");

    // ===== LIEN AVEC L'INTERPRETEUR ET LA SAUVEGARDE =====
    refIntp = new Interpreteur(Interpreteur::obtenirInterpreteur());
    sauvegarde = new class Sauvegarde();
    sauvegarde->setFenetrePrincipale(this);

    // ===== BOUTON POUR L'AFFICHAGE DES CLAVIERS =====
    afficherClavierCalculateur = new QPushButton("Afficher Clavier Calculateur");
    afficherClavierVariable = new QPushButton("Afficher Clavier Variable");
    afficherClavierCalculateur->setToolTip("Cliquez pour afficher/cacher le clavier");
    cacherClavierCalculateur = new QPushButton("Cacher Clavier Calculateur");
    cacherClavierVariable = new QPushButton("Cacher Clavier Variable");
    afficherClavierCalculateur->setVisible(false);
    afficherClavierVariable->setVisible(false);

    // CREATION DE L'AFFICHAGE CLAVIER NUMERIQUE
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

    // CREATION DE L'AFFICHAGE CLAVIER VARIABLE PROGRAMME
    if (persistance.obtenirTailleMapVariable() > persistance.obtenirTailleMapProgramme()) {
        tableBoutonVariableProgramme = new QTableWidget(persistance.obtenirTailleMapVariable(), 2);
    } else {
        tableBoutonVariableProgramme = new QTableWidget(persistance.obtenirTailleMapProgramme(), 2);
    }

    // ===== CREATIONS DES LAYOUT =====
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
    affichageClaviers->addWidget(cacherClavierCalculateur);
    affichageClaviers->addWidget(afficherClavierVariable);
    affichageClaviers->addWidget(cacherClavierVariable);

    //Layout Clavier Numérique
    clavierNumerique->addWidget(bouton1, 0, 0, 1, 1);
    clavierNumerique->addWidget(bouton2, 0, 1, 1, 1);
    clavierNumerique->addWidget(bouton3, 0, 2, 1, 1);
    clavierNumerique->addWidget(boutonPLUS, 0, 3, 1, 1);
    clavierNumerique->addWidget(bouton4, 1, 0, 1, 1);
    clavierNumerique->addWidget(bouton5, 1, 1, 1, 1);
    clavierNumerique->addWidget(bouton6, 1, 2, 1, 1);
    clavierNumerique->addWidget(boutonMOINS, 1, 3, 1, 1);
    clavierNumerique->addWidget(bouton7, 2, 0, 1, 1);
    clavierNumerique->addWidget(bouton8, 2, 1, 1, 1);
    clavierNumerique->addWidget(bouton9, 2, 2, 1, 1);
    clavierNumerique->addWidget(boutonFOIS, 2, 3, 1, 1);
    clavierNumerique->addWidget(boutonCLEAR, 3, 0, 1, 1);
    clavierNumerique->addWidget(bouton0, 3, 1, 1, 1);
    clavierNumerique->addWidget(boutonEVAL, 3, 2, 1, 1);
    clavierNumerique->addWidget(boutonDIVISER, 3, 3, 1, 1);

    //Layout Horizontal des deux claviers
    placeClaviers->addLayout(clavierNumerique);
    placeClaviers->addWidget(tableBoutonVariableProgramme);

    //LAYOUT Positionner les objets sur la fenêtre
    couche->addLayout(affichageVues);
    couche->addWidget(message);
    couche->addWidget(vuePile);
    couche->addWidget(commande);
    couche->addLayout(affichageClaviers);
    couche->addLayout(placeClaviers);

    //setLayout(couche); //On rattache le layout à la fenêtre (this)
    setLayout(couche);

    // ===== PARAMETRAGE DES DIFFERENTS WIDGETS =====

    // Mettre un titre à la fenêtre
    setWindowTitle("Comp'UT");
    setWindowIcon(QIcon(QCoreApplication::applicationDirPath() + "calculator.ico"));

    // Couleur à la barre + empêcher l'édition
    message->setStyleSheet("background-color :#456268; color : #fcf8ec");
    message->setReadOnly(true);

    // Focus automatique sur la commande
    commande->setFocus();
    QRegularExpression rx("([A-Z0-9a-z !.=<>+\\-/*'\\[\\]])*");
    QValidator *validator = new QRegularExpressionValidator(rx,this);
    commande->setValidator(validator);

    // Bonne apparence vuePile + non modifiable
    vuePile->setStyleSheet("background-color :#d0e8f2; color : #456268");
    vuePile->horizontalHeader()->setVisible(false);
    vuePile->horizontalHeader()->setStretchLastSection(true);
    vuePile->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // Initialisation des headers de la pile
    QStringList labelList;
    for (int i = 1; i <= getNombreItemAAfficher(); i++) {
        QString str = QString::number(i);
        str += " : ";
        labelList << str;
    }
    vuePile->setVerticalHeaderLabels(labelList);

    // Vidage de la pile à l'ouverture
    for (int i = 0; i < getNombreItemAAfficher(); i++) {
        vuePile->setItem(i, 0, new QTableWidgetItem(""));
    }

    // Remplissage de la pile
    int nb = 0;
    for (auto it = pile.copierListeItems().begin();
         it != pile.copierListeItems().end() && nb < getNombreItemAAfficher(); ++it, ++nb) {
        vuePile->item(nb, 0)->setText(it->obtenirLitterale().versString());
    }

    // ===== TEST BOUTON VARIABLE =====
    QStringList nomColonnesVariableProgramme;
    nomColonnesVariableProgramme << "Variables";
    nomColonnesVariableProgramme << "Programmes";
    tableBoutonVariableProgramme->setHorizontalHeaderLabels(nomColonnesVariableProgramme);
    tableBoutonVariableProgramme->verticalHeader()->setVisible(false);
    tableBoutonVariableProgramme->horizontalHeader()->setStretchLastSection(true);
    tableBoutonVariableProgramme->verticalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    tableBoutonVariableProgramme->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);

    QMap<QString, QString>::iterator it;
    int i = 0;
    auto mapVariable = persistance.obtenirMapVariable();
    for (auto it = mapVariable.begin(); it != mapVariable.end(); it++) {
        creerNouveauBoutonVariable(i, it.key(), it.value());
        i++;
    }
    i = 0;
    auto mapProgramme = persistance.obtenirMapProgramme();
    for (auto it = mapProgramme.begin(); it != mapProgramme.end(); it++) {
        creerNouveauBoutonProgramme(i, it.key(), it.value());
        i++;
    }


    // ===== Connecter signaux/slots =====
    QObject::connect(&Persistance::obtenirPersistance(), SIGNAL(actualiserAffichage()), vueVariable,SLOT(appelRefreshVariable()));
    QObject::connect(&Persistance::obtenirPersistance(), SIGNAL(actualiserAffichage()), vueProgramme,SLOT(appelRefreshProgramme()));
    connect(commande, SIGNAL(returnPressed()), this, SLOT(getNextCommande()));

    // CONNECTER LES BOUTONS DU CLAVIER NUMERIQUE
    QObject::connect(bouton1, SIGNAL(clicked()), this, SLOT(empile_1()));
    QObject::connect(bouton2, SIGNAL(clicked()), this, SLOT(empile_2()));
    QObject::connect(bouton3, SIGNAL(clicked()), this, SLOT(empile_3()));
    QObject::connect(bouton4, SIGNAL(clicked()), this, SLOT(empile_4()));
    QObject::connect(bouton5, SIGNAL(clicked()), this, SLOT(empile_5()));
    QObject::connect(bouton6, SIGNAL(clicked()), this, SLOT(empile_6()));
    QObject::connect(bouton7, SIGNAL(clicked()), this, SLOT(empile_7()));
    QObject::connect(bouton8, SIGNAL(clicked()), this, SLOT(empile_8()));
    QObject::connect(bouton9, SIGNAL(clicked()), this, SLOT(empile_9()));
    QObject::connect(bouton0, SIGNAL(clicked()), this, SLOT(empile_0()));
    QObject::connect(boutonPLUS, SIGNAL(clicked()), this, SLOT(empile_PLUS()));
    QObject::connect(boutonMOINS, SIGNAL(clicked()), this, SLOT(empile_MOINS()));
    QObject::connect(boutonFOIS, SIGNAL(clicked()), this, SLOT(empile_FOIS()));
    QObject::connect(boutonDIVISER, SIGNAL(clicked()), this, SLOT(empile_DIV()));
    QObject::connect(boutonCLEAR, SIGNAL(clicked()), this, SLOT(empile_CLEAR()));
    QObject::connect(boutonEVAL, SIGNAL(clicked()), this, SLOT(empile_EVAL()));

    //AFFICHER LE CLAVIER OU NON
    QObject::connect(afficherClavierCalculateur, SIGNAL(clicked()), this, SLOT(affichageClavierCalculateur()));
    QObject::connect(afficherClavierVariable, SIGNAL(clicked()), this, SLOT(affichageClavierVariable()));
    QObject::connect(cacherClavierCalculateur, SIGNAL(clicked()), this, SLOT(cacheClavierCalculateur()));
    QObject::connect(cacherClavierVariable, SIGNAL(clicked()), this, SLOT(cacheClavierVariable()));

    //AFFICHER LES VUES
    QObject::connect(boutonVariable, SIGNAL(clicked()), this, SLOT(ouvertureVueVariable()));
    QObject::connect(boutonProgramme, SIGNAL(clicked()), this, SLOT(ouvertureVueProgramme()));
    QObject::connect(boutonParametre, SIGNAL(clicked()), this, SLOT(ouvertureVueParametre()));

    // ===== LANCER LA RECUPERATION SAUVEGARDE =====
    sauvegarde->recupereEtat();
    refresh();
} // ======================================= FIN DU CONSTRUCTEUR QCOMPUTER ======================================= //



// ======================================= METHODES ======================================= //
void fenetrePrincipale::refreshMethode() {
    vuePile->setRowCount(getNombreItemAAfficher());
    QStringList labelList;
    for (int i = 1; i <= getNombreItemAAfficher(); i++) {
        QString str = QString::number(i);
        str += " : ";
        labelList << str;
    }
    vuePile->setVerticalHeaderLabels(labelList);
    //message-> setText(pile->getMessage());

    //On efface tout
    for (int i = 0; i < getNombreItemAAfficher(); i++) {
        vuePile->setItem(i, 0, new QTableWidgetItem(""));
    }

    //On parcourt le contenu de la pile et on affiche les éléments dans vuePile
    int nb = 0;
    vector<Item> liste = pile.copierListeItems();
    for (auto it = liste.rbegin(); it != liste.rend() && nb < getNombreItemAAfficher(); ++it, ++nb) {
        vuePile->item(nb, 0)->setText(it->obtenirLitterale().versString());
    }
}

void fenetrePrincipale::creerNouveauBoutonVariable(int i, QString key, QString valeur) {
    QPushButton *nouvelleVariable = new QPushButton(key);
    QSignalMapper *mapper = new QSignalMapper(this);
    QObject::connect(mapper, SIGNAL(mapped(QString)), this, SLOT(empileVariable(QString)));

    mapper->setMapping(nouvelleVariable, valeur);
    QObject::connect(nouvelleVariable, SIGNAL(clicked()), mapper, SLOT(map()));

    tableBoutonVariableProgramme->setCellWidget(i, 0, nouvelleVariable);
}

void fenetrePrincipale::creerNouveauBoutonProgramme(int i, QString key, QString valeur) {
    QPushButton *nouveauProgramme = new QPushButton(key);
    QSignalMapper *mapper = new QSignalMapper(this);
    QObject::connect(mapper, SIGNAL(mapped(QString)), this, SLOT(empileProgramme(QString)));
    mapper->setMapping(nouveauProgramme, valeur);
    QObject::connect(nouveauProgramme, SIGNAL(clicked()), mapper, SLOT(map()));
    tableBoutonVariableProgramme->setCellWidget(i, 1, nouveauProgramme);
}
// =======================================   FIN DES METHODES   ======================================= //




// =======================================   SLOTS QCOMPUTER   ======================================= //

void fenetrePrincipale::refresh() {
    message->setText(pile.obtenirEtat());
    //On efface tout
    vuePile->setRowCount(getNombreItemAAfficher());
    for (int i = 0; i < getNombreItemAAfficher(); i++) {
        vuePile->setItem(i, 0, new QTableWidgetItem(""));
    }

    //On parcourt le contenu de la pile et on affiche les éléments dans vuePile
    int nb = 0;
    vector<Item> liste = pile.copierListeItems();
    for (auto it = liste.rbegin(); it != liste.rend() && nb < getNombreItemAAfficher(); ++it, ++nb) {
        vuePile->item(nb, 0)->setText(it->obtenirLitterale().versString());
    }
    commande->setFocus();
}

void fenetrePrincipale::getNextCommande() {
    message->clear();
    QString saisieComplete = commande->text().toUpper();
    try {
        refIntp->interpreter(saisieComplete);
        commande->clear();
    } catch (ComputerException &ce) {
        commande->setText(ce.what());
    }
    refresh();
}

void fenetrePrincipale::affichageClavierVariable() {
    tableBoutonVariableProgramme->setVisible(true);
    afficherClavierVariable->setVisible(false);
    cacherClavierVariable->setVisible(true);
    commande->setFocus();
}

void fenetrePrincipale::cacheClavierVariable() {
    tableBoutonVariableProgramme->setVisible(false);
    cacherClavierVariable->setVisible(false);
    afficherClavierVariable->setVisible(true);
    commande->setFocus();
}

void fenetrePrincipale::affichageClavierCalculateur() {
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
    afficherClavierCalculateur->setVisible(false);
    cacherClavierCalculateur->setVisible(true);
    commande->setFocus();
}

void fenetrePrincipale::cacheClavierCalculateur() {
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
    cacherClavierCalculateur->setVisible(false);
    afficherClavierCalculateur->setVisible(true);
    commande->setFocus();
}

void fenetrePrincipale::ouvertureVueVariable() {
    vueVariable->show();
    commande->setFocus();
}

void fenetrePrincipale::ouvertureVueProgramme() {
    vueProgramme->show();
    commande->setFocus();
}

void fenetrePrincipale::ouvertureVueParametre() {
    vueParametre->setNombre(getNombreItemAAfficher());
    vueParametre->show();
    commande->setFocus();
}

void fenetrePrincipale::refreshTableVariableProgramme() {
    tableBoutonVariableProgramme->clearContents();
    if (persistance.obtenirTailleMapVariable() > persistance.obtenirTailleMapProgramme()) {
        tableBoutonVariableProgramme->setRowCount(persistance.obtenirTailleMapVariable());
    } else {
        tableBoutonVariableProgramme->setRowCount(persistance.obtenirTailleMapProgramme());
    };
    QMap<QString, QString>::iterator it;
    int j = 0;
    auto mapVariable = persistance.obtenirMapVariable();
    for (auto it = mapVariable.begin(); it != mapVariable.end(); it++) {
        creerNouveauBoutonVariable(j, it.key(), it.value());
        j++;
    }
    j = 0;
    auto mapProgramme = persistance.obtenirMapProgramme();
    for (auto it = mapProgramme.begin(); it != mapProgramme.end(); it++) {
        creerNouveauBoutonProgramme(j, it.key(), it.value());
        j++;
    }
}

void fenetrePrincipale::fermetureDerniereFenetre() {
    sauvegarde->sauvegardeEtat();
}
// =======================================   FIN DEFINITIONS SLOTS   ======================================= //
